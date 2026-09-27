# Guion del Video — Treap

**Proyecto**: CS2023 "Anima tu Estructura de Datos" (UTEC)
**Duración objetivo**: 1:51 · **264 palabras** a 150 palabras/minuto
**Integrantes**: Denilson · Alexander · Benjamín

---

## Antes de grabar: ajustar la duración del video

El video renderizado actualmente dura **1:05**, que a ritmo de narración clara son unas
160 palabras — no alcanza para que hablen tres personas. Hay que alargarlo a ~1:51.

Dos cambios en `animation/render_treap.py`:

```python
DURACION = 0.85          # línea 20, estaba en 0.55
```

```python
# Intro.construct()        →  self.wait(2)  pasa a  self.wait(13)
# Complejidad.construct()  →  self.wait(2)  pasa a  self.wait(11)
# Creditos.construct()     →  self.wait(3)  pasa a  self.wait(7)
```

Luego re-renderizar y concatenar:

```bash
manim -qh --disable_caching animation/render_treap.py Intro TreapScene Complejidad Creditos

cd media/videos/render_treap/1080p60
printf "file 'Intro.mp4'\nfile 'TreapScene.mp4'\nfile 'Complejidad.mp4'\nfile 'Creditos.mp4'\n" > lista.txt
ffmpeg -f concat -safe 0 -i lista.txt -c copy video_final.mp4
```

---

## Reparto

Cada uno narra lo que implementó — es lo que el informe pide justificar como contribución
de cada integrante.

| Persona | Bloques | Tiempo | Parte del proyecto |
|---|---|---|---|
| **Denilson** | Intro + Inserción | 42.7 s (38%) | `treap_core.cpp`, `insert.cpp` |
| **Benjamín** | Búsqueda + Complejidad + Cierre | 35.2 s (31%) | `search.cpp`, Manim, video |
| **Alexander** | Eliminación + Caso borde | 34.0 s (30%) | `erase.cpp` |

### Tiempos por bloque

| # | Bloque | Quién | Palabras | Necesita | Tiene | Margen |
|---|---|---|---:|---:|---:|---:|
| 1 | Intro | Denilson | 38 | 15.2 s | 15.5 s | +0.3 s |
| 2 | Inserción | Denilson | 68 | 27.2 s | 27.2 s | 0.0 s |
| 3 | Búsqueda | Benjamín | 32 | 12.8 s | 12.8 s | −0.1 s |
| 4 | Eliminación | Alexander | 41 | 16.4 s | 18.7 s | +2.3 s |
| 5 | Caso borde | Alexander | 35 | 14.0 s | 15.3 s | +1.3 s |
| 6 | Complejidad | Benjamín | 35 | 14.0 s | 14.5 s | +0.5 s |
| 7 | Cierre | Benjamín | 15 | 6.0 s | 8.0 s | +2.0 s |
| | **TOTAL** | | **264** | **105.6 s** | **112.0 s** | |

---

## 1 · Introducción — DENILSON
**0:00 – 0:15** · *En pantalla: título "Treap" y las dos líneas de key/priority*

> Un árbol binario de búsqueda es rapidísimo… hasta que los datos llegan ordenados.
> Ahí degenera en una lista y todo cuesta O de n.
> Un AVL lo arregla con reglas estrictas. El treap, con algo más simple: azar.

---

## 2 · Inserción — DENILSON
**0:15 – 0:42** · *En pantalla: se insertan 50, 30, 70, 20, 40, 60, 80, 10 con sus rotaciones*

> Cada nodo guarda dos cosas: su clave, que mantiene el orden del BST, y una prioridad
> aleatoria, que mantiene la propiedad de montículo.
>
> Al insertar bajamos comparando claves. Pero si el nodo nuevo saca más prioridad que su
> padre, rota y sube.
>
> El cuarenta llegó quinto, sacó la prioridad más alta de las ocho, y subió hasta la raíz.
> No mandó el orden de llegada: mandó el sorteo.

**Sincronización**: "rota y sube" debe caer sobre la primera rotación. La frase del cuarenta
va al final del bloque, cuando el árbol ya está completo y se ve que quedó en la raíz.

---

## 3 · Búsqueda — BENJAMÍN
**0:42 – 0:55** · *En pantalla: se buscan 60, 99 y 20*

> Buscar es igual que en un BST: comparas la clave y bajas a izquierda o derecha.
> Las prioridades no intervienen.
> Buscamos noventa y nueve, llegamos a un nodo vacío, y no existe.

**Cuidado**: es el bloque más apretado del guion (−0.1 s). Sin pausas largas en medio.

---

## 4 · Eliminación — ALEXANDER
**0:55 – 1:14** · *En pantalla: se eliminan 20, 70, 50 y 99*

> Para eliminar no buscamos un sucesor. Rotamos el nodo hacia abajo: sube el hijo de mayor
> prioridad, y el nodo a borrar baja un nivel. Repetimos hasta volverlo hoja, y ahí lo
> borramos.
>
> Son las mismas rotaciones de la inserción, reutilizadas.

**Por qué importa la última frase**: es tu contribución real. `erase.cpp` reutiliza
`rotateLeft` / `rotateRight` declaradas en `treap.h` en vez de reescribirlas, que es
justo lo que pedía el reparto de trabajo. Tienes 2.3 s de margen en este bloque.

---

## 5 · Caso borde — ALEXANDER
**1:14 – 1:29** · *En pantalla: el árbol se vacía, búsqueda fallida, y se inserta el 42*

> Los casos límite también salen del código real. Vaciamos el árbol entero.
> Buscar en un árbol vacío responde "no encontrado", sin romperse.
> Insertamos una clave y el treap arranca otra vez, con un solo nodo.

---

## 6 · Análisis de complejidad — BENJAMÍN
**1:29 – 1:43** · *En pantalla: escena `Complejidad`*

> La forma del treap depende solo de las prioridades, nunca del orden de llegada.
> Como son aleatorias, equivale a insertar en orden aleatorio: altura esperada O de log n.
> El mismo análisis del quicksort aleatorizado.

**Si alguien pregunta en la sustentación**: el peor caso sigue siendo O(n), pero la
probabilidad es despreciable. Y el azar está en el programa, no en los datos — por eso
nadie puede forzar el peor caso eligiendo qué insertar, cosa que con un BST normal sí
se puede (basta darle los datos ordenados).

---

## 7 · Cierre y créditos — BENJAMÍN
**1:43 – 1:51** · *En pantalla: escena `Creditos`*

> Nada está simulado: cada fotograma sale del archivo de traza que emite nuestro código.
> Gracias.

**Por qué importa**: responde directo al requisito del enunciado de que la animación esté
impulsada por una implementación real y no hecha "a mano". No la quites.

---

## Notas de grabación

- **Ritmo**: 150 palabras por minuto ya es pausado. Si al ensayar te quedas corto de
  tiempo, el problema es el ritmo, no el texto. Cronometra tu bloque solo antes de grabar.
- **Dónde respirar**: los bloques 4 y 7 son los que tienen holgura (+2.3 s y +2.0 s).
- **Graba el audio por separado** y móntalo sobre el video ya renderizado. Narrar en vivo
  contra la animación obliga a repetir el render completo cada vez que alguien se traba.
- **Si hay que identificar a cada quien**, pon un rótulo con el nombre al entrar cada
  bloque. Se hace en el montaje, sin tocar Manim.
