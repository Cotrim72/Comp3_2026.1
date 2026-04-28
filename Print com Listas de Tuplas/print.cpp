#include <initializer_list>
#include <iostream>
#include <memory>

using namespace std;

class AbstractPair{ 
    public:
        virtual void imprime(std::ostream& o){
        };
    virtual ~AbstractPair() {}

};

template <class A, class B>
class ImplPair : public AbstractPair{ 
    A first;
    B second;
    public:
        ImplPair(const A& a, const B& b): first(a), second(b){
        }

        void imprime(std::ostream& o){
            o << first << " = " << second << endl;
        };

};

class Pair {
public:
  template <typename A, typename B>
  Pair( A a, B b ) { 
    p = shared_ptr<AbstractPair>{new ImplPair<A, B>(a, b)};
  }
  void print(std::ostream& o) const {
        if (p) p->imprime(o);
    } 
private:
    shared_ptr<AbstractPair> p;
};


void print( ostream& o, initializer_list<Pair> lista ) {
    for (const auto& x:lista){
        x.print(o);
    }
}

int main() {
 
    Pair p( "1", 2 );
    p.print(cout);
  
    print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;  
}
