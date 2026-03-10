#include <iostream>

template <typename T>
struct Node 
{
    T data;
    Node* m_next;
    Node(T value) : data(value), m_next(nullptr) {}
};

template <typename T>
class Stack
{
private:
    Node<T>* m_top;
public:
    Stack() : m_top(nullptr) {}
    ~Stack()
    {
        while (m_top != nullptr) 
        {
            Node<T>* temp = m_top;
            m_top = m_top->m_next;
            delete temp;
        }
    }
    void push(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->m_next = m_top;
        m_top = newNode;
    }
    void pop()
    {
        if (m_top == nullptr) 
        {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        Node<T>* temp = m_top;
        m_top = m_top->m_next;
        delete temp;
    }   
    void top()
    {
        if (m_top == nullptr) 
        {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        std::cout << m_top->data << std::endl;
    }
    void print()
    {
        Node<T>* temp = m_top;
        while (temp != nullptr) 
        {
            std::cout << temp->data << " ";
            temp = temp->m_next;
        }
        std::cout << std::endl;
    }
};

int main()
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.print(); 
    s.top();   
    s.pop();
    s.print(); 
}