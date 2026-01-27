#include <iostream>
#include <cstddef>
#include <initializer_list>

namespace My
{
    template <typename T>
    class List
    {
        private:
            struct Node
            {
                T data;
                Node* prev;
                Node* next;
                Node(const T& value) : data(value), prev(nullptr), next(nullptr){}
            };
            Node* m_head;
            Node* m_tail;
            size_t m_size;
        public:
            class iterator
            {
                private:
                    Node* m_ptr;
                public:
                    iterator(Node* ptr = nullptr) : m_ptr(ptr){}
                    iterator(const iterator& other) = default;
                    T& operator*()
                    {
                        return m_ptr->data;
                    }
                    T* operator->()
                    {
                        return &m_ptr->data;
                    }
                    iterator& operator++()
                    {
                        m_ptr = m_ptr->next;
                        return *this;
                    }
                    iterator operator++(int)
                    {
                        iterator temp(*this);
                        m_ptr = m_ptr->next;
                        return temp;
                    }
                    iterator& operator--()
                    {
                        m_ptr = m_ptr->prev;
                        return *this;
                    }
                    iterator operator--(int)
                    {
                        iterator temp(*this);
                        m_ptr = m_ptr->prev;
                        return temp;
                    }
                    bool operator==(const iterator& other) const
                    {
                        return m_ptr == other.m_ptr;
                    }
                    bool operator!=(const iterator& other) const
                    {
                        return m_ptr != other.m_ptr;
                    }
                    friend class List;
            };
        public:
            List() : m_head(nullptr), m_tail(nullptr), m_size(0){}
            List(std::initializer_list<T> list) : m_head(nullptr), m_tail(nullptr), m_size(0)
                {
                    for (const T& value : list)
                    {
                        push_back(value);
                    }
                }
            ~List()
            {
                Node* current = m_head;
                while(current)
                {
                    Node* next = current->next;
                    delete current;
                    current = next;
                }
                m_head = nullptr;
                m_tail = nullptr;
                m_size = 0;

            }
            List(const List& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
            {
                Node* cur = other.m_head;
                while(cur)
                {
                    push_back(cur->data);
                    cur = cur->next;
                }
            }
            List& operator=(const List& other)
            {
                if(this != &other)
                {
                    Node* cur = m_head;
                    while(cur)
                    {
                        Node* next = cur->next;
                        delete cur;
                        cur = next;
                    }
                    m_head = nullptr;
                    m_tail = nullptr;
                    m_size = 0;
                    cur = other.m_head;
                    while(cur)
                    {
                        push_back(cur->data);
                        cur = cur->next;
                    }
                }
                return *this;
            }
            List(List&& other) : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
            {
                other.m_head = nullptr;
                other.m_tail = nullptr;
                other.m_size = 0;
            }
            List& operator=(List&& other)
            {
                if(this != &other)
                {
                    Node* cur = m_head;
                    while(cur)
                    {
                        Node* next = cur->next;
                        delete cur;
                        cur = next;
                    }
                    m_head = other.m_head;
                    m_tail = other.m_tail;
                    m_size = other.m_size;
                    other.m_head = nullptr;
                    other.m_tail = nullptr;
                    other.m_size = 0;
                }
                return *this;
            }
            void push_back(const T& value)
            {
                Node* new_node = new Node(value);
                if(!m_head)
                {
                    m_head = m_tail = new_node;
                }
                else
                {
                    new_node->prev = m_tail;
                    m_tail->next = new_node;    
                    m_tail = new_node;
                }
                ++m_size;
            }
            void push_front(const T& value)
            {
                Node* new_node = new Node(value);
                if(!m_head)
                {
                    m_head = m_tail = new_node;
                }
                else
                {
                    new_node->next = m_head;
                    m_head->prev = new_node;
                    m_head = new_node;
                }
                ++m_size;
            }
            void pop_back()
            {
                if(!m_tail)
                {
                    return;
                }
                if(m_tail == m_head)
                {
                    delete m_tail;
                    m_head = nullptr;
                    m_tail = nullptr;
                    m_size = 0;
                    return;
                }
                Node* new_node = m_tail;
                m_tail = m_tail->prev;
                m_tail->next = nullptr;
                delete new_node;
                --m_size;
            }
            void pop_front()
            {
                if(!m_head)
                {
                    return;
                }
                if(m_head == m_tail)
                {
                    delete m_head;
                    m_head = nullptr;
                    m_tail = nullptr;
                    m_size = 0;
                    return;
                }
                Node* new_node = m_head;
                m_head = m_head->next;
                m_head->prev = nullptr;
                delete new_node;
                --m_size;
            }
            bool empty() const
            {
                return m_size == 0;
            }
            size_t size() const
            {
                return m_size;
            }
            iterator begin()
            {
                return iterator(m_head);
            }
            iterator end()
            {
                return iterator(nullptr);
            }
            iterator insert(iterator it,const T& value)
            {
                if(!m_head)
                {
                    push_back(value);
                    return iterator(m_head);
                }
                if(it.m_ptr == m_head)
                {
                    push_front(value);
                    return iterator(m_head);
                }
                if(it.m_ptr == nullptr)
                {
                    push_back(value);
                    return iterator(m_tail);
                }
                Node* cur = it.m_ptr;
                Node* cur_prev = cur->prev;
                Node* new_node = new Node(value);
                new_node->next = cur;
                new_node->prev = cur_prev;
                cur->prev = new_node;
                cur_prev->next = new_node;
                ++m_size;
                return iterator(new_node);
            }
            iterator erase(iterator it)
            {
                if(!it.m_ptr)
                {
                    return end();
                }
                Node* cur = it.m_ptr;
                Node* cur_next = cur->next;
                if(cur == m_head)
                {
                    pop_front();
                    return iterator(cur_next);
                }
                if(cur == m_tail)
                {
                    pop_back();
                    return end();
                }
                Node* cur_prev = cur->prev;
                cur_prev->next = cur->next;
                cur->next->prev = cur_prev;

                delete cur;
                --m_size;
                return iterator(cur_next);
            }
    };
}



int main()
{
    My::List<int> l{1, 2, 3, 4, 5, 5, 7, 8};
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto it = l.begin();
    ++it; 
    l.insert(it, 10);
    for (auto it2 = l.begin(); it2 != l.end(); ++it2)
    {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;
    it = l.begin();
    ++it; 
    l.erase(it);
    for (auto it3 = l.begin(); it3 != l.end(); ++it3)
    {
        std::cout << *it3 << " ";
    }
    std::cout << std::endl;

    return 0;
}
