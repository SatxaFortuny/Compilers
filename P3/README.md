# Pràctica 3: Creació d’un compilador complet

En aquest document s’explicara breument el funcionament de les parts principals del projecte junt amb les decisions de disseny escollides.
Aquesta pràctica es centra en la resolució de codis que necessiten saber el numero d’una linea de codi que encara no s’ha llegit, pel que ens centrarem en explicar les instruccions que necessiten aquest tractament especial.

## Detall d'Implementació: Gestió del Control de Flux (IF-THEN)

Aquesta secció detalla el funcionament intern del compilador per a la generació de Codi de Tres Adreces (C3A) en estructures condicionals, basat en la tècnica de **Backpatching** (emplenat posterior de salts).

El procés es divideix en tres etapes cronològiques durant l'anàlisi sintàctica (Bison):

### 1. Detecció de la Sentència Booleana (Condició)
Quan l'analitzador sintàctic (Bison) detecta una expressió booleana (ex: `a < b`), no genera un valor (1 o 0), sinó que genera **flux de control**.

1.  **Generació de Codi:** S'afegeixen immediatament a l'array global d'instruccions (`code_memory`) dues instruccions amb destí desconegut:
    ```text
    Línia X:   IF PREDICAT GOTO ??
    Línia X+1: GOTO ??
    ```
2.  **Creació de Llistes:** Es generen dues llistes dinàmiques associades a l'estructura semàntica (`$$`) d'aquesta regla:
    * **`truelist`:** Conté l'índex de la instrucció del salt condicional (Línia X).
    * **`falselist`:** Conté l'índex de la instrucció del salt incondicional (Línia X+1).

Aquestes llistes serveixen per "apuntar" les instruccions que s'hauran d'editar (backpatch) més endavant.

### 2. Detecció del token `THEN` (El Marcador)
Just després de l'expressió i abans del bloc de sentències, el compilador detecta una regla buida anomenada **Marker**.

* **Funció:** Captura el número de línia actual (`instruction_line`) en el moment exacte abans d'entrar al cos del `if`.
* **Emmagatzematge:** Aquest valor (la referència a l'inici del codi del bloc) es guarda a la variable semàntica del marcador (accessible posteriorment com a `$4`).

### 3. Detecció del token `FI` (Resolució Final)
Quan Bison detecta aquest token, significa que s'ha processat tot el bloc condicional i s'activa la regla completa `IF-THEN-FI`. En aquest moment, es disposa de tota la informació necessària per connectar els salts.

Es realitza el procés de **Backpatching** de la següent manera:

* **Resolució del Camí CERT (`truelist`):**
    S'agafa la `truelist` (generada al pas 1) i a totes les instruccions apuntades per aquesta llista se'ls assigna com a destí el valor capturat pel marcador (`$4`).
    > *Resultat: Si la condició és certa, salta a l'inici del bloc.*

* **Resolució del Camí FALS (`falselist`):**
    S'agafa la `falselist` (generada al pas 1) i se'ls assigna com a destí la línia actual (`instruction_line`), que correspon a la instrucció immediatament posterior al `FI`.
    > *Resultat: Si la condició és falsa, salta al final i evita executar el bloc.*


## Detall d'Implementació: Gestió del Control de Flux (IF-THEN-ELSE)

En el cas de les estructures condicionals amb alternativa (`else`), la lògica de **Backpatching** s'amplia per gestionar el salt exclusiu entre blocs i evitar que s'executin tots dos.

El procés es divideix en quatre etapes cronològiques durant l'anàlisi sintàctica:

### 1. Detecció de la Sentència Booleana (Condició)
Igual que en el cas simple, Bison detecta l'expressió i genera el flux de control inicial:

1.  **Generació de Codi:** S'afegeixen a l'array global (`code_memory`) els salts inicials:
    ```text
    Línia X:   IF PREDICAT GOTO ??
    Línia X+1: GOTO ??
    ```
2.  **Creació de Llistes:** Es generen les llistes `truelist` (index Línia X) i `falselist` (index Línia X+1).

### 2. Detecció del token `THEN` (Primer Marcador)
Es detecta el primer marcador buit just abans del bloc *then*.
* **Funció:** Captura el número de línia d'inici del bloc *then*.
* **Emmagatzematge:** Es guarda a la variable semàntica del marcador (accessible com a `$4`).

### 3. Detecció del token `ELSE` (Salt de Sortida i Segon Marcador)
Aquest és el punt crític que diferencia aquesta estructura. Just quan s'acaba el bloc *then* i es llegeix la paraula `else`, s'executa una **acció intermèdia**:

1.  **Generació de Salt de Sortida:** Com que acabem d'executar el *then*, hem de saltar-nos el *else*. S'emet una instrucció incondicional:
    ```text
    Línia Y:   GOTO ??
    ```
    Es crea una nova llista temporal (`nextlist`) que apunta a aquesta instrucció.

2.  **Segon Marcador:** Immediatament després, un segon marcador captura la línia actual, que correspon a l'inici del bloc *else*. Aquest valor es guarda a la seva variable semàntica (accessible com a `$8`).

### 4. Detecció del token `FI` (Resolució Final)
Al final de l'estructura, s'activa la regla completa i es resolen tots els camins pendents amb tres operacions de Backpatching:

* **Resolució del Camí CERT (`truelist`):**
    Apuntem la `truelist` de la condició al **Primer Marcador** (`$4`).
    > *Resultat: Si és cert, entra al bloc THEN.*

* **Resolució del Camí FALS (`falselist`):**
    Apuntem la `falselist` de la condició al **Segon Marcador** (`$8`).
    > *Resultat: Si és fals, salta directament a l'inici del bloc ELSE.*

* **Resolució de la SORTIDA DEL THEN (`nextlist`):**
    Apuntem la llista del salt incondicional generat al pas 3 (el `GOTO` creat abans del *else*) a la línia actual (`instruction_line`).
    > *Resultat: Quan acaba d'executar el bloc THEN, salta al final de tot per no executar el ELSE.*


## Detall d'Implementació: Gestió del Control de Flux (Bucle FOR)

La implementació del bucle `FOR` presenta un repte addicional: cal generar instruccions de control (inicialització i comprovació) abans de processar el cos, i instruccions d'actualització (increment) al final. Per fer-ho en una sola passada, s'utilitza una regla auxiliar a la gramàtica.

El procés es divideix en tres etapes cronològiques:

### 1. Detecció de la Capçalera (`for_header`)
Abans de processar les sentències de dins del bucle, s'activa una regla auxiliar que gestiona la declaració `FOR i IN inici .. final DO`. En aquest moment es realitzen tres accions crítiques:

1.  **Inicialització:** S'emet la instrucció per assignar el valor d'inici a la variable iteradora (`i := inici`).
2.  **Marcatge de l'Inici:** Es captura la línia actual (`instruction_line`). Aquesta serà l'etiqueta de retorn (`L_INICI`) on saltarem després de cada iteració.
3.  **Condició de Sortida:** S'emet una instrucció condicional per comprovar si hem acabat:
    ```text
    Línia X: IF i > final GOTO ??
    ```
    Es crea una `falselist` (o llista de sortida) amb aquest salt pendent.
    > *Nota: Si la condició es compleix (i > final), hem de sortir del bucle.*

### 2. Processament del Cos (`stmt_list`)
Es processen les sentències internes del bucle de manera estàndard. Aquestes instruccions s'emeten seqüencialment a continuació de la capçalera.

### 3. Detecció del token `DONE` (Tancament i Cicle)
Quan l'analitzador detecta el final del bucle, executa les accions per tancar el cicle i resoldre els salts pendents:

1.  **Increment:** S'emet automàticament la instrucció per augmentar la variable iteradora:
    ```text
    i := i + 1
    ```
2.  **Salt de Retorn (Loop):** S'emet un salt incondicional (`GOTO`) apuntant a la línia capturada al pas 1 (`L_INICI`). Això força la repetició del bucle i la re-avaluació de la condició.
    ```text
    GOTO L_INICI
    ```
3.  **Backpatching de la Sortida:** Finalment, es resol el salt pendent generat al pas 1 (la `falselist` de la condició de sortida). S'apunta a la línia actual, permetent que quan el bucle acabi (`i > final`), el flux salti directament aquí i continuï amb la resta del programa.


## Detall d'Implementació: Gestió del Control de Flux (Bucle WHILE)

El bucle `WHILE` combina la presa de decisions (com un `IF`) amb la repetició. Per aconseguir-ho, s'utilitzen dos marcadors: un per saber on tornar a començar (bucle) i un altre per saber on comença el codi intern.

El procés es divideix en quatre etapes cronològiques:

### 1. Detecció de l'Inici (Primer Marcador)
Immediatament després de llegir la paraula clau `WHILE` (i abans de processar la condició), es detecta un **Primer Marcador**.
* **Funció:** Captura la línia actual, que correspon a l'inici absolut del bucle.
* **Utilitat:** Aquesta serà l'etiqueta de retorn (`L_INICI`) on farem el salt incondicional al final de cada iteració per tornar a avaluar la condició.
* **Emmagatzematge:** Es guarda a la variable semàntica `$2`.

### 2. Detecció de la Sentència Booleana (Condició)
Es processa l'expressió lògica. Com en els casos anteriors, es generen dos camins de flux:
* **`truelist`:** Salts pendents si la condició és certa (volem entrar al bucle).
* **`falselist`:** Salts pendents si la condició és falsa (volem sortir del bucle).

### 3. Detecció del token `DO` (Segon Marcador)
Just abans d'entrar al cos del bucle (`stmt_list`), es detecta un **Segon Marcador**.
* **Funció:** Captura la línia on comencen les instruccions del cos del bucle.
* **Emmagatzematge:** Es guarda a la variable semàntica `$5`.

## 4. Detecció del token `DONE` (Tancament i Resolució)
Al final del bloc, s'activa la regla completa i es realitzen totes les connexions (Backpatching) i l'emissió del salt de retorn:

1.  **Resolució de l'Entrada (`truelist`):**
    S'apunta la `truelist` de la condició al **Segon Marcador** (`$5`).
    > *Resultat: Si la condició és certa, entra a executar les sentències del cos.*

2.  **Salt de Retorn (Loop):**
    S'emet una instrucció `GOTO` incondicional apuntant al **Primer Marcador** (`$2`).
    > *Resultat: Un cop acabades les sentències, torna a dalt de tot per re-avaluar la condició.*

3.  **Resolució de la Sortida (`falselist`):**
    S'apunta la `falselist` de la condició a la línia actual (`instruction_line`).
    > *Resultat: Si la condició inicial (o les re-avaluacions posteriors) és falsa, salta al final del bloc i continua el programa.*


## Detall d'Implementació: Gestió del Control de Flux (Estructura SWITCH)

La implementació del `SWITCH` en un compilador d'una sola passada presenta un repte únic: quan processem un `CASE`, necessitem saber contra quina variable estem comparant, tenint en compte que hi pot haver switches encadenats (un dins de l'altre).

Per resoldre-ho, s'utilitza una **Pila Global de Context (`switch_stack`)** i es genera una "cascada" de comparacions.

El procés es divideix en quatre etapes:

### 1. Detecció de l'Inici (`SWITCH`)
Quan s'avalua l'expressió del switch (ex: `switch(a)`):
1.  **Push a la Pila:** Es guarda l'adreça de la variable avaluada (`a`) al cim de la pila global `switch_stack`.
    * *Motiu:* Això permet que els `CASE` posteriors sàpiguen quina variable han de comparar, sense confondre's amb variables de switches pares.

### 2. Processament dels `CASE` (Encadenament en Cascada)
L'avaluació dels casos es tradueix en una seqüència lineal de comparacions (equivalent a `if ... else if ... else if ...`). La connexió entre un cas i el següent es realitza mitjançant la regla gramatical recursiva de la llista de casos:

1.  **Comparació de Desigualtat:** Cada cas genera una comprovació inicial:
    ```text
    IF variable != valor_cas GOTO ??
    ```
    Aquest salt pendent es guarda a la `falselist` del cas actual.

2.  **Backpatching Encadenat:** Quan l'analitzador detecta que comença un **nou cas** (següent item de la llista), utilitza el marcador d'inici del nou cas per resoldre la `falselist` del cas **anterior**.
    > *Resultat:* Es crea una cadena lògica on, si el Cas 1 no coincideix, el flux salta automàticament a l'inici de la comprovació del Cas 2, i així successivament.

3.  **Cos del Cas i Break:** Si la comprovació no salta (coincidència trobada), s'executa el cos. Si hi ha un `BREAK`, es genera un `GOTO` incondicional cap al final del Switch, evitant avaluar els casos restants.

### 3. Gestió del `BREAK`
Dins de cada cas, si es detecta la sentència `BREAK`:
1.  **Salt de Sortida:** S'emet un salt incondicional (`GOTO ??`) cap al final de l'estructura `SWITCH`.
2.  **Acumulació:** Aquest salt s'afegeix a una llista general de sortida (`nextlist`) que acumula tots els `breaks` de tots els casos.

### 4. Detecció del token `FSWITCH` (Final i Neteja)
Quan s'acaba l'estructura:
1.  **Backpatching de Sortida:** Es resol la `nextlist` (tots els breaks acumulats) fent que apuntin a la línia actual (`instruction_line`).
2.  **Backpatching de Fallada:** Es resolen els salts dels casos que no han coincidit (si no hi ha `default`).
3.  **Restauració de Context:** S'executa `pop_switch()` per treure la variable actual de la pila.
    * *Resultat:* Si estàvem dins d'un switch fill, el cim de la pila torna a ser la variable del switch pare.