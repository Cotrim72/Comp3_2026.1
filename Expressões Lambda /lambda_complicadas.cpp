#include <map>
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

template<typename lambda>
struct Expr{
    lambda l;
    Expr(lambda l):l(l){}
    template<typename K>
    auto operator()(K valor)const {return l(valor);}
    template<typename I>
    auto operator[](I i) const {
        auto nova_lambda = [l_atual = this->l, i](auto v){ return l_atual(v)[i]; };
        return Expr<decltype(nova_lambda)>{nova_lambda};
    }
};

auto x = Expr{[](auto valor){return valor;}};

template<typename A, typename B>
auto operator + ( A a, B b ) {
    return Expr{[a,b]( auto x ){ return a(x) + b(x); }};
}

template<typename A>
auto operator + ( A a, int b ) {
    return Expr{[a,b]( auto x ){
        if constexpr(is_same_v<decay_t<decltype(x)>,vector<int>>){
            auto resultado = a(x);  
            resultado.push_back(b); 
            return resultado;
        }
        else 
            return a(x) + b; 
    }};
}
template<typename T>
auto operator + (vector<T> v, int b){
    v.push_back(b);
    return v;
}
template<typename B>
auto operator + ( int a, B b ) {
    return Expr{[a,b]( auto x ){ return a + b(x);}};
}
template<typename A, typename B>
auto operator * (A a, B b){
    return Expr{[a,b](auto x){return a(x)*b(x);}};
}
template<typename F, typename = invoke_result_t<F, int>>
auto operator <<(ostream& os, F a){
    return [&os,a](auto x){
        using std::operator<<;  
        os << a(x);};
}

template<typename A>
auto operator <<(A a, char b){
    return [a,b](auto x){
        using std::operator<<;
        a(x);
        cout << b;
    };
}
template<typename A>
auto operator %(A a, int b){
    return Expr{[a,b](auto x){return a(x)%b;}};
}
template <typename L>
auto operator ==(Expr<L> a, int b){
    return Expr{[a,b](auto x){return a(x) == b;}};
}

template <typename L>
auto operator != (Expr<L> a, int b){
    return Expr{[a,b](auto v){return a(v) != b;}};
}

template <typename L, typename F>
auto operator |(Expr<L> x, F f){    
    return [x, f](auto v){
        auto result = x(v);
        for(auto const& elem : result)
            f(elem);
    };
}
