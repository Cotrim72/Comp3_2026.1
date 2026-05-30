#include <iostream>
#include <map>
#include <memory>
#include <sstream>

using namespace std;

class Var {
    public:
        class Int;
        class Double;
        class String;
        class Bool;
        class Char;
        class Erro;
        template<typename T, size_t N> class Array;
        template <typename Lambda> class Function;
        class Undefined { 
            public:
                virtual ~Undefined() = default;
                virtual shared_ptr<Undefined> clone() const = 0;

                virtual shared_ptr<Undefined> add( const Undefined& rhs ) const = 0;
                virtual shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const = 0;
                virtual shared_ptr<Undefined> addToDouble( const Double& lhs ) const = 0;
                virtual shared_ptr<Undefined> addToString( const String& lhs ) const = 0;
                virtual shared_ptr<Undefined> addToChar( const Char& lhs ) const = 0;
                virtual shared_ptr<Undefined> sub( const Undefined& rhs ) const = 0;
                virtual shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const = 0;
                virtual shared_ptr<Undefined> subToDouble( const Double& lhs ) const = 0;
                virtual shared_ptr<Undefined> subToString( const String& lhs ) const = 0;
                virtual shared_ptr<Undefined> subToChar( const Char& lhs ) const = 0;
                virtual shared_ptr<Undefined> div( const Undefined& rhs ) const = 0;
                virtual shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const = 0;
                virtual shared_ptr<Undefined> divToDouble( const Double& lhs ) const = 0;
                virtual shared_ptr<Undefined> divToString( const String& lhs ) const = 0;
                virtual shared_ptr<Undefined> divToChar( const Char& lhs ) const = 0;
                virtual shared_ptr<Undefined> mult( const Undefined& rhs ) const = 0;
                virtual shared_ptr<Undefined> multToInt   ( const Int&    lhs ) const = 0;
                virtual shared_ptr<Undefined> multToDouble( const Double& lhs ) const = 0;
                virtual shared_ptr<Undefined> multToString( const String& lhs ) const = 0;
                virtual shared_ptr<Undefined> multToChar( const Char& lhs ) const = 0;
                virtual shared_ptr<Undefined> menor_que( const Undefined& rhs ) const = 0;
                virtual shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const = 0;
                virtual shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const = 0;
                virtual shared_ptr<Undefined> menor_queToString( const String& lhs ) const = 0;
                virtual shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const = 0;
                virtual shared_ptr<Undefined> and1( const Undefined& rhs ) const = 0;
                virtual shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const = 0;
                virtual shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const = 0;
                virtual shared_ptr<Undefined> and1ToString( const String& lhs ) const = 0;
                virtual shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const = 0;
                virtual shared_ptr<Undefined> and1ToChar( const Char& lhs ) const = 0;
                virtual shared_ptr<Undefined> or1( const Undefined& rhs ) const = 0;
                virtual shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const = 0;
                virtual shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const = 0;
                virtual shared_ptr<Undefined> or1ToString( const String& lhs ) const = 0;
                virtual shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const = 0;
                virtual shared_ptr<Undefined> or1ToChar( const Char& lhs ) const = 0;
                virtual shared_ptr<Undefined> not1() const = 0;
                virtual string toString() const = 0;
                virtual shared_ptr<Undefined> call(const Var& arg) const = 0;
                virtual Var& get_value(string s) = 0;
                virtual bool eh_funcao() const { return false; }
                virtual bool eh_objeto() const { return false; }
                virtual void imprime(ostream& o) const = 0;

        };

        class Int : public Undefined { 
            public: 
                int v;
                Int(int v): v(v){}
                shared_ptr<Undefined> clone() const override { return make_shared<Int>(v);}
                shared_ptr<Undefined> add( const Undefined& rhs ) const override { return rhs.addToInt( *this );}
                shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const override { return make_shared<Int>( lhs.v + v );}
                shared_ptr<Undefined> addToDouble( const Double& lhs ) const override{ return make_shared<Double>( lhs.v + v );}
                shared_ptr<Undefined> addToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> sub( const Undefined& rhs ) const override{ return rhs.subToInt(*this);}
                shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const override{ return make_shared<Int>(lhs.v - v);}
                shared_ptr<Undefined> subToDouble( const Double& lhs ) const override{ return make_shared<Double>(lhs.v -v);}
                shared_ptr<Undefined> subToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> div( const Undefined& rhs ) const override {return rhs.divToInt(*this);}
                shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const override {return make_shared<Double>(lhs.v/v);}
                shared_ptr<Undefined> divToDouble( const Double& lhs ) const override {return make_shared<Double>(lhs.v/v);}
                shared_ptr<Undefined> divToString( const String& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> mult( const Undefined& rhs ) const override{return rhs.multToInt(*this);}
                shared_ptr<Undefined> multToInt   ( const Int&    lhs ) const override{return make_shared<Int>(lhs.v * v);}
                shared_ptr<Undefined> multToDouble( const Double& lhs ) const override{return make_shared<Double>(lhs.v * v);}
                shared_ptr<Undefined> multToString( const String& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_que( const Undefined& rhs ) const override{return rhs.menor_queToInt(*this);}
                shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v < v);}
                shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v < v);}
                shared_ptr<Undefined> menor_queToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1( const Undefined& rhs ) const override{return rhs.and1ToInt(*this);}
                shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v && v);}
                shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v && v);}
                shared_ptr<Undefined> and1ToString( const String& lhs ) const override{return make_shared<Bool>(!lhs.v.empty() && (v != 0));}
                shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1( const Undefined& rhs ) const override{return rhs.or1ToInt(*this);}
                shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v || v);}
                shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v || v);}
                shared_ptr<Undefined> or1ToString( const String& lhs ) const override{return make_shared<Bool>(!lhs.v.empty() || (v != 0));}
                shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> not1() const override{return make_shared<Bool>(!v);}
                shared_ptr<Undefined> addToChar( const Char& lhs ) const override {return make_shared<Int>(int(lhs.v)+v);}
                shared_ptr<Undefined> subToChar( const Char& lhs ) const override {return make_shared<Int>(int(lhs.v)-v);}
                shared_ptr<Undefined> divToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> multToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const override{return make_shared<Int>(int(lhs.v)<v);}
                shared_ptr<Undefined> and1ToChar( const Char& lhs ) const override{return make_shared<Int>(int(lhs.v)&&v);}
                shared_ptr<Undefined> or1ToChar( const Char& lhs ) const override{return make_shared<Int>(int(lhs.v)||v);}
                shared_ptr<Undefined> call(const Var& arg) const override{return nullptr;}
                Var& get_value(string s) override {throw Var::Erro("Essa variável não é um objeto");}
                string toString() const override { return to_string( v ); }
                void imprime(ostream& o) const override{ o << v;}
        };
        class Double : public Undefined {
            public: 
                double v;
                Double(double v): v(v){}
                shared_ptr<Undefined> clone() const override { return make_shared<Double>(v);}
                shared_ptr<Undefined> add( const Undefined& rhs ) const override { return rhs.addToDouble( *this );}
                shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const override { return make_shared<Double>( lhs.v + v );}
                shared_ptr<Undefined> addToDouble( const Double& lhs ) const override{ return make_shared<Double>( lhs.v + v );}
                shared_ptr<Undefined> addToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> sub( const Undefined& rhs ) const override{ return rhs.subToDouble(*this);}
                shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const override{ return make_shared<Double>(lhs.v - v);}
                shared_ptr<Undefined> subToDouble( const Double& lhs ) const override{ return make_shared<Double>(lhs.v - v);}
                shared_ptr<Undefined> subToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> div( const Undefined& rhs ) const override {return rhs.divToDouble(*this);}
                shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const override{return make_shared<Double>(lhs.v/v);}
                shared_ptr<Undefined> divToDouble( const Double& lhs ) const override{return make_shared<Double>(lhs.v/v);}
                shared_ptr<Undefined> divToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> mult( const Undefined& rhs ) const override{return rhs.multToDouble(*this);}
                shared_ptr<Undefined> multToInt   ( const Int&    lhs ) const override{return make_shared<Double>(lhs.v * v);}
                shared_ptr<Undefined> multToDouble( const Double& lhs ) const override{return make_shared<Double>(lhs.v * v);}
                shared_ptr<Undefined> multToString( const String& lhs ) const override {return nullptr;}
                string toString() const override { return to_string( v ); }
                shared_ptr<Undefined> menor_que( const Undefined& rhs ) const override{return rhs.menor_queToDouble(*this);}
                shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v < v);}
                shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v < v);}
                shared_ptr<Undefined> menor_queToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1( const Undefined& rhs ) const override{return rhs.and1ToDouble(*this);}
                shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v && v);}
                shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v && v);}
                shared_ptr<Undefined> and1ToString( const String& lhs ) const override{return make_shared<Bool>(!lhs.v.empty() && (v != 0.0));}
                shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> or1( const Undefined& rhs ) const override{return rhs.or1ToDouble(*this);}
                shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v || v);}
                shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v || v);}
                shared_ptr<Undefined> or1ToString( const String& lhs ) const override{return make_shared<Bool>(!lhs.v.empty() || (v != 0.0));}
                shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> not1() const override{return make_shared<Bool>(!v);}
                shared_ptr<Undefined> addToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> subToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> divToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> multToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> call(const Var& arg) const override{return nullptr;}
                Var& get_value(string s) override {throw Var::Erro("Essa variável não é um objeto");}
                void imprime(ostream& o) const override{ o << v;}
        };
        class String : public Undefined {
            public:
                string v;
                String( const string& v): v(v){}
                shared_ptr<Undefined> clone() const override { return make_shared<String>(v);}
                shared_ptr<Undefined> add( const Undefined& rhs ) const override {return rhs.addToString( *this ); }
                shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const override { return nullptr;}
                shared_ptr<Undefined> addToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> addToString( const String& lhs ) const override{ return make_shared<String>( lhs.v + v);}
                shared_ptr<Undefined> sub( const Undefined& rhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> div( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> mult( const Undefined& rhs ) const override{return rhs.multToString(*this);}
                shared_ptr<Undefined> multToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToString( const String& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_que( const Undefined& rhs ) const override{return rhs.menor_queToString(*this);}
                shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToString( const String& lhs ) const override{return make_shared<Bool>(lhs.v < v);}
                shared_ptr<Undefined> and1( const Undefined& rhs ) const override{return rhs.and1ToString(*this);}
                shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v != 0 && !v.empty());}
                shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v != 0.0 && !v.empty());}
                shared_ptr<Undefined> and1ToString( const String& lhs ) const override{return make_shared<Bool>(!lhs.v.empty() && !v.empty());}
                shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> or1( const Undefined& rhs ) const override{return rhs.or1ToString(*this);}
                shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v != 0 || !v.empty());}
                shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const override{return make_shared<Bool>(lhs.v != 0.0 || !v.empty());}
                shared_ptr<Undefined> or1ToString( const String& lhs ) const override{return make_shared<Bool>(!lhs.v.empty() || !v.empty());}
                shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> not1() const override{return nullptr;}
                string toString() const override { return v; }
                shared_ptr<Undefined> addToChar( const Char& lhs ) const override {return make_shared<String>(lhs.v+v);}
                shared_ptr<Undefined> subToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> divToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> multToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const override{
                    string s(1, (char)lhs.v);
                    return make_shared<Bool>(s < v);
                }
                shared_ptr<Undefined> and1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> call(const Var& arg) const override{return nullptr;}
                Var& get_value(string s) override {throw Var::Erro("Essa variável não é um objeto");}
                void imprime(ostream& o) const override{ o << v;}
        };
        class Char : public Undefined {
            public:
                char v;
                Char( char v): v(v){}
                shared_ptr<Undefined> clone() const override { return make_shared<Char>(v);}
                shared_ptr<Undefined> add( const Undefined& rhs ) const override {return rhs.addToChar( *this ); }
                shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const override { return make_shared<Int>(lhs.v + int(v));}
                shared_ptr<Undefined> addToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> addToString( const String& lhs ) const override{ return make_shared<String>( lhs.v + v);}
                shared_ptr<Undefined> sub( const Undefined& rhs ) const override{ return rhs.subToChar(*this);}
                shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const override{ return make_shared<Int>(lhs.v - int(v));}
                shared_ptr<Undefined> subToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> div( const Undefined& rhs ) const override{return rhs.divToChar(*this);}
                shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> mult( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToInt   ( const Int&    lhs ) const override{ return make_shared<Int>(lhs.v*int(v));}
                shared_ptr<Undefined> multToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> multToString( const String& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_que( const Undefined& rhs ) const override{return rhs.menor_queToChar(*this);}
                shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v < int(v));}
                shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToString( const String& lhs ) const override{
                    string s(1, (char)v);
                    return make_shared<Bool>(lhs.v < s);
                }
                shared_ptr<Undefined> and1( const Undefined& rhs ) const override{return rhs.and1ToChar(*this);}
                shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v && int(v));}
                shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> or1( const Undefined& rhs ) const override{return rhs.or1ToChar(*this);}
                shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const override{return make_shared<Bool>(lhs.v || int(v));}
                shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> not1() const override{return nullptr;}
                shared_ptr<Undefined> addToChar( const Char& lhs ) const override {
                    string s = {lhs.v};
                    string s2 = {v};
                    return make_shared<String>(s+s2);
                }
                shared_ptr<Undefined> subToChar( const Char& lhs ) const override {return make_shared<Int>(lhs.v-v);}
                shared_ptr<Undefined> divToChar( const Char& lhs ) const override {return make_shared<Int>(lhs.v/v);}
                shared_ptr<Undefined> multToChar( const Char& lhs ) const override {return make_shared<Int>(lhs.v*v);}
                shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const override{return nullptr;;}
                shared_ptr<Undefined> and1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> call(const Var& arg) const override{return nullptr;}
                Var& get_value(string s) override {throw Var::Erro("Essa variável não é um objeto");}
                string toString() const override { return to_string(v); }
                void imprime(ostream& o) const override{ o << v;}
        };
        class Bool : public Undefined {
            public:
                bool v;
                Bool( bool v): v(v){}
                shared_ptr<Undefined> clone() const override { return make_shared<Bool>(v);}
                shared_ptr<Undefined> add( const Undefined& rhs ) const override {return nullptr;}
                shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const override { return nullptr;}
                shared_ptr<Undefined> addToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> addToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> sub( const Undefined& rhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> div( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> mult( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToInt   ( const Int&    lhs )const override{return nullptr;}
                shared_ptr<Undefined> multToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToString( const String& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_que( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1( const Undefined& rhs ) const override{return rhs.and1ToBool(*this);}
                shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const override{return make_shared<Bool>(lhs.v && v);}
                shared_ptr<Undefined> or1( const Undefined& rhs ) const override{return rhs.or1ToBool(*this);}
                shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const override{return make_shared<Bool>(lhs.v || v);}
                shared_ptr<Undefined> not1() const override{return make_shared<Bool>(!v);}
                shared_ptr<Undefined> addToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> subToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> divToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> multToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const override{return nullptr;;}
                shared_ptr<Undefined> and1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> call(const Var& arg) const override{return nullptr;}
                Var& get_value(string s) override {throw Var::Erro("Essa variável não é um objeto");}
                string toString() const override { return to_string(v); }
                void imprime(ostream& o) const override{o << boolalpha << v;}
            };

        template<typename T, size_t N>
        class Array : public Undefined {
            public:
                T data[N];
                Array( const T (&arr)[N]){for (size_t i = 0; i < N; ++i) { data[i] = arr[i];}}
                shared_ptr<Undefined> clone() const override { return make_shared<Array>(data);}
                shared_ptr<Undefined> add( const Undefined& rhs ) const override {return nullptr;}
                shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const override { return nullptr;}
                shared_ptr<Undefined> addToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> addToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> sub( const Undefined& rhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> div( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> mult( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToInt   ( const Int&    lhs )const override{return nullptr;}
                shared_ptr<Undefined> multToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToString( const String& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_que( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> not1() const override{return nullptr;}
                shared_ptr<Undefined> addToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> subToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> divToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> multToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const override{return nullptr;;}
                shared_ptr<Undefined> and1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> call(const Var& arg) const override{return nullptr;}
                Var& get_value(string s) override {throw Var::Erro("Essa variável não é um objeto");}
                string toString() const override {
                    stringstream ss;
                    ss << "[";
                    for (size_t i = 0; i < N; ++i) {
                        ss << data[i];
                        if (i < N - 1) {
                            ss << ", "; 
                        }
                    }
                    ss << "]";
                    return ss.str();
                }
                void imprime(ostream& o) const override{
                    for(auto&x : data)
                        o << x;
                }
            };
        template <typename Lambda>
        class Function : public Undefined {
            private:
                Lambda lambda;
            public:
                Function(Lambda L) : lambda(L) {}
                shared_ptr<Undefined> clone() const override { return make_shared<Function<Lambda>>(lambda);}
                string toString() const override {return "function";}
                void imprime(ostream& o) const override { o << toString();}
                shared_ptr<Undefined> add(const Undefined& rhs) const override { return nullptr; }
                shared_ptr<Undefined> addToInt(const Int& lhs) const override { return nullptr; }
                shared_ptr<Undefined> addToDouble(const Double& lhs) const override { return nullptr; }
                shared_ptr<Undefined> addToString(const String& lhs) const override { return nullptr; }
                shared_ptr<Undefined> addToChar(const Char& lhs) const override { return nullptr; }
                shared_ptr<Undefined> sub(const Undefined& rhs) const override { return nullptr; }
                shared_ptr<Undefined> subToInt(const Int& lhs) const override { return nullptr; }
                shared_ptr<Undefined> subToDouble(const Double& lhs) const override { return nullptr; }
                shared_ptr<Undefined> subToString(const String& lhs) const override { return nullptr; }
                shared_ptr<Undefined> subToChar(const Char& lhs) const override { return nullptr; }
                shared_ptr<Undefined> div(const Undefined& rhs) const override { return nullptr; }
                shared_ptr<Undefined> divToInt(const Int& lhs) const override { return nullptr; }
                shared_ptr<Undefined> divToDouble(const Double& lhs) const override { return nullptr; }
                shared_ptr<Undefined> divToString(const String& lhs) const override { return nullptr; }
                shared_ptr<Undefined> divToChar(const Char& lhs) const override { return nullptr; }
                shared_ptr<Undefined> mult(const Undefined& rhs) const override { return nullptr; }
                shared_ptr<Undefined> multToInt(const Int& lhs) const override { return nullptr; }
                shared_ptr<Undefined> multToDouble(const Double& lhs) const override { return nullptr; }
                shared_ptr<Undefined> multToString(const String& lhs) const override { return nullptr; }
                shared_ptr<Undefined> multToChar(const Char& lhs) const override { return nullptr; }
                shared_ptr<Undefined> menor_que(const Undefined& rhs) const override { return nullptr; }
                shared_ptr<Undefined> menor_queToInt(const Int& lhs) const override { return nullptr; }
                shared_ptr<Undefined> menor_queToDouble(const Double& lhs) const override { return nullptr; }
                shared_ptr<Undefined> menor_queToString(const String& lhs) const override { return nullptr; }
                shared_ptr<Undefined> menor_queToChar(const Char& lhs) const override { return nullptr; }
                shared_ptr<Undefined> and1(const Undefined& rhs) const override { return nullptr; }
                shared_ptr<Undefined> and1ToInt(const Int& lhs) const override { return nullptr; }
                shared_ptr<Undefined> and1ToDouble(const Double& lhs) const override { return nullptr; }
                shared_ptr<Undefined> and1ToString(const String& lhs) const override { return nullptr; }
                shared_ptr<Undefined> and1ToBool(const Bool& lhs) const override { return nullptr; }
                shared_ptr<Undefined> and1ToChar(const Char& lhs) const override { return nullptr; }
                shared_ptr<Undefined> or1(const Undefined& rhs) const override { return nullptr; }
                shared_ptr<Undefined> or1ToInt(const Int& lhs) const override { return nullptr; }
                shared_ptr<Undefined> or1ToDouble(const Double& lhs) const override { return nullptr; }
                shared_ptr<Undefined> or1ToString(const String& lhs) const override { return nullptr; }
                shared_ptr<Undefined> or1ToBool(const Bool& lhs) const override { return nullptr; }
                shared_ptr<Undefined> or1ToChar(const Char& lhs) const override { return nullptr; }
                shared_ptr<Undefined> not1() const override { return nullptr; }
                shared_ptr<Undefined> call(const Var& arg) const override {
                    Var resultado = lambda(arg); 
                    return resultado.p; 
                }
                Var& get_value(string s) override {throw Var::Erro("Essa variável não é um objeto");}
                bool eh_funcao() const { return true; }
            };
        class Object : public Undefined { 
            map<string,Var> atributos;
            public:
                Object(){}
                shared_ptr<Undefined> clone() const override { return make_shared<Object>();}
                Var& get_value(string s) override {
                    if (atributos.find(s) == atributos.end()) {
                        atributos[s] = Var();
                    }
                    return atributos[s]; 
                }
                shared_ptr<Undefined> add( const Undefined& rhs ) const override {return nullptr;}
                shared_ptr<Undefined> addToInt   ( const Int&    lhs ) const override { return nullptr;}
                shared_ptr<Undefined> addToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> addToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> sub( const Undefined& rhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToInt   ( const Int&    lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToDouble( const Double& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> subToString( const String& lhs ) const override{ return nullptr;}
                shared_ptr<Undefined> div( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> divToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> mult( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToInt   ( const Int&    lhs )const override{return nullptr;}
                shared_ptr<Undefined> multToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> multToString( const String& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_que( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> menor_queToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> and1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1( const Undefined& rhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToInt   ( const Int&    lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToDouble( const Double& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToString( const String& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToBool( const Bool& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> not1() const override{return nullptr;}
                shared_ptr<Undefined> addToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> subToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> divToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> multToChar( const Char& lhs ) const override {return nullptr;}
                shared_ptr<Undefined> menor_queToChar( const Char& lhs ) const override{return nullptr;;}
                shared_ptr<Undefined> and1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> or1ToChar( const Char& lhs ) const override{return nullptr;}
                shared_ptr<Undefined> call(const Var& arg) const override{return nullptr;}
                virtual bool eh_objeto() const { return true; }
                string toString() const override {return "object";}
                void imprime(ostream& o) const override { o << toString();}
        };
        class Erro {
            public:
                Erro( string msg ): msg(msg) {}
 
                string operator()() const { return msg; }
                
            private:
                string msg;
        };

        Var(){}                         
        Var( int v ){ p = shared_ptr<Undefined>{new Int(v)}; }                   
        Var( double v ){ p = shared_ptr<Undefined>{new Double(v)}; }                
        Var( const char* v ){ p = shared_ptr<Undefined>{new String(v)}; } 
        Var( char v ) {p = shared_ptr<Undefined>{new Char(v)}; }          
        Var( const string& v ){ p = shared_ptr<Undefined>{new String(v)}; }
        Var( bool v){p = shared_ptr<Undefined>{new Bool(v)};}

        template<typename T, size_t N>
        Var(T (&arr)[N]){ p = shared_ptr<Undefined>{new Array<T,N>(arr)};}

        template <typename Lambda>
        Var(Lambda L){p = shared_ptr<Undefined>{new Function(L)};}

        void print(ostream& os){
            if (p) 
                p->imprime(os);
            else
                os << "undefined";
        }
        Var operator+( const Var& rhs ) const {
            Var res;
            res.p = p->add(*rhs.p);
            return res;
        }
        Var operator-( const Var& rhs) const{
            Var res;
            res.p = p->sub(*rhs.p);
            return res;
        }

        Var operator /(const Var& rhs) const{
            Var res;
            res.p = p->div(*rhs.p);
            return res;
        }
        Var operator *(const Var& rhs) const{
            Var res;
            res.p = p->mult(*rhs.p);
            return res;
        }
        Var operator <(const Var& rhs) const{
            Var res;
            res.p = p->menor_que(*rhs.p);
            return res;
        }
        Var operator &&(const Var& rhs) const{
            Var res;
            res.p = p->and1(*rhs.p);
            return res;
        }

        Var operator || (const Var& rhs) const{
            Var res;
            res.p = p->or1(*rhs.p);
            return res;
        }

        Var operator !(){
            Var res;
            if (p) res.p = p->not1();
            return res;
        }

        Var operator()(auto x) {
            Var res;
            if (!p) throw Erro("Essa variável não pode ser usada como função");
            if (!(p->eh_funcao())) throw Erro("Essa variável não pode ser usada como função");
            if (p) res.p = p->call(Var(x)); 
            return res;
        }

        Var operator()(Var x) {
            Var res;
            if (!p) throw Erro("Essa variável não pode ser usada como função");
            if (!(p->eh_funcao())) throw Erro("Essa variável não pode ser usada como função");
            if (p) res.p = p->call(x);
            return res; 
        }

        Var& operator[](string s) {
            if (!p) p = make_shared<Object>(); 
            if (!(p->eh_objeto()))throw Erro("Essa variável não é um objeto");
            return p->get_value(s); 
        }
        Var operator[](string s) const {
            if (!p) return Var();
            if (!(p->eh_objeto())) throw Erro("Essa variável não é um objeto");
            if (auto obj = dynamic_pointer_cast<Object>(p)) return obj->get_value(s);
            return Var();
        }
        shared_ptr<Undefined> p;
};

ostream& operator << (ostream& os, Var x){
    x.print(os);
    return os;
}

Var operator - (auto x, Var y){
    Var l = x;
    return l - y;
}

Var operator / ( auto x, Var y){
    Var l = x;
    return l/y;
}

Var operator * (auto x, Var y){
    Var l = x;
    return l*y;
}

Var operator <(auto x, Var y){
    Var l = x;
    return l < y;
}

Var operator &&(auto x, Var y){
    Var l = x;
    return l && y;
}

Var operator ||(auto x, Var y){
    Var l = x;
    return l || y;
}

Var newObject(){
    Var res;
    res.p = shared_ptr<Var::Undefined>{new Var::Object};
    return res;
}

Var operator > ( const Var& a, const Var& b ) { return b<a; }
Var operator != ( const Var& a, const Var& b ) { return (a<b) || (b<a); }
Var operator == ( const Var& a, const Var& b ) { return !(a!=b); }
Var operator <= ( const Var& a, const Var& b ) { return !(b<a); }
Var operator >= ( const Var& a, const Var& b ) { return !(a<b); }
