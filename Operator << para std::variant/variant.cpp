#include <iostream>
#include <variant>
#include <string>

 
using namespace std;

template<int N, typename ...args>
void print_variant(ostream& os, variant<args...> v ){
    if constexpr ( N <= (sizeof...(args)-1)){
        if (v.index() == N) 
            os << get<N>(v); 
        else
            return print_variant<N+1>(os, v);
    }
}

template<typename T, typename ...args>
ostream& operator<< (ostream& os, variant<T, args...> v){
    print_variant<0>(os, v);
    return os;
}
 
int main() {
    variant<int,char,string> x = 7;
    cout << x << endl;
    return 0;
}
