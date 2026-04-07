using namespace std;
class PilhaInt {
    private:
        vector<int> pilha;
        
    public:
        PilhaInt(int n = 0){
            pilha.reserve(n);
        }

        ~PilhaInt(){
            pilha = vector<int>();
        }

        PilhaInt(const PilhaInt& p ){
            pilha.reserve(p.pilha.capacity());
            for (auto x:p.pilha){
                pilha.push_back(x);
            }
        }
        
        const int capacidade(){
            return pilha.capacity();
        }

        void redimensiona(int n){
            if (int (pilha.size()) < n){
                pilha.resize(n);
            }

            else if (int(pilha.size())> n ){
                vector<int> v(n);
                for (int i = 0; i < n; i++){
                    v[i] = pilha[i];
                }
                pilha = vector<int>();
                pilha = v;
            }
        }
        
        void empilha (int valor){
            pilha.push_back(valor); 
        }
        
        int desempilha(){
            if(pilha.size() > 0){
                int desempilhado = pilha.back();
                pilha.pop_back();
                return desempilhado;
            }
            return 0;
        }
        
        void print(std::ostream& o) {
            o << "[ "; 
            for ( int i = 0; i < int(pilha.size()); i++) {
                o << pilha[i];
                if (i < int(pilha.size()) - 1) { 
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
                pilha = vector<int>();
                pilha.reserve(p.pilha.capacity());
                for (auto x:p.pilha){
                    pilha.push_back(x);
                }
            }
            return *this;
        }
        
};
