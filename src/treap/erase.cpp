#include "../../include/treap/treap.h"

using namespace std;

namespace {
void rotateRightAt(Node*& node) {
    int old_root_key = node->key;
    emit("rotate_right_before", "Girando derecha en nodo " + to_string(old_root_key), node->id);
    node = rotateRight(node);
    emit("rotate_right_after", "Giro completo: " + to_string(node->key) + " ahora es padre", node->id);
}

void rotateLeftAt(Node*& node) {
    int old_root_key = node->key;
    emit("rotate_left_before", "Girando izquierda en nodo " + to_string(old_root_key), node->id);
    node = rotateLeft(node);
    emit("rotate_left_after", "Giro completo: " + to_string(node->key) + " ahora es padre", node->id);
}

void eraseAt(Node*& node, int key, bool found) {
    if (node == nullptr) {
        emit("erase_not_found", "No se pudo eliminar: " + to_string(key) + " no existe", -1);
        return;
    }

    if (key < node->key) {
        emit("erase_compare", "Buscando " + to_string(key) + " a la izquierda de " + to_string(node->key), node->id);
        eraseAt(node->left, key, found);
        return;
    }

    if (key > node->key) {
        emit("erase_compare", "Buscando " + to_string(key) + " a la derecha de " + to_string(node->key), node->id);
        eraseAt(node->right, key, found);
        return;
    }

    if (!found) {
        emit("erase_found", "Clave " + to_string(key) + " encontrada", node->id);
    }

    if (node->left == nullptr && node->right == nullptr) {
        Node* removed = node;
        emit("erase_leaf_before", "Eliminando la hoja " + to_string(key), removed->id);
        node = nullptr;
        delete removed;
        emit("erase_leaf_after", "Hoja " + to_string(key) + " eliminada", -1);
        return;
    }

    if (node->left == nullptr || node->right == nullptr) {
        Node* removed = node;
        Node* child = node->left ? node->left : node->right;
        emit("erase_replace_before", "Reemplazando " + to_string(key) + " por " + to_string(child->key), removed->id);
        node = child;
        delete removed;
        emit("erase_replace_after", "Reemplazo completo: " + to_string(child->key) + " ocupa su lugar", child->id);
        return;
    }

    if (node->left->priority > node->right->priority) {
        rotateRightAt(node);
        eraseAt(node->right, key, true);
    } else {
        rotateLeftAt(node);
        eraseAt(node->left, key, true);
    }
}
}

Node* erase(Node* node, int key) {
    root = node;
    eraseAt(root, key, false);
    return root;
}
