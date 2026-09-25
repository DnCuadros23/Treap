#include "treap/treap.h"
#include <iostream>

using namespace std;
int main() {
    resetTrace();
    cout << " Treap: Inserción y Búsqueda " << endl;
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

    cout << "\n Archivo trace.jsonl generado exitosamente." << endl;
    cout << "  Para animar: python3 animation/render_treap.py" << endl;

    return 0;
}
