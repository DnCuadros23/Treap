#include "../../include/treap/treap.h"

using namespace std;

namespace {
Node* eraseNode(Node* node, int key, bool found) {
    if (node == nullptr) {
        emit("erase_not_found", "No se pudo eliminar: " + to_string(key) + " no existe", -1);
        return nullptr;
    }

    if (key < node->key) {
        emit("erase_compare", "Buscando " + to_string(key) + " a la izquierda de " + to_string(node->key), node->id);
        node->left = eraseNode(node->left, key, found);
        return node;
    }

    if (key > node->key) {
        emit("erase_compare", "Buscando " + to_string(key) + " a la derecha de " + to_string(node->key), node->id);
        node->right = eraseNode(node->right, key, found);
        return node;
    }

    if (!found) {
        emit("erase_found", "Clave " + to_string(key) + " encontrada", node->id);
    }

    if (node->left == nullptr && node->right == nullptr) {
        int id = node->id;
        emit("erase_leaf", "Eliminando la hoja " + to_string(key), id);
        delete node;
        return nullptr;
    }

    if (node->left == nullptr) {
        node = rotateLeft(node);
        node->left = eraseNode(node->left, key, true);
        return node;
    }

    if (node->right == nullptr) {
        node = rotateRight(node);
        node->right = eraseNode(node->right, key, true);
        return node;
    }

    if (node->left->priority > node->right->priority) {
        node = rotateRight(node);
        node->right = eraseNode(node->right, key, true);
    } else {
        node = rotateLeft(node);
        node->left = eraseNode(node->left, key, true);
    }

    return node;
}
}

Node* erase(Node* node, int key) {
    return eraseNode(node, key, false);
}
