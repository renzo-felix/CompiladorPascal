# CompiladorPascal

#  README - Nuevos Tokens para Scanner Pascal

Este documento explica **qué significan los nuevos tokens agregados** al scanner del compilador Pascal y **por qué se usan**.

El objetivo es facilitar el soporte de **punteros** y **arrays** en el lenguaje Pascal.

---

## Nuevos Tokens Agregados

### `CARET`
- **Símbolo en código:** `^`
- **Significado en Pascal:**
  - Declara o accede a un puntero.
  - Ejemplo:
    ```pascal
    var p: ^Integer;
    p^ := 10;
    ```
- **Por qué se necesita:**
  - El scanner debe reconocer `^` como un token separado.
  - El parser decidirá si es parte de un tipo (`^Integer`) o un acceso (`p^`).

---

###  `ARRAY`
- **Palabra clave en Pascal:** `array`
- **Significado:**
  - Declara arreglos (arrays).
  - Ejemplo:
    ```pascal
    var a: array[1..10] of Integer;
    ```
- **Por qué se necesita:**
  - El scanner reconoce `array` como palabra reservada para que el parser pueda construir la declaración de un arreglo.

---

### 3 `OF`
- **Palabra clave en Pascal:** `of`
- **Significado:**
  - Especifica el tipo de los elementos de un array.
  - Ejemplo:
    ```pascal
    array[1..10] of Integer
    ```
- **Por qué se necesita:**
  - Indica la parte del tipo de elementos en la definición del array.

---

###  `LEFT_BRACKET` y `RIGHT_BRACKET`
- **Símbolos en código:** `[` y `]`
- **Significado en Pascal:**
  - Delimitan el rango de índices de un array.
  - Ejemplo:
    ```pascal
    array[1..10] of Integer
    ```
- **Por qué se necesita:**
  - Permiten al parser detectar el inicio y fin de la lista de índices o rangos en un array.

---

###  `DOT_DOT`
- **Símbolo en código:** `..`
- **Significado en Pascal:**
  - Define un rango de valores.
  - Muy usado en arrays para especificar índices.
  - Ejemplo:
    ```pascal
    array[1..10] of Integer
    ```
- **Por qué se necesita:**
  - Es un token especial para reconocer rangos en las declaraciones de arrays.
  - Es diferente de un solo `.` (que marca el final de un programa en Pascal).

---

## Resumen de Nuevos Tokens

| TOKEN         | Símbolo / Palabra | Usado para                                     |
|----------------|-------------------|-----------------------------------------------|
| `CARET`       | `^`                | Declarar o acceder a punteros                 |
| `ARRAY`       | `array`            | Declarar arreglos                             |
| `OF`          | `of`               | Especificar tipo de elementos en arrays       |
| `LEFT_BRACKET`| `[`                | Inicio del rango de índices en arrays         |
| `RIGHT_BRACKET`| `]`               | Fin del rango de índices en arrays            |
| `DOT_DOT`     | `..`               | Definir rango (ej: `1..10`)                   |

---
```
 Gramática Pascal Simplificada 
Programa ::= 'program' Identificador ';' Bloque '.'
Bloque ::= ListaDeclaracionesVariables ListaSubProgramas ListaSentencias

ListaDeclaracionesVariables ::= var { DeclaracionVariable }
DeclaracionVariable ::= ListaIdentificadores ':' Tipo ';'
ListaIdentificadores ::= Identificador { ',' Identificador }
Tipo ::= 'integer' | 'longint' | 'boolean'| ArrayType | PointerType

ArrayType ::= 'array' '[' Range ']' 'of' Type
PointerType ::= '^' Type

Rango ::= Numero '..' Numero

ListaSubProgramas ::= { DeclaracionSubprograma }
DeclaracionSubprograma ::= DeclaracionFuncion
DeclaracionFuncion ::= 'function' Identificador '(' [ ListaParametros ] ')' ':' Tipo ';' Bloque ';'
ListaParametros ::= Parametro { ';' Parametro }
Parametro ::= ListaIdentificadores ':' Tipo

ListaSentencias ::= 'begin' { Sentencia ';' } 'end'

Sentencia ::= SentenciaAsignacion | SentenciaEscritura | SentenciaCondicional | SentenciaPara | SentenciaCompuesta

SentenciaAsignacion ::= Identificador ':=' Expresion

SentenciaEscritura ::= 'writeln' '(' Expresion ')'
SentenciaCondicional ::= 'if' Expresion 'then' Sentencia [ 'else' Sentencia ]
SentenciaPara ::= 'for' Identificador ':=' Expresion 'to' Expresion 'do' Sentencia
SentenciaCompuesta ::= 'begin' ListaSentencias 'end'


Expresion ::= ExpresionSimple [ OperadorRelacional ExpresionSimple ]
ExpresionSimple ::= Termino { OperadorAditivo Termino }
Termino ::= Factor { OperadorMultiplicativo Factor }
Factor ::= '(' Expresion ')' | Numero | Identificador | LlamadaFuncion
LlamadaFuncion ::= Identificador '(' [ Expresion { ',' Expresion } ] ')'
OperadorRelacional ::= '=' | '<' | '<=' | '<>' | '>' | '>='
OperadorAditivo ::= '+' | '-'
OperadorMultiplicativo ::= '*' | '/'
Numero ::= entero_literal
Identificador ::= identificador
Identificador ::= identificador



```


```pascal
var
  p: ^Integer;
  a: array[1..10] of Integer;
