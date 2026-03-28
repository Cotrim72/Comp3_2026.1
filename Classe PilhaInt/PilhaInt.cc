class PilhaInt {
    private:
        int pilha[100];
        int index;
        
    public:
        PilhaInt(){
            for(int i = 0; i < 100; i++){
                pilha[i] = 0;
            }
            index = 0;
        }
        
        void empilha (int valor){
            pilha[index++] = valor; 
        }
        
        int desempilha(){
            return pilha[--index];
        }
        
        void print(std::ostream& o) {
            o << "[ "; 
            for (int i = 0; i < index; i++) {
                o << pilha[i];
                if (i < index - 1) { 
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
                index = p.index;
                for( int i = 0; i < p.index; i++ ) {
                    pilha[i] = p.pilha[i];
                }
            }
            return p;
    }
    
};
