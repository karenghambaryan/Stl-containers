#include <iostream>
#include <vector>
#include <list>

namespace my
{

    template <typename k, typename v>
    class HashTable
    {
        private:
            std::vector<std::list<std::pair<k,v>>> m_table;
            size_t m_size;
            size_t hash(const k& key)
            {
                return std::hash<k>{}(key) % m_size;
            }

        public:
            HashTable(size_t size) : m_size(size)
            {
                m_table.resize(m_size);
            }

            void insert(const k& key, const v& value)
            {
                size_t index = hash(key);

                for(auto& p : m_table[index])
                {
                    if(p.first == key)
                    {
                        p.second = value;
                        return;
                    }
                }
            m_table[index].push_back({key,value});
            }

            bool find(const k& key, v& value)
            {
                size_t index = hash(key);
                for(auto& p : m_table[index])
                {
                    if(p.first == key)
                    {
                        value = p.second;
                        return true;
                    }
                }
                return false;
            }

            void remove(const k& key)
            {
                size_t index = hash(key);
                auto& bucket = m_table[index];
                for(auto it = bucket.begin(); it != bucket.end(); ++it)
                {
                    if(it->first == key)
                    {
                        bucket.erase(it);
                        return;
                    }
                }
            }
    };
}

int main()
{
    my::HashTable<std::string, int> ht(10);
    ht.insert("one", 1);
    ht.insert("two", 2);
    ht.insert("three", 3);

    int value;
    if(ht.find("two", value))
    {
        std::cout << "Found: " << value << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }

    ht.remove("two");
    if(ht.find("two", value))
    {
        std::cout << "Found: " << value << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }
    return 0;
}