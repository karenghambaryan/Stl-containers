#include <iostream>

namespace my
{
    template <typename T>
    struct Node
    {
        T m_data;
        Node* m_left;
        Node* m_right;
        Node(T data) : m_data(data), m_left(nullptr), m_right(nullptr) {}
    };
    template <typename T>
    class Set
    {
        private:
            Node<T>* m_root;  
            Node<T>* insert(Node<T>* node, T data)
            {
                if (node == nullptr)
                {
                    return new Node<T>(data);
                }
                else if (data < node->m_data)
                {
                    node->m_left = insert(node->m_left, data);
                }
                else if (data > node->m_data)
                {
                    node->m_right = insert(node->m_right, data);
                }
                return node;
            }
            bool find(Node<T>* node, T data)
            {
                if(!node)
                {
                    return false;
                }
                if(node->m_data == data)
                {
                    return true;
                }
                else if(node->m_data < data)
                {
                    return find(node->m_right, data);
                }
                else
                {
                    return find(node->m_left, data);
                }
            }
            void inorder(Node<T>* node)
            {
                if(node)
                {
                    inorder(node->m_left);
                    std::cout << node->m_data << " ";
                    inorder(node->m_right);
                }
            }
            void postorder(Node<T>* node)
            {
                if(node)
                {
                    postorder(node->m_left);
                    postorder(node->m_right);
                    std::cout << node->m_data << " ";
                }
            }
            void preorder(Node<T>* node)
            {
                if(node)
                {
                    std::cout << node->m_data << " ";
                    preorder(node->m_left);
                    preorder(node->m_right);
                }
            }
        public:
            Set() : m_root(nullptr) {}
            void insert(T data)
            {
                m_root = insert(m_root, data);
            }
            void inorder()
            {
                inorder(m_root);
                std::cout << std::endl;
            }
            void postorder()
            {
                postorder(m_root);
                std::cout << std::endl;
            }
            void preorder()
            {
                preorder(m_root);
                std::cout << std::endl;
            }
            bool contains(T data)
            {
                return find(m_root, data);  
            }
    };
}

int main()
{
    my::Set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(7);
    s.insert(2);
    s.insert(4);
    s.insert(6);
    s.insert(8);
    s.insert(8);


    std::cout << "Inorder: ";
    s.inorder();
    std::cout << "Preorder: ";
    s.preorder();
    std::cout << "Postorder: ";
    s.postorder();
    std::cout << "Contains 4? " << (s.contains(4) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 10? " << (s.contains(10) ? "Yes" : "No") << std::endl;

    return 0;
}