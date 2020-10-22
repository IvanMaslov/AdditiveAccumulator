#include <vector>
#include <string>

#ifndef CRYPTO_MERKLE_TREE_H
#define CRYPTO_MERKLE_TREE_H

class merkle_tree {
public:
    using witness = std::vector<std::string>;
private:
    static const std::string C0;
    static const std::string C1;
    static const std::string C2;

    struct Node {
        std::string hash;
        Node* left;
        Node* right;
        size_t left_index;
        size_t right_index;

        Node(const std::string &hash, size_t left, size_t right);
        ~Node();

        bool is_leaf();
    };

    Node* root;
    size_t size;
    size_t capacity;

    void insert(Node* v, size_t index, const std::string &item);
    void update(Node* v);
    std::string hash_item(const std::string &item);
    void prove(Node *v, size_t index, witness &w);
    bool check_proof(Node* v, size_t index, const std::string &item, witness &w);

public:
    static const std::string NIL;

    merkle_tree();
    merkle_tree(const std::vector<std::string> &items);

    std::string get_root();
    size_t get_size();
    void add(const std::string &item);
    void set(size_t index, const std::string &item);

    witness create_witness(size_t index);
    bool verify_witness(witness w, size_t index, const std::string &item);
};

#endif //CRYPTO_MERKLE_TREE_H
