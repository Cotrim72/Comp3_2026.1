#include <iostream>
#include <cmath>
#include <type_traits>

class Var{
    public:
        double e(double v) const { return v;}
        double dx(double v) const { return 1;}
};

class cte{
    public:
        cte(double x) : x(x){}
        double e(double v) const{ return x;}
        double dx(double v) const { return 0;}
    private:
        double x;
};

template <typename F, typename G>
class Adicao{
    public:
        Adicao(const F& f, const G& g) : f(f), g(g){}
        double e(double v) const {return f.e(v) + g.e(v);}
        double dx(double v) const{return f.dx(v) + g.dx(v);}
    private:
        F f;
        G g;
};

template <typename F, typename G>
class Subtracao{
    public:
        Subtracao(const F& f, const G& g) : f(f), g(g){}
        double e(double v) const {return f.e(v) - g.e(v);}
        double dx(double v) const {return f.dx(v) - g.dx(v);}
    private:
        F f;
        G g;
};

template <typename F, typename G>
class mult{
    public:
        mult(const F& f, const G& g) : f(f), g(g){}
        double e(double v) const {return f.e(v)*g.e(v);}
        double dx(double v) const {return f.dx(v)*g.e(v) + f.e(v)*g.dx(v);}
    private:
        F f;
        G g;
};

template <typename F, typename G>
class divisao{
    public:
        divisao(const F& f, const G& g) : f(f), g(g){}
        double e(double v) const {return f.e(v)/g.e(v);}
        double dx(double v) const {
            auto dif = f.dx(v)*g.e(v) - f.e(v)*g.dx(v);
            auto g_2 = (mult(g,g)).e(v);
            return dif/g_2;
        }
    private:
        F f;
        G g;
};

template <typename F>
class exponenciacao{
    public:
        exponenciacao(const F& f, int g) : f(f), g(g){}
        double e(double v) const { return std::pow(f.e(v),g);}
        double dx(double v) const {
            return g*((f->*(g-1)).e(v))*f.dx(v);
        }
    private:
        F f;
        int g;
};

template <typename F>
class Seno{
    public: 
        Seno(F f): f(f){}
        double e(double v) const{ return std::sin(f.e(v));}
        double dx(double v) const { return cos(f).e(v)*f.dx(v);}
    private:
        F f;
};

template <typename F>
class Cosseno{
    public: 
        Cosseno(F f): f(f){}
        double e(double v) const{ return std::cos(f.e(v));}
        double dx(double v) const { return -sin(f).e(v)*f.dx(v);}
    private:
        F f;
};

template <typename F>
class Exponencial{
    public: 
        Exponencial(F f): f(f){}
        double e(double v) const{ return std::exp(f.e(v));}
        double dx(double v) const { return exp(f).e(v)*f.dx(v);}
    private:
        F f;
};

template <typename F>
class Logaritmo{
    public: 
        Logaritmo(F f): f(f){}
        double e(double v) const{ return std::log(f.e(v));}
        double dx(double v) const { return f.dx(v)/f.e(v);}
    private:
        F f;
};

// Operador de multiplicação
auto operator*(double t, auto f){
    return mult(cte(t),f);
}
auto operator*(int t, auto f){
    return mult(cte(t),f);
}
auto operator*(auto t, double f){
    return mult(t,cte(f));
}
auto operator*(auto t, int f){
    return mult(t,cte(f));
}
auto operator*(auto t, auto f){
    return mult(t,f);
}

// Operador de soma
auto operator+(double t, auto f){
    return Adicao(cte(t),f);
}
auto operator+(int t, auto f){
    return Adicao(cte(t),f);
}
auto operator+(auto t, double f){
    return Adicao(t,cte(f));
}
auto operator+(auto t, int f){
    return Adicao(t,cte(f));
}
auto operator+(auto t, auto f){
    return Adicao(t,f);
}

// Operador de subtração
auto operator-(double t, auto f){
    return Subtracao(cte(t),f);
}
auto operator-(int t, auto f){
    return Subtracao(cte(t),f);
}
auto operator-(auto t, double f){
    return Subtracao(t,cte(f));
}
auto operator-(auto t, int f){
    return Subtracao(t,cte(f));
}
auto operator-(auto t, auto f){
    return Subtracao(t,f);
}

// Operador de divisão
auto operator/(double t, auto f){
    return divisao(cte(t),f);
}
auto operator/(int t, auto f){
    return divisao(cte(t),f);
}
auto operator/(auto t, double f){
    return divisao(t,cte(f));
}
auto operator/(auto t, int f){
    return divisao(t,cte(f));
}
auto operator/(auto t, auto f){
    return divisao(t,f);
}

// Operador de Exponenciação
template<typename T, typename N>
auto operator->*(T t, N f){
    static_assert(std::is_integral_v<N>, "Operador de potenciação definido apenas para inteiros");
    return exponenciacao(t,f);
}

template<typename T>
auto sin(T f) {
    return Seno<T>(f); 
}

template<typename T>
auto cos(T f) {
    return Cosseno<T>(f); 
}

template<typename T>
auto exp(T f) {
    return Exponencial<T>(f); 
}

template<typename T>
auto log(T f) {
    return Logaritmo<T>(f); 
}

int main( int argc, char* argv[]) {
    Var x;
    double v = 3;
    auto f =  2 * x->*1;
    std::cout << "f(" << v << ")=" << f. e ( v ) << ", f'(" << v << ")=" << f. dx ( v ) << std::endl ;

    double n = 1.1;
    auto g = x*x*( x + 8.0 ) + x;
    std::cout << "g(" << n << ")=" << g. e ( n ) << ", f'(" << n << ")=" << g. dx ( n ) << std::endl ;
    
}
