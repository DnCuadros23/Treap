# Treap — Árbol Binario Equilibrado por Suerte (¡Prioridades Aleatorias!)

**Proyecto**: CS2023 "Anima tu Estructura de Datos" (UTEC)  
**Deadline**: 27/09/2026, 20:00  
**Grupo**: Hasta 3 personas

---

## ¿Qué es un Treap?

Imagina un **Árbol Binario de Búsqueda** (BST) normal, pero con un toque de magia aleatoria: cada nodo además de su `key` (para mantener el orden), tiene una `priority` aleatoria (para mantener el árbol equilibrado automáticamente, sin necesidad de complicadas rotaciones como en AVL o Red-Black Trees).

**La idea**: 
- Usas `key` para buscar: elementos pequeños a la izquierda, grandes a la derecha
- Usas `priority` para equilibrar: los nodos con prioridad alta suben automáticamente

**Resultado**: O(log n) esperado en inserción, búsqueda, eliminación. Simple y elegante.

### ¿Para qué sirve?
- Implementar conjuntos dinámicos que se buscan frecuentemente
- Split/merge eficientes (particionar un Treap en dos, combinar dos Treaps)
- Más simple que Red-Black Trees o AVL, pero igual de rápido en promedio
- Aparece en problemas competitivos de algoritmos

---

## Estructura del Proyecto

```
Treap/
├── include/treap/
│   └── treap.h                # Contrato (interfaz que usan todos)
├── src/treap/
│   ├── treap_core.cpp         # "Cámaras": snapshotNodes() y emit()
│   ├── insert.cpp             # Inserción + giros (rotaciones)
│   ├── search.cpp             # Búsqueda simple
│   └── erase.cpp              # Eliminación (por implementar)
├── src/
│   └── main.cpp               # Demo: inserta {50,30,70,...,10}, busca algunos
├── animation/
│   └── render_treap.py        # Script Manim (Persona C lo hará)
├── CMakeLists.txt             # Instrucciones para compilar
├── README.md                  # Este archivo
└── trace.jsonl                # Output: archivo con "película" del árbol
```

---

## Estado del Trabajo

### ✅ Listo (Denilson)

**treap_core.cpp** — El corazón de la captura:
- Cada nodo tiene un ID único (para que Manim sepa cuál es cuál)
- `snapshotNodes()`: toma una foto del árbol en ese momento (formato JSON)
- `emit()`: registra "qué pasó" + "cómo se veía el árbol en ese momento" → `trace.jsonl`

**insert.cpp** — El algoritmo bonito:
- Inserción normal de BST (izquierda/derecha según comparación)
- Después de insertar: si el nodo nuevo tiene prioridad alta, lo hacemos "subir" rotando
- Los giros (rotaciones) son O(1) cada uno, y hacemos ~log(n) giros en promedio

**search.cpp** — La búsqueda tradicional:
- Comparar la clave buscada con el nodo, ir izquierda o derecha
- Registramos cada paso para que Manim pueda mostrar la búsqueda paso a paso

**treap.h** — El contrato:
- Define qué funciones existen y qué parámetros usan
- Todos en el equipo usan esto como referencia

**main.cpp** — Demo funcional:
- Inserta los valores {50, 30, 70, 20, 40, 60, 80, 10}
- Busca algunos valores (60 = existe, 99 = no existe, 20 = existe)
- Genera `trace.jsonl` con ~25-30 eventos que Manim anima

**CMakeLists.txt** — Configuración para compilar:
- Funciona en Windows (Visual Studio), Linux (g++), Mac (clang)

---

### ⏳ Por Hacer (Persona B)

**erase.cpp** — Eliminación:
- [ ] Buscar la clave
- [ ] Si es una hoja: borrar y listo
- [ ] Si tiene un hijo: reemplazarla con ese hijo
- [ ] Si tiene dos hijos: rotar hacia abajo hasta que sea hoja, luego borrar
- [ ] Usar `emit()` para cada movimiento

---

### ⏳ Por Hacer (Persona C)

**Animación con Manim:**
- [ ] Leer `trace.jsonl` línea por línea
- [ ] Para cada par de líneas consecutivas: animar la transición (nodos se mueven, aparecen, desaparecen)
- [ ] Resaltar el nodo que está siendo manipulado
- [ ] Mostrar el texto del evento como subtítulo
- [ ] Exportar a video .mp4 de alta calidad

**Video Educativo** (requisitos del enunciado):
El video debe tener **1-2 minutos de duración** (máximo 5). Necesita:

1. **Introducción** (20-30 segundos)
   - Qué es un Treap, por qué existe
   - Ventaja: O(log n) sin complejidad de rebalanceo explícito

2. **Demo de Inserción** (40 segundos)
   - Mostrar cómo crece el árbol
   - Resaltar las rotaciones cuando suben nodos por prioridad

3. **Demo de Búsqueda** (20 segundos)
   - Mostrar el camino de búsqueda (izquierda/derecha)

4. **Caso Borde** (15 segundos)
   - Árbol vacío, un solo elemento, o worst-case de rotaciones

5. **Análisis de Complejidad** (15 segundos)
   - Treap: O(log n) esperado
   - BST normal: O(n) peor caso
   - Por qué la aleatoriedad ayuda

6. **Créditos** (10 segundos)
   - Título: "Treap — Árbol Binario Equilibrado por Suerte"
   - Nombres de los 3 integrantes

**Informe PDF** (requisitos del enunciado):
- Carátula: curso, nombres, fecha, estructura
- Explicación del TDA (qué es, para qué sirve)
- Herramientas usadas (C++17, Manim, CMake)
- **Instrucciones paso a paso**:
  1. Cómo compilar el código
  2. Cómo ejecutar y generar `trace.jsonl`
  3. Cómo correr Manim para animar
- Contribución de cada integrante (quién hizo qué)
- Análisis de complejidad (O(log n), O(n) espacio, etc.)
- Link funcional al repositorio GitHub
- Link funcional al video
- 2+ conclusiones personales (qué aprendimos, cuándo usarías Treap, etc.)
- Si te inspiraste en videos/ejemplos de terceros: cítalo

---

## Cómo Compilar y Ejecutar

### Necesitas:
- CMake 3.10 o más nuevo
- Compilador C++ que entienda C++17 (g++, clang, MSVC)

### En Linux o Mac:
```bash
cd Treap
mkdir build && cd build
cmake ..
cmake --build .
./treap_demo
```

### En Windows (Visual Studio):
```bash
cd Treap
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
.\Release\treap_demo.exe
```

### Qué pasa cuando lo ejecutas:
```
=== Treap: Inserción y Búsqueda ===
Generando trace.jsonl para animación Manim...

--- Fase 1: Inserción ---
Insertando 50
Insertando 30
... (8 inserciones totales)

--- Fase 2: Búsquedas ---
Buscando 60
  ✓ Encontrado
Buscando 99
  ✗ No encontrado
Buscando 20
  ✓ Encontrado

✓ Archivo trace.jsonl generado exitosamente.
  Para animar: python3 animation/render_treap.py
```

**Resultado**: Crea `trace.jsonl` con ~25-30 eventos que describen todo lo que pasó (inserciones, comparaciones, rotaciones, búsquedas).

---

## Quién Hace Qué

| Persona      | Responsabilidad | Archivos |
|--------------|-----------------|----------|
| **Denilson** | Infraestructura + Inserción | treap.h, treap_core.cpp, insert.cpp, main.cpp ✅ |
| **Alexander**        | Eliminación | erase.cpp |
| **C**        | Manim + Video + Informe PDF | render_treap.py, video.mp4, informe.pdf |

---

## Detalles Técnicos

### ¿Por qué funciona?

La aleatoriedad es la clave. Si todas las prioridades fueran 1,2,3,...,n (orden creciente), el árbol degeneraría en una lista y sería O(n). Pero como son **aleatorias**, con alta probabilidad el árbol queda equilibrado a O(log n) de profundidad.

### ¿Qué es `emit()`?

Cada vez que algo importante ocurre (insertamos un nodo, lo rotamos, lo buscamos), llamamos a `emit()` que dice:
- Qué pasó (`event`: "insert_leaf", "rotate_right", "search_found", etc.)
- Descripción amigable (`note`: "Insertando 50 con prioridad 853")
- Qué nodo resaltar en la animación (`highlighted_id`)
- **Foto actual del árbol** (`snapshot`: JSON con todos los nodos y sus conexiones)

Esto se escribe a `trace.jsonl`, una línea por evento. Manim lee esto y anima las transiciones.

### ¿Qué es `trace.jsonl`?

Un archivo de texto con una línea JSON por evento. Ejemplo:
```json
{"event":"insert_leaf","note":"Insertando 50 con prioridad 853","highlighted_id":1,"snapshot":{"1":{"key":50,"priority":853,"left":-1,"right":-1}}}
{"event":"insert_compare","note":"¿30 en qué lado de 50?","highlighted_id":1,"snapshot":{"1":{"key":50,"priority":853,"left":-1,"right":-1}}}
{"event":"insert_leaf","note":"Insertando 30 con prioridad 612","highlighted_id":2,"snapshot":{"1":{"key":50,"priority":853,"left":2,"right":-1},"2":{"key":30,"priority":612,"left":-1,"right":-1}}}
```

Manim procesa esto línea por línea y genera las animaciones.

---

## Checklist Antes de Gradescope

### Código
- [ ] Compila sin errores ni warnings
- [ ] `trace.jsonl` se genera correctamente
- [ ] Se ejecuta sin crashes
- [ ] Repositorio GitHub actualizado
- [ ] README.md con instrucciones funcionales

### Video
- [ ] Duración: 1-2 minutos (máx 5)
- [ ] Incluye intro conceptual
- [ ] Muestra inserción con rotaciones
- [ ] Muestra búsqueda
- [ ] Incluye análisis de complejidad
- [ ] Tiene créditos con nombres
- [ ] Formato: .mp4 alta resolución
- [ ] Si es muy grande: enlace funcional (Drive, YouTube no listado, etc.)

### Informe PDF
- [ ] Carátula (curso, nombres, estructura, fecha)
- [ ] Explicación del TDA
- [ ] Herramientas usadas
- [ ] Pasos para compilar y ejecutar
- [ ] Contribuciones de cada integrante
- [ ] Análisis de complejidad
- [ ] Link a GitHub (funciona ✓)
- [ ] Link a video (funciona ✓)
- [ ] 2+ conclusiones escritas

### Entrega
- [ ] Solo una persona sube a Gradescope
- [ ] Incluye: código + PDF + video (o links)
- [ ] Antes de 27/09/2026 20:00
- [ ] Verifica que se subió correctamente

---

## Importante: Animación Real (No Simulada)

El enunciado dice explícitamente: **la animación debe estar impulsada por una implementación real** de Treap, no "a mano" ni usando librerías pre-hechas.

 **Nuestro enfoque cumple**: 
- C++ real → `emit()` registra eventos reales → `trace.jsonl` tiene datos reales → Manim anima basándose en esos datos reales

 **No permitido**:
- Animar valores ficticios
- Usar una implementación de terceros (stdlib, librería)
- Falsificar los eventos

---

**Documentación actualizada: 2026-09-25 | Por Persona Denilson**

