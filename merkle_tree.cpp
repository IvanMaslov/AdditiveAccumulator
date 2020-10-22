#include <stdexcept>
#include "sha256.h"
#include "merkle_tree.h"

const std::string merkle_tree::NIL = "";

const std::string merkle_tree::C0 = "\x01";
const std::string merkle_tree::C1 = "\x02";
const std::string merkle_tree::C2 = "\x03";

merkle_tree::merkle_tree() {
    root = nullptr;
    size = 0;
    capacity = 0;
}

std::string merkle_tree::get_root() {
    return root->hash;
}

size_t merkle_tree::get_size() {
    return size;
}

merkle_tree::merkle_tree(const std::vector<std::string> &items) {
    size = items.size();
    capacity = 1;
    while (capacity < size) {
        capacity *= 2;
    }
    std::vector<Node*> nodes(size);
    for (size_t i = 0; i < items.size(); i++) {
        std::string hash = hash_item(items[i]);
        nodes[i] = new Node(hash, i, i + 1);
    }
    while (nodes.size() > 1) {
        std::vector<Node*> new_nodes;
        for (size_t i = 0; i < nodes.size(); i += 2) {
            size_t left_index = nodes[i]->left_index;
            size_t right_index = nodes[i]->right_index * 2 - left_index;
            Node* new_node = new Node(NIL, left_index, right_index);
            new_node->left = nodes[i];
            if (i != nodes.size() - 1) {
                new_node->right = nodes[i + 1];
            }
            update(new_node);
            new_nodes.push_back(new_node);
        }
        nodes.swap(new_nodes);
    }
    root = nodes[0];
}

void merkle_tree::add(const std::string &item) {
    if (capacity == 0) {
        capacity = 1;
        size = 1;
        root = new Node(hash_item(item), 0, 1);
        return;
    }
    if (size == capacity) {
        capacity *= 2;
        Node* new_root = new Node(NIL, 0, capacity);
        new_root->left = root;
        root = new_root;
    }
    insert(root, size, item);
    size++;
}

void merkle_tree::update(merkle_tree::Node *v) {
    std::string new_item = C1;
    if (v->left != nullptr) {
        new_item += v->left->hash;
    } else {
        new_item += NIL;
    }
    new_item += C2;
    if (v->right != nullptr) {
        new_item += v->right->hash;
    } else {
        new_item += NIL;
    }
    v->hash = sha256(new_item);
}

void merkle_tree::insert(merkle_tree::Node *v, size_t index, const std::string &item) {
    if (v->is_leaf()) {
        v->hash = hash_item(item);
        return;
    }
    if (v->left == nullptr) {
        v->left = new Node(NIL, v->left_index, (v->right_index + v->left_index) / 2);
    }
    if (index < v->left->right_index) {
        insert(v->left, index, item);
    } else {
        if (v->right == nullptr) {
            v->right = new Node(NIL, v->left->right_index, v->right_index);
        }
        insert(v->right, index, item);
    }
    update(v);
}

std::string merkle_tree::hash_item(const std::string &item) {
    return sha256(C0 + item);
}

void merkle_tree::set(size_t index, const std::string &item) {
    if (index > size) {
        throw std::invalid_argument("index out of range");
    }
    if (index == size) {
        add(item);
    } else {
        insert(root, index, item);
    }
}

merkle_tree::witness merkle_tree::create_witness(size_t index) {
    if (index >= size) {
        throw std::invalid_argument("index out of range");
    }
    witness w;
    prove(root, index, w);
    return w;
}

bool merkle_tree::verify_witness(merkle_tree::witness w, size_t index, const std::string &item) {
    if (index >= size) {
        throw std::invalid_argument("index out of range");
    }
    return check_proof(root, index, item, w);
}

void merkle_tree::prove(merkle_tree::Node *v, size_t index, merkle_tree::witness &w) {
    if (v->is_leaf()) {
        return;
    }
    if (index < v->left->right_index) {
        prove(v->left, index, w);
        if (v->right != nullptr) {
            w.push_back(v->right->hash);
        } else {
            w.push_back(NIL);
        }
    } else {
        prove(v->right, index, w);
        w.push_back(v->left->hash);
    }
}

bool merkle_tree::check_proof(merkle_tree::Node *v, size_t index, const std::string &item, merkle_tree::witness &w) {
    if (v->is_leaf()) {
        return w.empty() && v->hash == hash_item(item);
    }
    if (w.empty()) {
        return false;
    }
    if (index < v->left->right_index) {
        std::string s = w.back();
        w.pop_back();
        std::string r = v->right == nullptr ? NIL : v->right->hash;
        return s == r && check_proof(v->left, index, item, w);
    } else {
        std::string s = w.back();
        w.pop_back();
        std::string l = v->left->hash;
        return s == l && check_proof(v->right, index, item, w);
    }
}

merkle_tree::Node::Node(const std::string &hash, size_t left_index, size_t right_index) {
    this->hash = hash;
    this->left_index = left_index;
    this->right_index = right_index;
    left = nullptr;
    right = nullptr;
}

merkle_tree::Node::~Node() {
    delete left;
    delete right;
}

bool merkle_tree::Node::is_leaf() {
    return right_index - left_index == 1;
};


