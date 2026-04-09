#include <initializer_list>
#include <iostream>

using namespace std;

class AbstractPair{ // Classe Abstrata de Pair que irá apontar para a classe Implementação
    public:
        virtual void imprime(std::ostream& o){
        };
    virtual ~AbstractPair() {}

};

template <class A, class B>
class ImplPair : public AbstractPair{ // Classe de implementação na qual será uma classe template para suportar os diferentes tipos 
    A first;
    B second;
    public:
        ImplPair(A a, B b): first(a), second(b){
        }

        void imprime(std::ostream& o){
            o << first << " = " << second << endl;
        };

};

class Pair {
public:
  template <typename A, typename B>
  Pair( A a, B b ) { // Classe Pair
    p = new ImplPair<A, B>(a, b);
  }
  void print(std::ostream& o) const {
        if (p) p->imprime(o);
    } 
private:
  AbstractPair *p;
};


void print( ostream& o, initializer_list<Pair> lista ) {
    for (auto x:lista){
        x.print(o);
        o << endl;
    }
}

int main() {
 
    Pair p( "1", 2 );
    p.print(cout);
  
    print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;  
}
