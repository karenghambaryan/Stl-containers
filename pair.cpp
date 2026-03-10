#include <iostream>

namespace my
{
    template <typename T1, typename T2>
    struct pair 
    {
        T1 first;
        T2 second;
        pair(T1 f, T2 s) : first(f), second(s) {}
        void print()
        {
            std::cout << "First: " << first << " Second: " << second << std::endl;
        }
    };
    template<typename T1, typename T2>
    pair<T1,T2> make_pair(T1 a, T2 b)
    {
        return pair<T1,T2>(a,b);
    }
}
int main()
{
    auto p = my::make_pair(1, "Hello");
    p.print();
    return 0;
}   
