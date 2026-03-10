#include <iostream>
#include <queue>


struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    void destroy(Node* node) {
        if (!node) 
        {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    Node* insert(Node* node, int value) {
        if (!node) 
        {
            return new Node(value);
        }
        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }

Node* remove(Node* node, int value)
{
    if (!node)
    {
        return nullptr;
    }

    if (value < node->data)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        if (!node->left)
        {
            Node* tmp = node->right;
            delete node;
            return tmp;
        }
        else if (!node->right)
        {
            Node* tmp = node->left;
            delete node;
            return tmp;
        }

        Node* succ = findMin(node->right);
        node->data = succ->data;
        node->right = remove(node->right, succ->data);
    }

    return node;
}
    bool contains(Node* node, int value) const 
    {
        if (!node) 
        {
            return false;
        }
        if (value == node->data) 
        {
            return true;
        }
        return value < node->data ? contains(node->left, value): contains(node->right, value);
    }

    void inorder(Node* node) const {
        if (!node)
        {
            return;
        }
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const {
        if (!node)
        {
            return;
        }
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {
        if (!node) 
        {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() 
    { 
        destroy(root); 
    }

    void insert(int value) 
    { 
        root = insert(root, value); 
    }
    void remove(int value) 
    { 
        root = remove(root, value); 
    }
    bool contains(int value) const 
    { 
        return contains(root, value); 
    }

    void inorder() const 
    {
        inorder(root);
        std::cout << '\n';
    }
    void preorder() const 
    {
        preorder(root);
        std::cout << '\n';
    }
    void postorder() const 
    {
        postorder(root);
        std::cout << '\n';
    }

    void levelOrder() const {
        if (!root) 
        {
        return;
        }
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) 
        {
            Node* cur = q.front(); 
            q.pop();
            std::cout << cur->data << " ";
            if (cur->left)
            {
                q.push(cur->left);
            }
            if (cur->right)
            {
                q.push(cur->right);
            }
        }
        std::cout << '\n';
    }
};

int main() {
    BinarySearchTree tree;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) 
    {
        tree.insert(v);
    }
    std::cout << "Inorder traversal: ";
    tree.inorder();
    std::cout << "Preorder traversal: ";
    tree.preorder();
    std::cout << "Postorder traversal: ";
    tree.postorder();
    std::cout << "Level-order traversal: ";
    tree.levelOrder();

    std::cout << "Contains 40? " << (tree.contains(40) ? "yes" : "no") << '\n';
    std::cout << "Contains 100? " << (tree.contains(100) ? "yes" : "no") << '\n';
    std::cout << "Removing 30 (node with two children)\n";
    tree.remove(30);
    std::cout << "Inorder after removal: ";
    tree.inorder();

    return 0;
}