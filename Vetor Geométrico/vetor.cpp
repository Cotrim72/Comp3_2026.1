#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

template <int N, class T>
class Vetor{
    private:
        vector<T> v;
    public:

        class MeioDoProdutoVetorial{
            public:
            vector<T> v;
            MeioDoProdutoVetorial(Vetor& b){
                v.reserve(b.v.size());
                for (auto x:b.v){
                    v.push_back(x);
                }
            }
        };

        Vetor(){
            v.reserve(N);
        }

        Vetor operator + ( const Vetor& s){
            Vetor<N,T> t;
            for (int i=0; i < N; i++){
                t.v.push_back(this->v[i] + s.v[i]);
            }
            return t;
        };

        Vetor operator - (const Vetor& s){
            Vetor<N,T> t;
            for (int i=0; i < N; i++){
                t.v.push_back(this->v[i] - s.v[i]);
            }
            return t;
        };

        MeioDoProdutoVetorial operator*() {
            return MeioDoProdutoVetorial(*this);
        };

        Vetor operator *(const MeioDoProdutoVetorial& s){
            decltype(this->v[1]*s.v[2]) i = (this->v[1]*s.v[2]) - (this->v[2]*s.v[1]);
            decltype(this->v[2]*s.v[0]) j = (this->v[2]*s.v[0]) - (this->v[0]*s.v[2]);
            decltype(this->v[0]*s.v[1]) k = (this->v[0]*s.v[1]) - (this->v[1]*s.v[0]);
            Vetor<N,decltype(this->v[0]*s.v[1])> t;
            t.v = {i,j,k};
            return t;
        }


        double operator * (const Vetor& s) const{
            double t = 0.0;
            for (int i=0; i < N; i++){
                t += this->v[i]*s.v[i];
            }
            return t;
        }

        Vetor operator * (double n) const{
            Vetor<N,double> t;
            for (int i=0; i < N; i++){
                t.v.push_back((this->v[i])*n);
            }
            return t;
        }

        const Vetor& operator= (initializer_list<T> s){
            for (auto x:s){
                v.push_back(x);
            }
            return *this;
        }

        void print(std::ostream& o) const{
            o << "[ "; 
            for ( int i = 0; i < int(v.size()); i++) {
                o << v[i];
                if (i < int(v.size()) - 1) { 
                    o << ", ";
                }
            }
            o << " ]";
        }

};
template<int N, typename T>
ostream& operator<<(ostream& os, const Vetor<N,T>& v) {
    v.print(os);
    return os;
}
template<int N, typename T>
Vetor<N,T> operator*(double n, const Vetor<N,T>& v){
    return v*n;
};

int main(){
    Vetor< 3, double> a, b;
    int caso;
  double x, y, z;
  
    cin >> caso >> x >> y >> z;
    a = { x, y, z };
    b = { 1, 2, 3 };
    switch( caso ) {
        case 1: cout << a << endl; break;
        case 2: cout << a + b << endl; break;
        case 3: {
            Vetor< 3, double> c;
            c = a ** b; 
            cout << c << endl;
            break; 
        }
        case 4: cout << a * b << endl; break;
        case 5: cout << a * 3.0 << endl; break;
        case 6: cout << 2.1 * a << endl; break;
        case 7: cout << a + b + a * 2.0 << endl; break;
    }
  
    return 0;
};
