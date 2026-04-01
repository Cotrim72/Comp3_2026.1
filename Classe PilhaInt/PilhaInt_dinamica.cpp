#include <iostream>
#include <sstream>

using namespace std;
class PilhaInt {
    private:
        int tamanho;
        int capacity;
        int* Pointer_tab;
        
    public:
        PilhaInt(int capacity = 10){
            this->capacity = capacity;
            Pointer_tab = (int*) malloc( capacity * sizeof(int) );
            // if (!arr) { perror("malloc"); return 1; }

            for(int i = 0; i < capacity; i++){
                Pointer_tab[i] = 0;
            }
            tamanho = 0;
        }

        ~PilhaInt(){
            free(Pointer_tab);
        }
        PilhaInt(const PilhaInt& p ){
            Pointer_tab = (int*) malloc( p.capacity * sizeof(int) );
            capacity = p.capacity;
            for (int i = 0; i < p.capacity; i++){
              Pointer_tab[i] = p.Pointer_tab[i];
            }
            tamanho = p.tamanho;

        }
        
        int capacidade(){
            return capacity;
        }

        void redimensiona(int n){
            if (capacity < n){
                int* tmp = (int*) realloc( Pointer_tab, n * sizeof(int) );
                //if (!tmp) { perror("realloc"); free(Pointer_tab); return 1; }
                Pointer_tab = tmp;
            }
            else if (capacity > n && tamanho > n){
                while (tamanho > n){
                    desempilha();
                }
            }
            capacity = n;
        }
        
        void empilha (int valor){
            if (tamanho == capacity) {
            capacity *= 2;
            int* tmp = (int*) realloc( Pointer_tab, capacity * sizeof(int) );
            //if (!tmp) { perror("realloc"); free(Pointer_tab); return 1; }
            Pointer_tab = tmp;
            }
            Pointer_tab[tamanho++] = valor; 
        }
        
        int desempilha(){
            return Pointer_tab[--tamanho];
        }
        
        void print(std::ostream& o) {
            o << "[ "; 
            for (int i = 0; i < tamanho; i++) {
                o << Pointer_tab[i];
                if (i < tamanho - 1) { 
                    o << ", ";
                }
            }
            o << " ]";
        }
        
        PilhaInt& operator << (int valor) {
            empilha( valor );
            return *this;
        }
        
        const PilhaInt& operator= ( const PilhaInt& p ){
            if( this != &p ) {
                free(Pointer_tab);
                Pointer_tab = (int*) malloc( p.capacity * sizeof(int) );
                for (int i = 0; i < p.capacity; i++){
                    Pointer_tab[i] = p.Pointer_tab[i];
                }
                tamanho = p.tamanho;
                capacity = p.capacity;
            }
            return *this;
        }
        
};

int main(){
    //Teste1
    PilhaInt p;
    p.empilha( 1 );
    p << 3 << 9 << 13 << 89;
    std::cout << p.desempilha() << std::endl;
    std::cout << p.desempilha() << std::endl;
    p.print( std::cout );
    p << 19 << 18 << 17 << 30;
    std::stringstream ss;
    p.print( ss );
    std::cout << std::endl << "{" << ss.str() << "}" << std::endl;
    /**
    //Teste2
    PilhaInt a(5), b(15);
    cout << a.capacidade() << endl;
    cout << b.capacidade() << endl;
    /**
    PilhaInt a( 7 );
    a << 3 << 5 << 13 << 19;
    PilhaInt b{ embaralha( a ) };
    a.print( cout ); cout << endl;
    b.print( cout ); cout << endl;
    
    //Teste4
    PilhaInt a{7}, b{500}, c{5};
    a << 8 << 3 << 1 << 4 << 5;
    b << 1 << 2 << 3;
    c = a;
    a = b;
    b = c;
    c.desempilha();
    c << 7;
    a.print( cout ); cout << endl;
    b.print( cout ); cout << endl;
    c.print( cout ); cout << endl;
    //Teste5
    PilhaInt a{7}, b{500000}, c{5};
    a << 8 << 3 << 1 << 4 << 5;
    for( int i = 0; i < b.capacidade(); i++ )
    b << i;
    c = a;
    a = b;
    b = c;
    cout << a.capacidade() << ", " << b.capacidade() << ", " << c.capacidade() << endl;
    //Teste6
    
    PilhaInt a{7};
    a << 8 << 3 << 1 << 4 << 5;
    a = a;
    a.print( cout ); cout << endl;
    //Teste7
    PilhaInt a{81};
    a << 5 << 6 << 3 << 2 << 9 << 13;
    a.redimensiona( 81 ); cout << a.capacidade() << endl;
    a.redimensiona( 11 ); cout << a.capacidade() << endl;
    a.redimensiona( 6 ); cout << a.capacidade() << endl;
    a.print( cout ); cout << endl;
    a.redimensiona( 3 ); cout << a.capacidade() << endl;
    a.print( cout ); cout << endl;
    */
    //Teste8
    PilhaInt a{3};
    for( int i = 0; i < 20; i++ ) {
        a << i;
        cout << a.capacidade() << " ";
    }
    cout << endl;
    a.print( cout ); cout << endl;
}