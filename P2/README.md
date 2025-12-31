# Pràctica 2: Compilació d’un llenguatge senzill

En aquest document s’explicarà breument el funcionament de les parts principals del projecte junt amb les decisions de disseny escollides per a la generació de Codi de Tres Adreces (C3A).
Aquesta pràctica es centra en la gestió de tipus (enters i reals), l'aritmètica complexa, la gestió de memòria per a taules (arrays) i estructures iteratives simples.

## Detall d'Implementació: Gestió de Tipus i Expressions

El compilador gestiona dos tipus de dades primitius: `INT` i `FLOAT`. Per gestionar les operacions entre ells, s'han pres les següents decisions de disseny a la gramàtica:

### 1. Promoció Implícita de Tipus (Càsting)
Quan es detecta una operació binària (suma, resta, multiplicació, divisió) entre operands de diferent tipus, el compilador prioritza el tipus `FLOAT`.

* **Lògica:** Si es detecta `INT op FLOAT` o `FLOAT op INT`, s'emet immediatament una instrucció de conversió `I2F` (Integer to Float) per a l'operand enter.
* **Generació de Codi:** Es crea un temporal per guardar el valor convertit i s'utilitza aquest temporal per a l'operació final, que serà en coma flotant.

### 2. Optimització: Constant Folding (Plegat de Constants)
S'ha implementat una optimització en temps de compilació seguint les indicacions de l'enunciat. Si els dos operands d'una expressió són **literals** (constants), el compilador no genera codi C3A.
* **Funcionament:** Calcula el resultat directament en C i modifica l'atribut `$$` per marcar-lo com a constant (`is_const = 1`).
* **Resultat:** Una expressió com `3 + 5` no genera una instrucció `ADDI`, sinó que es propaga com el valor `8` (o `8.0` si és float).

## Detall d'Implementació: Operador de Potència (`**`)

A diferència de les operacions bàsiques, el C3A no disposa d'una instrucció primitiva per a la potència. Per resoldre això, s'ha implementat la generació d'un micro-bucle directament dins de la regla gramatical.

El procés es divideix en tres etapes durant l'anàlisi:

1.  **Inicialització:** Es genera un temporal pel resultat (inicialitzat a 1) i es copia l'exponent a un comptador temporal.
2.  **Estructura del Bucle:**
    * Es guarda la línia actual (`instruction_line`) com a punt de retorn.
    * S'emet la multiplicació acumulativa: `res := res * base`.
    * S'emet el decrement del comptador: `cnt := cnt - 1`.
3.  **Condició de Salt:** S'emet una comprovació al final: `IF cnt > 0 GOTO inici`.


## Detall d'Implementació: Gestió de Taules (Arrays)

La gestió de variables dimensionades es basa en el càlcul d'offsets i instruccions específiques d'accés a memòria.

### 1. Declaració i Memòria
S'utilitza una variable global `global_offset` (inicialitzada a 25 com es demana a l'enunciat) per assignar adreces úniques.
* Variables simples: Incrementen l'offset en 1.
* Arrays: Incrementen l'offset segons la mida declarada (`val->size`).

### 2. Accés i Assignació
Per accedir als elements, s'utilitzen instruccions especials que accepten índexs variables:
* **Lectura (`val := arr[idx]`):** Es resol generant la instrucció personalitzada `emit_array_load`.
* **Escriptura (`arr[idx] := val`):** Es resol amb `emit_array_store`.
* **Control d'Errors:** S'implementa una comprovació semàntica per assegurar que la variable és realment un array i que l'índex és de tipus `INT`.

## Detall d'Implementació: Control de Flux (REPEAT-DO-DONE)

Per implementar el bucle `REPEAT`, que executa un bloc de codi un nombre determinat de vegades, s'ha utilitzat una regla auxiliar (`loop_header`) per gestionar les etiquetes de salt de manera seqüencial.

El flux és el següent:

### 1. Capçalera (`loop_header`)
Abans de processar el cos del bucle:
1.  Es captura l'expressió que indica el nombre de repeticions.
2.  Es guarda aquest valor en un comptador temporal.
3.  Es captura la línia actual (`get_current_line()`) i es guarda a l'estructura semàntica `$$`. Aquesta línia marca l'inici del bucle.

### 2. Cos (`stmt_list`)
Es processen les sentències internes normalment.

### 3. Tancament (`DONE`)
Al final de l'estructura, es recupera la informació de la capçalera (`$1`):
1.  **Decrement:** S'emet `SUBI` per restar 1 al comptador temporal.
2.  **Salt Condicional:** S'emet `IF comptador > 0 GOTO inici` utilitzant la línia capturada al pas 1.