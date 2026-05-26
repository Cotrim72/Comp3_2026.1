#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <functional>

using namespace std;

template <typename T, typename F>
auto operator | (T const& v, F Function){
    if constexpr(is_same_v<invoke_result_t<F, typename T::value_type>, bool>){
        vector<typename T::value_type> res;
        for (auto const& j:v){
            if (invoke(Function,j)){
                res.push_back(j);
            }
        }
        return res;
    }
    else if constexpr(is_void_v<invoke_result_t<F,typename T::value_type>>){
        for_each(begin(v),end(v),Function);
        return v;
    }
    else{
        vector<decltype(invoke(Function, *begin(v)))> res;
        for(auto const& x : v) {
            res.push_back(invoke(Function,x));
        }
        return res;
    }
}
template<typename T, size_t N, typename F>
auto operator | (T (&arr)[N], F Function){
    if constexpr(is_same_v<invoke_result_t<F, T>, bool>){
        vector<T> res;
        for (auto const& j:arr){
            if (invoke(Function,j)){
                res.push_back(j);
            }
        }
        return res;
    }
    else if constexpr(is_void_v<invoke_result_t<F,T>>){
        for_each(begin(arr),end(arr),Function);
        return arr;
    }
    else{
        vector<decltype(invoke(Function,*begin(arr)))> res;
        for(auto const& x : arr) {
            res.push_back(invoke(Function,x));
        }
        return res;
    }
}

template <typename T,typename F>
auto operator | (initializer_list<T>& v, F Function){
    if constexpr(is_same_v<invoke_result_t<F, T>, bool>){
        vector<T> res;
        for (auto const& j:v){
            if (invoke(Function,j)){
                res.push_back(j);
            }
        }
        return res;
    }
    else if constexpr(is_void_v<invoke_result_t<F,T>>){
        for_each(begin(v),end(v),Function);
        return v;
    }
    else{
        vector<decltype(invoke(Function,*begin(v)))> res;
        for(auto const& x : v) {
            res.push_back(invoke(Function,x));
        }
        return res;
    }
}

class X {
    public:
        template <typename K>
        auto operator()( K valor ) const { return valor; }
};

auto operator + ( auto a, auto b ) {
    return [a,b](auto x){ return a(x) + b(x); };
}
auto operator + ( auto a, int b ) {
    return [a,b](auto x){ return a(x) + b; };
}
auto operator + ( int a, auto b ) {
    return [a,b](auto x){ return a + b(x); };
}
auto operator * (auto a, auto b){
    return [a,b](auto x){return a(x)*b(x);};
}

template<typename F, typename = invoke_result_t<F, int>>
auto operator <<(ostream& os, F a){
    return [&os,a](auto x){
        using std::operator<<;  
        os << a(x);
    };
}

auto operator <<(auto a, char b){
    return [a,b](auto x){
        using std::operator<<;
        a(x);
        cout << b;
    };
}
auto operator %(auto a, int b){
    return [a,b](auto x){return a(x)%b;};
}
auto operator ==(auto a, int b){
    return [a,b](auto x){return a(x) == b;};
}
