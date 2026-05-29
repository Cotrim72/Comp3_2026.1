#include <functional>

using namespace std;

template <typename F, typename ... P>
class Bind {
public:
    F Funct;
    tuple<P...> Paramt;

    Bind(F func, P... param) : Funct(func), Paramt(param...) {}

    template<typename ...Args>
    auto operator()(Args... args) {
        auto all_args = tuple_cat(Paramt, forward_as_tuple(args...));

        return apply([&](auto&&... combined) {
            using NewBind = Bind<F,decay_t<decltype(combined)>...>;

            if constexpr (is_invocable_v<F, decltype(combined)...>) {
                return invoke(Funct,combined...);
            } else {
                return NewBind(Funct, combined...);
            }
        }, all_args);
    }
};

template<typename F, typename ... P>
auto bind(F func, P ... param ){
    return Bind<F,P...>(func,param...);
}

template<typename F, typename ...P>
auto bind(Bind<F,P...> & B, P ... param){
    return Bind<F,P...>(B,param ...);
}
