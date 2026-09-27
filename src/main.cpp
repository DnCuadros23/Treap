#include "treap/treap.h"
#include <iostream>

using namespace std;
int main() {
    resetTrace();
    cout << " Treap: Inserción, Búsqueda y Eliminación " << endl;
    cout << "Generando trace.jsonl para animación Manim..." << endl;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 10};

    cout << "\n Fase 1: Inserción " << endl;
    for (int val : values) {
        cout << "Insertando " << val << endl;
        root = insert(root, val);
    }

    cout << "\n Fase 2: Búsquedas " << endl;
    int search_keys[] = {60, 99, 20};
    for (int key : search_keys) {
        cout << "Buscando " << key << endl;
        bool found = search(root, key);
        if (found) {
            cout << "  Encontrado" << endl;
        } else {
            cout << "  No encontrado" << endl;
        }
    }

    // Sin search() de por medio: cada búsqueda extra ensucia la traza que anima Manim
    cout << "\n Fase 3: Eliminación " << endl;
    int erase_keys[] = {20, 70, 50, 99};
    for (int key : erase_keys) {
        cout << "Eliminando " << key << endl;
        root = erase(root, key);
    }

    // Caso borde exigido por el enunciado: vaciar el árbol por completo y
    // reconstruirlo desde cero, para que la animación lo muestre de verdad
    cout << "\n Fase 4: Caso borde " << endl;
    int remaining[] = {10, 30, 40, 60, 80};
    for (int key : remaining) {
        cout << "Vaciando: eliminando " << key << endl;
        root = erase(root, key);
    }

    cout << "Buscando 50 en el árbol vacío" << endl;
    if (search(root, 50)) {
        cout << "  Encontrado" << endl;
    } else {
        cout << "  No encontrado (árbol vacío)" << endl;
    }

    cout << "Insertando 42 como único nodo" << endl;
    root = insert(root, 42);

    cout << "\n Archivo trace.jsonl generado exitosamente." << endl;
    cout << "  Para animar: manim -pqh animation/render_treap.py TreapScene" << endl;

    return 0;
}
