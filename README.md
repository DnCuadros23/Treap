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
│   └── erase.cpp              # Eliminación
├── src/
│   └── main.cpp               # Demo: 4 fases (inserción, búsqueda, eliminación, caso borde)
├── animation/
│   └── render_treap.py        # Script Manim: 4 escenas
├── .vscode/
│   ├── tasks.json             # Tarea de compilación del proyecto completo
│   └── c_cpp_properties.json  # IntelliSense (include path)
├── CMakeLists.txt             # Instrucciones para compilar
├── guion.md                   # Guion del video, repartido entre los 3 integrantes
├── .gitignore                 # Ignora binarios, build/, trace.jsonl, media/
├── media/                     # Salida de Manim (NO versionada, se regenera)
│   └── videos/render_treap/1080p60/
│       ├── Intro.mp4 · TreapScene.mp4 · Complejidad.mp4 · Creditos.mp4
│       └── video_final.mp4    # Las 4 escenas unidas — esto es lo que se entrega
└── README.md                  # Este archivo
```

> **Nota**: `trace.jsonl` **no** está versionado ni vive fijo en la raíz. `emit()` lo abre con
> ruta relativa, así que se genera **en el directorio desde donde ejecutas el binario**.
> Ejecuta `./treap_demo` desde la raíz del repo para que quede ahí (que es donde el script
> de Manim lo busca primero).

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
- Prioridades en rango `[1, 999]`: sigue siendo aleatorio, pero cabe dibujado sobre el nodo

**search.cpp** — La búsqueda tradicional:
- Comparar la clave buscada con el nodo, ir izquierda o derecha
- Registramos cada paso para que Manim pueda mostrar la búsqueda paso a paso

**treap.h** — El contrato:
- Define qué funciones existen y qué parámetros usan
- Todos en el equipo usan esto como referencia

**main.cpp** — Demo funcional, integra las 3 partes:
- **Fase 1**: inserta {50, 30, 70, 20, 40, 60, 80, 10}
- **Fase 2**: busca 60 (existe), 99 (no existe), 20 (existe)
- **Fase 3**: elimina 20, 70, 50 y 99 (este último no existe)
- **Fase 4 (caso borde)**: vacía el árbol por completo, busca en el árbol vacío e inserta un único nodo
- Genera `trace.jsonl` con **87 eventos** que Manim anima

**CMakeLists.txt** — Configuración para compilar:
- Funciona en Windows (Visual Studio), Linux (g++), Mac (clang)

---

### ✅ Listo (Alexander)

**erase.cpp** — Eliminación:
- [X] Buscar la clave
- [X] Si es una hoja: borrar y listo
- [X] Si tiene un hijo: reemplazarla con ese hijo
- [X] Si tiene dos hijos: rotar hacia abajo hasta que sea hoja, luego borrar
- [X] Usar `emit()` para cada movimiento
- [X] Reutiliza `rotateLeft` / `rotateRight` declaradas en `treap.h` (no las reescribe)

Verificado: el árbol conserva la propiedad BST **y** la de heap después de cada eliminación,
incluido el borrado de la raíz y el borrado de una clave inexistente.

---

### Listo (Benjamín)

**Animación con Manim** — `animation/render_treap.py`, renderizado y unido:
- [X] Leer `trace.jsonl` línea por línea
- [X] Para cada evento: animar la transición (nodos se mueven, aparecen, desaparecen)
- [X] Resaltar el nodo que está siendo manipulado (`highlighted_id` → borde amarillo)
- [X] Mostrar el texto del evento (`note`) como subtítulo
- [X] Renderizar y exportar a video .mp4 de alta calidad (1920x1080, 60 fps)
- [X] Unir las 4 escenas con ffmpeg → `video_final.mp4` (1:05)

**Video Educativo** (requisitos del enunciado):
El video debe tener **1-2 minutos de duración** (máximo 5). Necesita:

1. **Introducción** (20-30 s pedidos) → escena `Intro`, **5.0 s reales** ✅
   - Qué es un Treap, por qué existe
   - Ventaja: O(log n) sin complejidad de rebalanceo explícito

2. **Demo de Inserción** (40 s pedidos) → `TreapScene` Fase 1, **17.6 s reales** ✅
   - Mostrar cómo crece el árbol
   - Resaltar las rotaciones cuando suben nodos por prioridad

3. **Demo de Búsqueda** (20 s pedidos) → `TreapScene` Fase 2, **8.2 s reales** ✅
   - Mostrar el camino de búsqueda (izquierda/derecha)
   - *(la Fase 3, eliminación, añade 12.1 s más)*

4. **Caso Borde** (15 s pedidos) → `TreapScene` Fase 4, **9.9 s reales** ✅
   - Árbol vacío, búsqueda en árbol vacío, un solo elemento

5. **Análisis de Complejidad** (15 s pedidos) → escena `Complejidad`, **7.0 s reales** ✅
   - Treap: O(log n) esperado
   - BST normal: O(n) peor caso
   - Por qué la aleatoriedad ayuda

6. **Créditos** (10 s pedidos) → escena `Creditos`, **4.0 s reales** ✅
   - Título: "Treap — Árbol Binario Equilibrado por Suerte"
   - Nombres de los 3 integrantes

> Las secciones salen más cortas que lo sugerido por el enunciado, pero el total
> (**1:05**) cae dentro del rango de 1-2 minutos exigido. Para alargarlas, sube
> `DURACION` en `render_treap.py` (animación del árbol) o los `self.wait()` de
> `Intro`, `Complejidad` y `Creditos`.

**Informe PDF** (requisitos del enunciado):
- Carátula: curso, nombres, fecha, estructura
- Explicación del TDA (qué es, para qué sirve)
- Herramientas usadas (C++17, CMake, Manim Community, ffmpeg)
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
- Compilador C++ que entienda C++17 (g++, clang, MSVC)
- CMake 3.10 o más nuevo *(opcional: abajo está el comando directo sin CMake)*
- Para la animación: Python 3, Manim Community y ffmpeg

### Opción A — Sin CMake (lo más rápido, Linux/Mac)

```bash
cd Treap
clang++ -std=c++17 -Iinclude -Wall -Wextra -Wpedantic \
  src/main.cpp src/treap/*.cpp -o treap_demo
./treap_demo
```

En Linux cambia `clang++` por `g++`. En VS Code está la tarea **"Compilar Treap"**
(`Cmd+Shift+B`), que corre exactamente este comando.

### Opción B — Con CMake (Linux o Mac)

```bash
cd Treap
cmake -S . -B build
cmake --build build
./build/treap_demo          # ojo: genera trace.jsonl dentro de build/
```

### Opción C — Con CMake (Windows, Visual Studio)

```bash
cd Treap
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
.\build\Release\treap_demo.exe
```

### Qué pasa cuando lo ejecutas:

```
 Treap: Inserción, Búsqueda y Eliminación 
Generando trace.jsonl para animación Manim...

 Fase 1: Inserción 
Insertando 50
Insertando 30
... (8 inserciones totales)

 Fase 2: Búsquedas 
Buscando 60
  Encontrado
Buscando 99
  No encontrado
Buscando 20
  Encontrado

 Fase 3: Eliminación 
Eliminando 20
Eliminando 70
Eliminando 50
Eliminando 99

 Fase 4: Caso borde 
Vaciando: eliminando 10
... (5 eliminaciones hasta vaciar el árbol)
Buscando 50 en el árbol vacío
  No encontrado (árbol vacío)
Insertando 42 como único nodo

 Archivo trace.jsonl generado exitosamente.
  Para animar: manim -pqh animation/render_treap.py TreapScene
```

**Resultado**: crea `trace.jsonl` con **87 eventos** que describen todo lo que pasó
(inserciones, comparaciones, rotaciones, búsquedas, eliminaciones).

---

## Cómo Generar la Animación

### 1. Instalar dependencias (una sola vez)

```bash
# macOS
brew install ffmpeg pango pkg-config py3cairo
pip3 install manim

# Verificar
manim --version && ffmpeg -version | head -1
```

### 2. Generar la traza y renderizar

```bash
./treap_demo                                        # genera trace.jsonl
manim -pqh animation/render_treap.py TreapScene     # anima (1080p60)
```

- `-q h` = alta calidad (1080p60), **lo que hay que entregar**
- `-p` = abre el video al terminar
- Mientras ajustas cosas, usa `-pql`: renderiza en segundos, pero sale en
  **480p a 15 fps**. Sirve para revisar la lógica, no para entregar — si el
  vídeo se ve pixelado o a tirones, revisa que no estés mirando el de `-ql`.
- `--disable_caching` fuerza a re-renderizar todo tras editar el script; sin
  esto Manim reutiliza fragmentos viejos y parece que tus cambios no surten efecto

El resultado sale en `media/videos/render_treap/1080p60/TreapScene.mp4`.

### 3. Renderizar las 4 escenas y unirlas

```bash
manim -qh animation/render_treap.py Intro TreapScene Complejidad Creditos

cd media/videos/render_treap/1080p60
printf "file 'Intro.mp4'\nfile 'TreapScene.mp4'\nfile 'Complejidad.mp4'\nfile 'Creditos.mp4'\n" > lista.txt
ffmpeg -f concat -safe 0 -i lista.txt -c copy video_final.mp4
```

**Duración real**: 48.9 s de animación del árbol + intro (5 s) + complejidad (7 s)
+ créditos (4 s) = **1:05**, dentro del rango de 1-2 minutos que pide el enunciado.
Si lo quieres más pausado, sube `DURACION` en `animation/render_treap.py`.

El resultado queda en `media/videos/render_treap/1080p60/video_final.mp4`
(1920x1080, 60 fps, H.264, ~4 MB). `media/` está en `.gitignore`: sube el vídeo a
Drive o YouTube no listado y pon el enlace en el informe.

---

## Quién Hace Qué

| Persona        | Responsabilidad             | Archivos |
|----------------|-----------------------------|----------|
| **Denilson**   | Infraestructura + Inserción | `treap.h`, `treap_core.cpp`, `insert.cpp`, `main.cpp` ✅ |
| **Alexander**  | Eliminación                 | `erase.cpp` ✅ |
| **Benjamín**   | Manim + Video + Informe PDF | `render_treap.py` ✅ · `video_final.mp4` ✅ · `informe.pdf` 🚧 |

---

## Detalles Técnicos

### ¿Por qué funciona?

La aleatoriedad es la clave. Si todas las prioridades fueran 1,2,3,...,n (orden creciente), el árbol degeneraría en una lista y sería O(n). Pero como son **aleatorias**, con alta probabilidad el árbol queda equilibrado a O(log n) de profundidad.

### ¿Qué es `emit()`?

Cada vez que algo importante ocurre (insertamos un nodo, lo rotamos, lo buscamos), llamamos a `emit()` que dice:
- Qué pasó (`event`: `"insert_leaf"`, `"rotate_right_before"`, `"search_found"`, etc.)
- Descripción amigable (`note`: `"Nuevo nodo: key=50, priority=770"`)
- Qué nodo resaltar en la animación (`highlighted_id`, o `-1` si ninguno)
- **Foto actual del árbol** (`snapshot`: JSON con todos los nodos y sus conexiones)

Esto se escribe a `trace.jsonl`, una línea por evento. Manim lee esto y anima las transiciones.

### Catálogo de eventos

Los **17** tipos de evento que emite la implementación. **Las rotaciones emiten dos
eventos** (`_before` y `_after`), no uno: eso es lo que permite animar el giro en dos
tiempos. En la corrida de la demo aparecen 16 de los 17: `insert_duplicate` solo se
dispara si insertas una clave que ya existe, y `main.cpp` no lo hace.

| Evento | Cuándo | `highlighted_id` |
|---|---|---|
| `insert_compare` | se compara la clave contra un nodo | ese nodo |
| `insert_leaf` | se crea el nodo nuevo | el nodo nuevo |
| `insert_duplicate` | la clave ya existía | el nodo existente |
| `rotate_left_before` / `rotate_left_after` | giro a la izquierda | pivote antes / después |
| `rotate_right_before` / `rotate_right_after` | giro a la derecha | pivote antes / después |
| `search_compare` | se compara durante una búsqueda | ese nodo |
| `search_found` | la clave existe | el nodo hallado |
| `search_not_found` | se llegó a un `nullptr` | `-1` |
| `erase_compare` | se baja buscando la clave a borrar | ese nodo |
| `erase_found` | la clave a borrar fue hallada | ese nodo |
| `erase_leaf_before` / `erase_leaf_after` | se borra una hoja | la hoja / `-1` |
| `erase_replace_before` / `erase_replace_after` | nodo con un solo hijo | el nodo / el hijo |
| `erase_not_found` | la clave no existía | `-1` |

### ¿Qué es `trace.jsonl`?

Un archivo de texto con una línea JSON por evento. Estas son las 3 primeras líneas reales
de una corrida:

```json
{"event":"insert_leaf","note":"Nuevo nodo: key=50, priority=770","highlighted_id":1,"snapshot":{"1":{"key":50,"priority":770,"left":-1,"right":-1}}}
{"event":"insert_compare","note":"¿30 en qué lado de 50?","highlighted_id":1,"snapshot":{"1":{"key":50,"priority":770,"left":-1,"right":-1}}}
{"event":"insert_leaf","note":"Nuevo nodo: key=30, priority=752","highlighted_id":2,"snapshot":{"1":{"key":50,"priority":770,"left":2,"right":-1},"2":{"key":30,"priority":752,"left":-1,"right":-1}}}
```

Detalles del formato que importan para el script de Manim:

- Las claves de `snapshot` son **strings** (`"1"`), pero `left` / `right` son **enteros**.
- `left: -1` / `right: -1` significan "sin hijo".
- Cuando el árbol está vacío, `snapshot` es `{}` (pasa 2 veces en la Fase 4).
- El snapshot **no marca cuál es la raíz**: es el único id que no aparece como hijo de
  nadie. Eso hace `buscar_raiz()` en `render_treap.py`.

Manim procesa esto línea por línea y genera las animaciones.

### Trampas de Manim que ya nos costaron un render

Si tocas `render_treap.py`, ten presente esto — cada punto corresponde a un bug real
que hubo que corregir porque el vídeo salía roto:

1. **Nunca animes un `VGroup` y uno de sus hijos en el mismo `self.play()`.**
   Cada nodo es `VGroup(círculo, clave, prioridad)`. Hacer
   `grupo.animate.move_to(...)` junto a `grupo[0].animate.set_fill(...)` provoca que
   una animación pise a la otra: el círculo se queda atrás y la clave viaja sola.
   Por eso el resaltado se aplica **fuera** del `play()` y sin `.animate`.

2. **`move_to()` centra el `VGroup` completo, etiqueta `p=` incluida.**
   Para que el *círculo* quede en el punto calculado hay que usar
   `shift(punto - grupo[0].get_center())`. Lo mismo para las aristas: se trazan entre
   `nodos[x][0].get_center()`, el centro del círculo, no el del grupo.

3. **`Transform` entre dos `Text` distintos hace un morph carácter a carácter** que en
   vídeo se lee como texto doble y borroso. Para el subtítulo usamos `become()`, que
   lo cambia de golpe.

4. **Nada de texto negro.** El fondo de Manim es negro: si un `Text(color=BLACK)` se
   sale de su círculo, desaparece. Las claves van en blanco sobre relleno oscuro, y el
   resaltado cambia el **borde** (no el relleno) para no perder contraste.

5. **`always_redraw` para las aristas.** Se recalculan en cada frame desde la posición
   actual de los nodos, así quedan pegadas a los círculos durante una rotación. Con
   líneas estáticas se despegan a mitad de cada animación.

6. **Usa `--disable_caching` después de editar el script**, o Manim reutiliza fragmentos
   ya renderizados y parece que tus cambios no hacen nada.

---

## Checklist Antes de Gradescope

### Código
- [X] Compila sin errores ni warnings (verificado con `-Wall -Wextra -Wpedantic`)
- [X] `trace.jsonl` se genera correctamente (87 líneas, todas JSON válido)
- [X] Se ejecuta sin crashes
- [X] Las 3 partes integradas en `main.cpp`
- [ ] Repositorio GitHub actualizado
- [X] README.md con instrucciones funcionales

### Video
- [X] Duración: 1-2 minutos (máx 5) — **1:05**
- [X] Incluye intro conceptual
- [X] Muestra inserción con rotaciones
- [X] Muestra búsqueda
- [X] Muestra eliminación
- [X] Incluye caso borde (árbol vacío / un solo elemento)
- [X] Incluye análisis de complejidad
- [X] Tiene créditos con nombres
- [X] Formato: .mp4 alta resolución (1920x1080 @ 60 fps, H.264)
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
- `render_treap.py` **no implementa ningún treap**: solo lee los snapshots y los dibuja.
  No decide rotaciones, no ordena claves, no calcula prioridades. Toda la lógica vive en C++.

**No permitido**:
- Animar valores ficticios
- Usar una implementación de terceros (stdlib, librería)
- Falsificar los eventos

---

**Documentación actualizada: 2026-09-26** — código, animación y vídeo verificados.
