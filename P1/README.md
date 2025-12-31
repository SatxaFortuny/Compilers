# Pràctica 1: Calculadora / Intèrpret

En aquest document s’explicarà breument el funcionament de les parts principals del projecte junt amb les decisions de disseny escollides per a la implementació d'aquest intèrpret (Calculadora).
Aquesta pràctica es centra en l'anàlisi lèxica i sintàctica, la gestió de tipus dinàmics (`INT`, `FLOAT`, `STRING`, `BOOL`), l'avaluació d'expressions complexes i la implementació d'estructures de dades (`STRUCT`).

## Detall d'Implementació: Precedència d'Operadors

No s'han utilitzat les directives de precedència de Bison (`%left`, `%right`). En el seu lloc, s'ha dissenyat una gramàtica estructurada que força l'ordre d'avaluació mitjançant la jerarquia de les regles.

L'estructura jeràrquica implementada, de menor a major precedència (de dalt a baix), és:

1.  **Lògica Booleana:** `or_predicate` $\rightarrow$ `and_predicate` $\rightarrow$ `not_predicate`.
2.  **Comparació:** `predicate` (operadors `EQ`, `LT`, `GE`, etc.).
3.  **Aritmètica de Suma:** `expression` (`+`, `-`).
4.  **Aritmètica de Producte:** `term` (`*`, `/`, `%`).
5.  **Unaris i Potència:** `unary` (signe negatiu) i `pow` (potència `**`).
6.  **Àtoms:** `atom` (literals, parèntesis, crides a funcions).

> *Resultat:* L'arbre sintàctic es construeix de manera que les operacions amb més prioritat (com la potència o els parèntesis) es troben més a prop de les fulles i s'avaluen primer.

## Detall d'Implementació: Gestió de Tipus

L'intèrpret gestiona quatre tipus bàsics (`INT`, `FLOAT`, `STRING`, `BOOL`). Per permetre operacions entre ells, s'ha implementat una lògica manual dins de les accions semàntiques de C:

* **Promoció Numèrica:** En operacions mixtes (`INT` amb `FLOAT`), l'operand enter es converteix temporalment a flotant per realitzar el càlcul, retornant un resultat `FLOAT`.
* **Concatenació de Cadenes:** L'operador `+` detecta si un dels operands és `STRING`. Si és així, converteix automàticament l'altre operand (sigui número o booleà) a text utilitzant `sprintf` i realitza la concatenació gestionant la memòria dinàmica.
* **Booleans:** Els operadors relacionals retornen sempre un tipus `BOOL` (internament un enter 0 o 1), necessari per als operadors lògics `AND`/`OR`.

## Detall d'Implementació: Estructures (`STRUCT`)

La implementació de `structs` ha estat un dels reptes principals, ja que requereix guardar una definició de tipus i instanciar variables amb camps propis.

El procés es divideix en tres etapes:

### 1. Definició i Instanciació
Quan es declara un struct (ex: `struct Punt { int x; } p1, p2`), l'analitzador:
1.  Captura la llista de camps (`token_list`) com una plantilla.
2.  Recorre la llista de variables a crear (`id_list`).
3.  Per a cada variable (ex: `p1`), crea una entrada a la taula de símbols de tipus `TYPE_STRUCT`.
4.  **Còpia:** Invoca la funció `copy_tokens()` per duplicar la llista de camps per a cada instància.
    * *Motiu:* Això assegura que modificar `p1.x` no afecti el valor de `p2.x`. Cada variable té la seva pròpia memòria per als camps.

### 2. Accés a Membre (`.`)
L'accés `ID . ID` (ex: `p1.x`) es resol mitjançant la funció auxiliar `find_field()`. Aquesta funció recorre la llista de tokens interna de la variable struct per trobar el camp sol·licitat i retornar-ne el valor o l'adreça per a l'assignació.

## Detall d'Implementació: Funcions Incorporades

S'han implementat les funcions requerides definint-les com a regles dins la gramàtica (`atom`):

* **Matemàtiques (`SIN`, `COS`, `TAN`, `**`):** Utilitzen la llibreria estàndard `<math.h>`. Es realitza un càsting explícit a `double` per als càlculs i es retorna `FLOAT`.
* **Cadenes (`LEN`, `SUBSTR`):**
    * `LEN`: Calcula la longitud utilitzant `strlen`.
    * `SUBSTR`: Extreu una subcadena gestionant els límits (per evitar *segmentation faults* si l'índex surt de rang) i reservant nova memòria per al resultat.