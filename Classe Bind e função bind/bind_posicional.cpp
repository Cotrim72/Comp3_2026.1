#include <tuple>
#include <functional>
#include <type_traits>

using namespace std;

class PlaceHolder{};

PlaceHolder __;

template <typename ...Args>
inline constexpr auto head( std::tuple<Args...> tp ) {
    return std::get<0>( tp );
}

template <typename H, typename ...T>
auto tail( const tuple<H, T...> t ) {
  constexpr auto split = []( const H head, const T... tail ) {
    return tuple<const T...>{ tail... };
  };

  return apply( split, t );
}

inline auto inverte(std::tuple<> t) {
    return t;
}

template<size_t N>
auto verifica_ph(std::tuple<> t) {
    return t;
}

template<typename first, typename ...Args>
auto inverte(std::tuple<first, Args...> t){
    if constexpr(sizeof...(Args)>0)
        return std::tuple_cat(inverte(tail(t)),std::tuple{head(t)});
    else
        return std::tuple{head(t)};
}

template<size_t N, typename ...Args>
auto verifica_ph(std::tuple<Args...> t){
    if constexpr(N < std::tuple_size_v<decay_t<decltype(t)>>){
        if constexpr(is_same_v<decay_t<decltype(head(t))>,PlaceHolder>){
            return verifica_ph<N+1>(tail(t));
        }
        else
            return inverte(t);
    }
    else
        return t;
}

template<typename T>
constexpr auto tem_ph(T const& t){
    return std::apply([](auto const&... args) {
        return std::integral_constant<bool, (is_same_v<decay_t<decltype(args)>, PlaceHolder> || ...)>{};
    }, t);
}


template<typename T1, typename T2>
auto concatena_tuplas(T1 t1, T2 t2) {
    if constexpr (std::tuple_size_v<T1> == 0) {
        return std::tuple_cat(t1, t2); 
    } else {
        auto h1 = head(t1);
        auto resto_t1 = tail(t1);
        if constexpr (is_same_v<decay_t<decltype(h1)>, PlaceHolder>) {
            return std::tuple_cat(std::tuple{head(t2)}, concatena_tuplas(resto_t1, tail(t2)));
        } else {
           
            return std::tuple_cat(std::tuple{h1}, concatena_tuplas(resto_t1, t2));
        }
    }
}

template <typename F, typename Tuple>
constexpr bool esta_pronto_para_chamar = false;

template <typename F, typename... Args>
constexpr bool esta_pronto_para_chamar<F, std::tuple<Args...>> = std::is_invocable_v<F, Args...>;

template <typename F, typename ...Args1>
class Bind {
    public:
        Bind( F f, std::tuple<Args1...> args1 ): f(f), args1(args1){}
 
        template <typename ...Args2>
        auto operator()( Args2... args2 ) {
            auto args1_limpo = verifica_ph<0>(inverte(args1));
            auto concatena = concatena_tuplas(args1_limpo, std::tuple<Args2...>{args2...});
    
            constexpr bool ainda_tem_ph = decltype(tem_ph(concatena))::value;

            if constexpr ( ainda_tem_ph ) {
                return std::apply([this](auto... novos_args) {
                        return Bind<F, decltype(novos_args)...>{ f, std::tuple{novos_args...} };
                    }, concatena);
            }
            else {
                if constexpr (!esta_pronto_para_chamar<F, decltype(concatena)>) {
                    return std::apply([this](auto... novos_args) {
                            return Bind<F, decltype(novos_args)...>{ f, std::tuple{novos_args...} };
                        }, concatena);
                }
                else 
                    return std::apply([&](auto&&... args) {
                        return std::invoke(f, std::forward<decltype(args)>(args)...);
                    }, concatena);
            }
}
    private:
        F f;
        std::tuple<Args1...> args1;
};
 
template <typename F, typename ...Args1>
auto bind( F f, Args1... args1 ) {
    return Bind{ f, std::tuple{ args1... } };
}
