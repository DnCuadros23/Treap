#ifndef TREAP_H
#define TREAP_H

#include <string>
#include <memory>

struct Node {
    int id;           // Identificador único para tracking en animación
    int key;          // Valor para mantener propiedad BST
    int priority;     // Prioridad aleatoria para mantener propiedad Heap
    Node* left;
    Node* right;

    Node(int id, int key, int priority)
        : id(id), key(key), priority(priority), left(nullptr), right(nullptr) {}
};

// Variables globales
extern Node* root;
extern int node_counter;

using namespace std;

// Registra un evento en trace.jsonl para que Manim lo pueda animar después
// event: qué operación ocurrió (insert, rotate, search, etc.)
// note: explicación en texto de lo que está pasando
// highlighted_id: qué nodo resaltar en la animación (o -1 si ninguno)
void emit(const string& event, const string& note, int highlighted_id = -1);
void resetTrace();

// Toma una "foto" del árbol actual en formato JSON
// Esto es lo que Manim va a leer para saber cómo se ve el árbol en cada momento
string snapshotNodes();

// Rotaciones (mantienen propiedad BST, reacomodan por prioridad Heap)
Node* rotateRight(Node* y);
Node* rotateLeft(Node* x);

// Operaciones principales
Node* insert(Node* node, int key);
bool search(Node* node, int key);
Node* erase(Node* node, int key);

#endif
