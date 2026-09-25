#include "../../include/treap/treap.h"
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

Node* rotateRight(Node* y) {
    // Rotación derecha: el hijo izquierdo sube y se convierte en padre
    Node* x = y->left;

    emit("rotate_right_before", "Girando derecha en nodo " + to_string(y->key), y->id);

    y->left = x->right;
    x->right = y;

    emit("rotate_right_after", "Giro completo: " + to_string(x->key) + " ahora es padre", x->id);

    return x;
}

Node* rotateLeft(Node* x) {
    // Rotación izquierda: el hijo derecho sube y se convierte en padre
    Node* y = x->right;

    emit("rotate_left_before", "Girando izquierda en nodo " + to_string(x->key), x->id);

    x->right = y->left;
    y->left = x;

    emit("rotate_left_after", "Giro completo: " + to_string(y->key) + " ahora es padre", y->id);

    return y;
}

Node* insert(Node* node, int key) {
    if (node == nullptr) {
        // Nodo nuevo: generar una prioridad aleatoria
        static mt19937 gen(time(nullptr) + rand());
        static uniform_int_distribution<> dis(1, 1000);

        int priority = dis(gen);
        Node* new_node = new Node(node_counter++, key, priority);

        emit("insert_leaf", "Nuevo nodo: key=" + to_string(key) + ", priority=" + to_string(priority), new_node->id);

        return new_node;
    }

    emit("insert_compare", "¿" + to_string(key) + " en qué lado de " + to_string(node->key) + "?", node->id);

    if (key < node->key) {
        // Ir a la izquierda e insertar recursivamente
        node->left = insert(node->left, key);

        // Si el hijo izquierdo tiene prioridad más alta, rotar derecha para subirlo
        if (node->left->priority > node->priority) {
            node = rotateRight(node);
        }
    } else if (key > node->key) {
        // Ir a la derecha e insertar recursivamente
        node->right = insert(node->right, key);

        // Si el hijo derecho tiene prioridad más alta, rotar izquierda para subirlo
        if (node->right->priority > node->priority) {
            node = rotateLeft(node);
        }
    } else {
        // Ya existe, no insertar duplicados
        emit("insert_duplicate", "Key " + to_string(key) + " ya está en el árbol", node->id);
    }

    return node;
}
