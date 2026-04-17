#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

double seno( double n ) { return sin(n); }
int id( int n ) { return n; }
string roman( int n ) {
    map<int,string> rom = { { 1, "I" }, { 2, "II" }, { 3, "III" }, { 4, "IV" }, { 5, "V" }, { 6, "VI" }, { 7, "VII" }, { 8, "VIII" } } ; 

    return rom[n]; 
}

struct FunctorSimples { 
    string operator()( int n ) { return roman( n ) + "!"; }
};

struct FunctorTemplate { 
    template <typename T>
    T operator()( T n ) { return n+n; }
};

template <typename T>
ostream& operator << ( ostream& o, const vector<T>& v ) {
    o << "[ ";
    for( auto x : v )
        o << x << " ";
        
    return o << "]";
}

auto apply(auto const& v, auto F) {
    vector<decltype(F(*begin(v)))> res;
    for(auto const& x : v) {
        res.push_back(F(x));
    }
    return res;
}

template <typename T, typename Function>
auto apply(initializer_list<T> const& v, Function F){
    vector<decltype(F(*v.begin()))> res;
    for(auto const& x : v){
        res.push_back(F(x));
    }
    return res;
}

int main( int argc, char* argv[]) {     
    vector<int> v{1,2,3,4};
    vector<string> r = ::apply(v, roman);
    vector<string> s = ::apply(v, FunctorSimples());
    vector<int> l = ::apply(v, id);
    vector<int> t = ::apply(v, FunctorTemplate());
    cout << r << endl;
    cout << s << endl;
    cout << l << endl;
    cout << t << endl;
    cout << ::apply( vector{ 1, 2, 3 }, FunctorSimples() );
    cout << ::apply( vector{ 1, 2, 3 }, FunctorTemplate() ) << ::apply( vector<string>{ "a", "b", "c" }, FunctorTemplate() );

  return 0;
}
