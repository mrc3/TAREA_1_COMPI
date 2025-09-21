# Tarea 1 – Compiladores  
**Analizador Léxico JSON Simplificado**
Alumnos: Marcelo Caceres - 5165343, Roberto Arce - 4500872

## 📌 Descripción
Este proyecto implementa un **analizador léxico** para un lenguaje JSON simplificado.  
El programa lee un archivo `.txt` con contenido JSON, reconoce tokens válidos y genera un archivo de salida con los componentes léxicos encontrados.

En caso de error léxico (ej. cadenas no cerradas, números mal formados), se muestra un mensaje de error y el analizador continúa procesando las siguientes líneas.

## 🎯 Objetivos
- Implementar un **Analizador Léxico** que reconozca:
  - Llaves `{ }`
  - Corchetes `[ ]`
  - Comas `,`
  - Dos puntos `:`
  - Literales de cadena (`STRING`)
  - Números (`NUMBER`)
  - Palabras reservadas: `true`, `false`, `null`
- Practicar conceptos de análisis léxico en compiladores.

## 📂 Archivos
- `lexer_json.c` → código fuente del analizador.
- `fuente.txt` → ejemplo de entrada (proporcionado por el enunciado).
- `salida.txt` → salida esperada para `fuente.txt`.
- `fuente2.txt` → archivo de prueba adicional con errores léxicos.
- `salida2.txt` → salida generada para `fuente2.txt`.

## ⚙️ Compilación
Compilar el programa (requiere **gcc** en Linux/Mac o WSL en Windows):
# gcc -std=c11 -O2 -Wall -Wextra -o lexer_json lexer_json.c
./lexer_json fuente.txt > salida.txt
./lexer_json fuente2.txt > salida2.txt

```bash
gcc -std=c11 -O2 -Wall -Wextra -o lexer_json lexer_json.c
