# Projecte de Compiladors (GEI)

Aquest repositori conté el desenvolupament de les tres pràctiques de l'assignatura de Compiladors. El projecte evoluciona des d'un intèrpret bàsic fins a un compilador complet capaç de generar Codi de Tres Adreces (C3A) utilitzant tècniques avançades.

## Resum de les Pràctiques

### Pràctica 1: Calculadora i Intèrpret
Implementació de la part frontal (*front-end*) d'un intèrpret que executa les instruccions directament.
* **Funcionalitat:** Avaluació d'expressions aritmètiques i booleanes, gestió de variables i assignacions.
* **Tipus de Dades:** Suport per a Enters, Reals (Float), Booleans i Cadenes de text (Strings) amb conversions implícites.
* **Estructures:** Implementació de tipus complexos `STRUCT` amb gestió de memòria pròpia (còpia profunda de camps).
* **Disseny:** Ús d'una gramàtica estratificada per gestionar la precedència d'operadors sense utilitzar directives `%left`/`%right`.

### Pràctica 2: Compilador Senzill (C3A)
Creació de la part dorsal (*back-end*) per generar codi intermedi (C3A) per a operacions seqüencials i iteratives simples.
* **Generació de Codi:** Traducció d'expressions a instruccions de tres adreces utilitzant variables temporals.
* **Gestió de Memòria:** Càlcul d'`offsets` per a l'ús de taules (Arrays) unidimensionals i accés mitjançant instruccions de càrrega/escriptura.
* **Control de Flux:** Implementació del bucle `REPEAT-DO-DONE` utilitzant etiquetes seqüencials.
* **Optimització:** *Constant Folding* (plegat de constants) per avaluar operacions entre literals en temps de compilació.

### Pràctica 3: Compilador Complet amb Backpatching
Ampliació del compilador per gestionar estructures de control de flux complexes en una sola passada.
* **Backpatching:** Tècnica per resoldre els salts condicionals (emplenat posterior) en estructures `IF-THEN`, `IF-THEN-ELSE` i `WHILE`.
* **Switch-Case:** Implementació de l'estructura `SWITCH` utilitzant una pila global per gestionar el context de les variables avaluades i salts en cascada.
* **Bucles Avançats:** Suport per a bucles `FOR` i `WHILE` amb gestió correcta de les condicions d'inici i final.
* **Expressions Booleanes:** Generació de flux de control (salts) en lloc de valors numèrics per a les condicions lògiques.

---

## Instruccions d'Ús

El projecte utilitza `Flex` i `Bison` per a l'anàlisi, i `GCC` per a la compilació del codi C generat.

### Requisits
* Flex
* Bison
* GCC (amb llibreries estàndard i matemàtiques `-lm`)
* Make

### Compilació i Execució

Per compilar tot el projecte, executa la comanda `make` al directori de la pràctica. Això generarà l'executable (per defecte `calc.exe`).

Per executar el programa, cal passar dos arguments: el fitxer amb el codi font d'entrada i el nom del fitxer on es guardarà la sortida (resultat de l'execució o codi C3A).

>calc.exe entrada.txt sortida.txt