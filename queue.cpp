#include <iostream>
template <typename T>
struct Node
{
    T data;
    Node* m_front;
    Node* m_end;
    Node(T value) : data(value), m_front(nullptr), m_end(nullptr) {}
};

template <typename T>
class Queue 
{
private:
    Node<T>* front;
    Node<T>* end;

public:
    Queue() : front(nullptr), end(nullptr) { }
    ~Queue() 
    {
        while (front != nullptr) 
        {
            Node<T>* temp = front;
            front = front->m_end;
            delete temp;
        }
    }
    void push(T value)
    {
        if(front == nullptr)
        {
            front = new Node<T>(value);
            end = front;
        }
        else
        {
            end->m_end = new Node<T>(value);
            end = end->m_end;
        }
    }
    void pop()
    {
        if(front == nullptr)
        {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        Node<T>* temp = front;
        front = front->m_end;
        delete temp;
    }
    void print()
    {
        Node<T>* temp = front;
        while(temp != nullptr)
        {
            std::cout << temp->data << " ";
            temp = temp->m_end;
        }
        std::cout << std::endl;
    }
};


int main()
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.print();
    q.pop();
    q.print();
    return 0;
}
