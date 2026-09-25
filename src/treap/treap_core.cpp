#include "../../include/treap/treap.h"
#include <fstream>
#include <sstream>
#include <functional>
#include <ctime>
#include <random>

using namespace std;

Node* root = nullptr;
int node_counter = 1;

string snapshotNodes() {
    stringstream ss;
    ss << "{";

    if (root == nullptr) {
        ss << "}";
        return ss.str();
    }

    // Recorrer todo el árbol y guardar cada nodo en formato JSON
    function<void(Node*)> traverse = [&](Node* node) {
        if (node == nullptr) return;

        ss << "\"" << node->id << "\":{";
        ss << "\"key\":" << node->key << ",";
        ss << "\"priority\":" << node->priority << ",";
        ss << "\"left\":" << (node->left ? node->left->id : -1) << ",";
        ss << "\"right\":" << (node->right ? node->right->id : -1);
        ss << "},";

        if (node->left) traverse(node->left);
        if (node->right) traverse(node->right);
    };

    traverse(root);

    string result = ss.str();
    if (result.back() == ',') result.pop_back();  // Quitar la última coma
    result += "}";

    return result;
}

void emit(const string& event, const string& note, int highlighted_id) {
    static ofstream trace_file("trace.jsonl", ios::app);

    // Capturar el estado actual del árbol
    string snapshot = snapshotNodes();

    // Armar la línea JSON con el evento, descripción y snapshot
    string json_line = "{";
    json_line += "\"event\":\"" + event + "\",";
    json_line += "\"note\":\"" + note + "\",";
    json_line += "\"highlighted_id\":" + to_string(highlighted_id) + ",";
    json_line += "\"snapshot\":" + snapshot;
    json_line += "}";

    // Escribir la línea en el archivo (una línea por evento)
    trace_file << json_line << "\n";
    trace_file.flush();
}
