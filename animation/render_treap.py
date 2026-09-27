"""Anima el treap a partir de trace.jsonl.

La animación está impulsada por la implementación real en C++: cada evento de
trace.jsonl fue emitido por insert.cpp / search.cpp / erase.cpp mediante emit().
Aquí no se simula ninguna estructura, solo se dibuja lo que el C++ reportó.

Uso:
    ./treap_demo                                          # genera trace.jsonl
    manim -pqh animation/render_treap.py TreapScene       # anima
"""

from manim import *
import json
import numpy as np
from pathlib import Path

ESPACIADO_X = 1.4
ESPACIADO_Y = 1.1
RADIO = 0.32
DURACION = 0.55


def buscar_trace():
    """trace.jsonl se genera donde se ejecuta el binario: probamos raíz y build/."""
    aqui = Path(__file__).resolve().parent
    for ruta in (aqui.parent / "trace.jsonl", aqui.parent / "build" / "trace.jsonl"):
        if ruta.exists():
            return ruta
    raise FileNotFoundError(
        "No encontré trace.jsonl. Compila y corre ./treap_demo desde la raíz del repo."
    )


def cargar_eventos():
    with open(buscar_trace(), encoding="utf-8") as f:
        return [json.loads(linea) for linea in f if linea.strip()]


def buscar_raiz(snap):
    """El snapshot no marca cuál es la raíz: es el único id que no es hijo de nadie."""
    if not snap:
        return None
    hijos = set()
    for nodo in snap.values():
        for lado in ("left", "right"):
            if nodo[lado] != -1:
                hijos.add(nodo[lado])
    for nid in snap:
        if int(nid) not in hijos:
            return int(nid)
    return None


def calcular_posiciones(snap):
    """Recorrido in-orden: la columna es el orden de visita, la fila la profundidad.

    Usar el orden in-orden (y no la posición binaria) evita que las ramas se
    pisen cuando el árbol queda desbalanceado.
    """
    pos, contador = {}, [0]

    def recorrer(nid, prof):
        if nid == -1 or nid is None:
            return
        nodo = snap[str(nid)]
        recorrer(nodo["left"], prof + 1)
        pos[nid] = (contador[0], prof)
        contador[0] += 1
        recorrer(nodo["right"], prof + 1)

    recorrer(buscar_raiz(snap), 0)
    return pos


def a_pantalla(pos):
    """Convierte (columna, profundidad) en coordenadas de Manim, centrado."""
    if not pos:
        return {}
    columnas = [c for c, _ in pos.values()]
    centro = (min(columnas) + max(columnas)) / 2
    return {
        nid: np.array([(c - centro) * ESPACIADO_X, 1.8 - p * ESPACIADO_Y, 0])
        for nid, (c, p) in pos.items()
    }


class TreapScene(Scene):
    """Reproduce trace.jsonl evento por evento."""

    def construct(self):
        self.nodos = {}      # id -> VGroup(círculo, clave, prioridad)
        self.enlaces = []    # lista de (id_padre, id_hijo)

        titulo = Text("Treap — Árbol Binario Equilibrado por Suerte", font_size=28)
        titulo.to_edge(UP)
        subtitulo = Text("", font_size=22).to_edge(DOWN)

        # always_redraw: las aristas se recalculan en cada frame a partir de la
        # posición actual de los nodos, así quedan pegadas a los círculos
        # mientras estos se desplazan durante una rotación.
        aristas = always_redraw(self.dibujar_aristas)

        self.add(titulo, aristas, subtitulo)  # aristas primero = quedan detrás

        for evento in cargar_eventos():
            self.mostrar_evento(evento, subtitulo)

        self.wait(1)

    def dibujar_aristas(self):
        grupo = VGroup()
        for padre, hijo in self.enlaces:
            if padre in self.nodos and hijo in self.nodos:
                grupo.add(Line(
                    self.nodos[padre][0].get_center(),
                    self.nodos[hijo][0].get_center(),
                    stroke_width=3,
                    color=GREY_B,
                ))
        return grupo

    def crear_nodo(self, datos):
        circulo = Circle(
            radius=RADIO,
            fill_opacity=1.0,
            fill_color=BLUE_E,
            stroke_color=BLUE_B,
            stroke_width=2,
        )
        # Blanco sobre relleno oscuro: si la clave se sale del círculo por
        # cualquier motivo, sigue siendo legible sobre el fondo negro.
        clave = Text(str(datos["key"]), font_size=20, color=WHITE).move_to(circulo)
        prioridad = Text(f"p={datos['priority']}", font_size=13, color=GREY_B)
        prioridad.next_to(circulo, UP, buff=0.06)
        return VGroup(circulo, clave, prioridad)

    def resaltar(self, mobj, activo):
        """Resalta por el borde, no por el relleno: así la clave blanca del
        interior mantiene su contraste en ambos estados."""
        if activo:
            mobj[0].set_stroke(YELLOW, width=6)
        else:
            mobj[0].set_stroke(BLUE_B, width=2)

    def mostrar_evento(self, evento, subtitulo):
        snap = evento["snapshot"]
        destacado = evento["highlighted_id"]  # -1 significa "ninguno"
        objetivo = a_pantalla(calcular_posiciones(snap))

        # Los enlaces se actualizan antes del play: always_redraw hace el resto
        self.enlaces = [
            (int(nid), datos[lado])
            for nid, datos in snap.items()
            for lado in ("left", "right")
            if datos[lado] != -1
        ]

        # El subtítulo cambia de golpe. Animarlo con Transform hace un morph
        # carácter a carácter que en vídeo se lee como texto doble y borroso.
        subtitulo.become(Text(evento["note"], font_size=22).to_edge(DOWN))

        # El resaltado se aplica FUERA del play y sin .animate: animar el
        # círculo (mobj[0]) a la vez que su VGroup padre hace que una animación
        # pise a la otra y el círculo se quede atrás, separado de su etiqueta.
        for nid, mobj in self.nodos.items():
            self.resaltar(mobj, nid == destacado)

        animaciones = []

        # Nodos que desaparecen (una eliminación)
        for nid in list(self.nodos):
            if nid not in objetivo:
                animaciones.append(FadeOut(self.nodos.pop(nid), scale=0.3))

        # Nodos que siguen ahí: se desplazan a su nueva posición.
        # shift y no move_to: move_to centraría el VGroup completo, que incluye
        # la etiqueta de prioridad, dejando el círculo fuera de su sitio.
        for nid, punto in objetivo.items():
            if nid in self.nodos:
                mobj = self.nodos[nid]
                animaciones.append(mobj.animate.shift(punto - mobj[0].get_center()))

        # Nodos nuevos: aparecen creciendo
        for nid, punto in objetivo.items():
            if nid not in self.nodos:
                nuevo = self.crear_nodo(snap[str(nid)])
                nuevo.shift(punto - nuevo[0].get_center())
                self.resaltar(nuevo, nid == destacado)
                self.nodos[nid] = nuevo
                animaciones.append(GrowFromCenter(nuevo))

        if animaciones:
            self.play(*animaciones, run_time=DURACION)
        else:
            self.wait(DURACION)


class Intro(Scene):
    """Sección 1 del video: qué es un Treap y por qué existe."""

    def construct(self):
        titulo = Text("Treap", font_size=72)
        sub = Text("BST + Heap con prioridades aleatorias", font_size=30)
        sub.next_to(titulo, DOWN, buff=0.4)
        idea = VGroup(
            Text("key      → mantiene el orden (BST)", font_size=26),
            Text("priority → mantiene el equilibrio (Heap)", font_size=26),
        ).arrange(DOWN, aligned_edge=LEFT, buff=0.3)
        idea.next_to(sub, DOWN, buff=0.7)

        self.play(Write(titulo))
        self.play(FadeIn(sub, shift=UP))
        self.play(FadeIn(idea, shift=UP))
        self.wait(2)


class Complejidad(Scene):
    """Sección 5 del video: análisis de complejidad."""

    def construct(self):
        titulo = Text("Complejidad", font_size=44).to_edge(UP)
        filas = VGroup(
            Text("Treap:       O(log n) esperado", font_size=32),
            Text("BST normal:  O(n) en el peor caso", font_size=32),
            Text("Espacio:     O(n)", font_size=32),
        ).arrange(DOWN, aligned_edge=LEFT, buff=0.45)

        cierre = Text(
            "La aleatoriedad de las prioridades evita el peor caso",
            font_size=26,
            color=YELLOW,
        )
        cierre.next_to(filas, DOWN, buff=0.8)

        self.play(FadeIn(titulo))
        self.play(Write(filas), run_time=3)
        self.play(FadeIn(cierre, shift=UP))
        self.wait(2)


class Creditos(Scene):
    """Sección 6 del video: créditos."""

    def construct(self):
        texto = VGroup(
            Text("Treap — Árbol Binario Equilibrado por Suerte", font_size=34),
            Text("Denilson · Alexander · Benjamín", font_size=26),
            Text("CS2023 — Anima tu Estructura de Datos — UTEC", font_size=22),
        ).arrange(DOWN, buff=0.45)

        self.play(FadeIn(texto, shift=UP))
        self.wait(3)
