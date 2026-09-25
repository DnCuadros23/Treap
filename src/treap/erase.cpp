#include "../../include/treap/treap.h"

using namespace std;

Node* erase(Node* node, int key) {
    if (node == nullptr) {
        // No encontramos la clave
        emit("erase_not_found", "No se pudo eliminar: " + to_string(key) + " no existe", -1);
        return nullptr;
    }

    if (key < node->key) {
        // Buscar a la izquierda
        node->left = erase(node->left, key);
    } else if (key > node->key) {
        // Buscar a la derecha
        node->right = erase(node->right, key);
    } else {
        // Encontramos el nodo a eliminar, pero Persona B lo implementará
        emit("erase_not_implemented", "Eliminación en progreso (Persona B)", node->id);
        return node;
    }

    return node;
}
