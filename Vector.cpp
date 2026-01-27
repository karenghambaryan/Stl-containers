#include <iostream>
#include <cstddef>
#include <initializer_list>

namespace My
{
    template <typename T>

    class Vector
    {
        private:
            T* m_data;
            size_t m_size;
            size_t m_capacity;
        public:
            Vector() : m_data(nullptr),m_size(0),m_capacity(0){}
            ~Vector()
            {
                delete[] m_data;
            }
            Vector(std::initializer_list<T> list) : m_data(nullptr), m_size(list.size()),m_capacity(list.size() * 2)
            {
                m_data = new T[m_capacity];
                size_t i = 0;
                for (const T& value : list)
                {
                    m_data[i++] = value;
                }
            }
            Vector(const Vector& other) : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity)
            {
                if(m_capacity > 0)
                {
                    m_data = new T[m_capacity];
                    for(size_t i = 0; i < m_size; i++)
                    {
                        m_data[i] = other.m_data[i];
                    }
                }
            }
            Vector& operator=(const Vector& other)
            {
                if(this != &other)
                {
                    delete[] m_data;
                    m_size = other.m_size;
                    m_capacity = other.m_capacity;
                    m_data = nullptr;
                    if(m_capacity > 0)
                    {
                        m_data = new T[m_capacity];
                        for(size_t i = 0; i < m_size; i++)
                        {
                            m_data[i] = other.m_data[i];
                        }
                    }
                }
                return *this;
            }
            Vector(Vector&& other) : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
            {
                other.m_data = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;
            }
            Vector& operator=(Vector&& other)
            {
                if(this != &other)
                {
                    delete[] m_data;
                    m_data = other.m_data;
                    m_size = other.m_size;
                    m_capacity = other.m_capacity;
                    other.m_data = nullptr;
                    other.m_size = 0;
                    other.m_capacity = 0;
                }
                return *this;
            }
            size_t size() const
            {
                return m_size;
            }
            size_t capacity() const
            {
                return m_capacity;
            }
            void push_back(const T& value)
            {
                if(m_size == m_capacity)
                {
                    size_t new_cap;
                    if(m_capacity == 0)
                    {
                        new_cap = 1;
                    }
                    else
                    {
                        new_cap = m_capacity * 2;
                    }
                    reserve(new_cap);
                }
                m_data[m_size] = value;
                m_size++;
            }
            void pop_back()
            {
                if(m_size > 0)
                {
                    --m_size;
                }
            }
            T& operator[](size_t i)
            {
                return m_data[i];
            }
            const T& operator[](size_t i) const
            {
                return m_data[i];
            }
            void reserve(size_t new_capacity)
            {
                if(new_capacity > m_capacity)
                {
                    T*new_data = new T[new_capacity];
                    for(size_t i = 0; i < m_size; i++)
                    {
                        new_data[i] = m_data[i];
                    }
                    delete[] m_data;
                    m_data = new_data;
                    m_capacity = new_capacity;
                }
            }
            void resize(size_t new_size)
            {
                if(new_size > m_capacity)
                {
                    reserve(new_size);
                }
                m_size = new_size;
            }
            bool empty() const
            {
                return m_size == 0;
            }
            T* begin()
            {
                return m_data;
            }
            T* end()
            {
                return m_data + m_size;
            }
            const T* begin() const
            {
                return m_data;
            }
            const T* end() const
            {
                return m_data + m_size;
            }
    };

}
int main()
{
    My::Vector<int> v = {1, 2, 3, 4, 5};

    for (int x : v)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Capacity: " << v.capacity() << std::endl;

    return 0;
}

