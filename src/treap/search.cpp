#include "../../include/treap/treap.h"

using namespace std;

bool search(Node* node, int key) {
    if (node == nullptr) {
        // Llegamos a un nodo vacío: la clave no existe
        emit("search_not_found", "No encontrado: " + to_string(key) + " no está aquí", -1);
        return false;
    }

    // Comparar la clave buscada con la del nodo actual
    emit("search_compare", "¿Es " + to_string(key) + " igual a " + to_string(node->key) + "?", node->id);

    if (key == node->key) {
        // ¡Encontrado!
        emit("search_found", "¡Encontrado! " + to_string(key) + " está aquí", node->id);
        return true;
    } else if (key < node->key) {
        // Buscar a la izquierda
        return search(node->left, key);
    } else {
        // Buscar a la derecha
        return search(node->right, key);
    }
}
