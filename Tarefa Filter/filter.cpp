#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <string.h>

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

template <typename T> 
void myPrint( T t ) {
    cout << t << " ";
}

struct PrintM {
  void operator() ( vector<int> v ) {
      cout << "[ " << v[0] << ", " << v[1] << " ] ";
  }
};

struct PrintM2 {
  void operator() ( vector<int> v ) {
      v | myPrint<int>;
  }
};

string StringToUpper(string strToConvert)
{
   for (std::string::iterator p = strToConvert.begin(); strToConvert.end() != p; ++p)
       *p = toupper(*p);

   return strToConvert;
}

struct PrintM3 {
    void operator()( string st ) {
        cout << StringToUpper( st ) << " ";
    }
};

int main( int argc, char* argv[]) {
    vector<string> v1 = { "janeiro", "fevereiro", "março", "abril", "maio" };
    v1 | &string::length | [] ( int x ) { cout << x << " "; };
  return 0;
}
