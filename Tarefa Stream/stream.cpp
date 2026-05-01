#include <algorithm>
#include <initializer_list>

using namespace std;

template <typename T, typename F>
void operator | (T const& v, F Function){
    for_each(begin(v),end(v),Function);
}

template <typename T,typename F>
void operator | (initializer_list<T> const& v, F Function){
    for_each(begin(v),end(v),Function);
}
