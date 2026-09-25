#include "../../include/treap/treap.h"
#include <random>

using namespace std;

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

namespace {
mt19937 generator(20260925u);
uniform_int_distribution<int> priority_distribution(1, 1000000000);

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

void insertAt(Node*& node, int key) {
    if (node == nullptr) {
        int priority = priority_distribution(generator);
        node = new Node(node_counter++, key, priority);
        emit("insert_leaf", "Nuevo nodo: key=" + to_string(key) + ", priority=" + to_string(priority), node->id);
        return;
    }

    emit("insert_compare", "¿" + to_string(key) + " en qué lado de " + to_string(node->key) + "?", node->id);

    if (key < node->key) {
        insertAt(node->left, key);
        if (node->left->priority > node->priority) {
            rotateRightAt(node);
        }
    } else if (key > node->key) {
        insertAt(node->right, key);
        if (node->right->priority > node->priority) {
            rotateLeftAt(node);
        }
    } else {
        emit("insert_duplicate", "Key " + to_string(key) + " ya está en el árbol", node->id);
    }
}
}

Node* insert(Node* node, int key) {
    root = node;
    insertAt(root, key);
    return root;
}
