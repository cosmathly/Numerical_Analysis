#ifndef _EquationSolver_
#define _EquationSolver_
typedef double (*Func)(double);
typedef unsigned int u_int;
int Sgn(double x);
double Abs(double x);
class EquationSolver
{
   public:
    virtual double solve() = 0;
};
class Bisection: public EquationSolver
{
   private:
   struct Input 
   {
    Func f;
    double a, b;
    u_int M;
    double delta;
    double epsilon;
    bool Preconditions()
    {
      if(Sgn(f(a))!=Sgn(f(b))) return true;
      else return false;
    }
    Input(Func _f, double _a, double _b, u_int _M, double _delta, double _epsilon):f(_f),
    a(_a), b(_b), M(_M), delta(_delta), epsilon(_epsilon) {} 
    ~Input() = default;
   };
   Input input;
   struct Output
   {
     double c, h;
     u_int k;
     bool Postconditions(const Input &_input) 
     {
       if(Abs(_input.f(c))<_input.epsilon||Abs(h)<_input.delta||k==_input.M) return true;
       else return false;
     }
     Output(double _c, double _h, u_int _k):c(_c), h(_h), k(_k) {}
     ~Output() = default;
   }
   Output output;
   public:
   Output solve();
};
class Newton: public EquationSolver
{
   public:
   Output solve();
};
class Secant: public EquationSolver
{
   public:
   Output solve();
};
#endif