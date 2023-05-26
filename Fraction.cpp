#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
  return b != 0 ? gcd(b, a % b) : a;
}

class Fraction
{
 protected:
  int64_t num;
  int64_t denom;
 public:
  Fraction(){
    num = 0;
    denom = 1;
  }

  Fraction(int64_t n){
    num = n;
    denom = 1;
  }

  Fraction(int64_t n, int64_t d){
    num = n;
    if(d < 0) num *= -1;
    if(d != 0) denom = abs(d);
  }

  Fraction(const Fraction& f){
    num = f.num;
    denom = f.denom;
  }

  int n() const{
    return num;
  }

  void set_n(int64_t n){
    num = n;
  }

  int d() const{
    return denom;
  }

  void set_d(int64_t d){
    denom = d;
  }

  Fraction& operator=(Fraction const& f){
    num = f.num;
    denom = f.denom;
    return *this;
  }


//  унарный -
  Fraction operator-() const{
    Fraction result(0, 1);
    result.num = -1 * num;
    result.denom = denom;
    return result;
  }

  Fraction operator*(int64_t m) const{
    Fraction result(0, 1);
    result.num = num * m;
    result.denom = denom;
    int64_t com_factor = gcd(abs(m), denom);
    result.num /= com_factor;
    result.denom /= com_factor;
    return result;
  }

  Fraction operator*(const Fraction& f) const{
    Fraction result(0, 1);
    result.num = num * f.num;
    result.denom = denom * f.denom;
    int64_t com_factor = gcd(abs(result.num), result.denom);
    result.num /= com_factor;
    result.denom /= com_factor;
    return result;
  }

  Fraction operator/(const Fraction& f) const{
    Fraction result(0, 1);
    if(f.num < 0) result.num = f.denom * (-1);
    else result.num = f.denom;
    result.denom = abs(f.num);
    return *this * result;
  }


  Fraction operator+(const Fraction& f) const{
    Fraction result(0, 1);
    result.num = num * f.denom + f.num * denom;
    result.denom = denom * f.denom;
    int64_t com_factor = gcd(abs(result.num), result.denom);
    result.num /= com_factor;
    result.denom /= com_factor;
    return result;
  }

  Fraction& operator+=(Fraction const& f){
    Fraction result(*this + f);
    num = result.num;
    denom = result.denom;
    return *this;
  }

  Fraction& operator/=(Fraction const& f){
    Fraction result;
    result = *this / f;
    num = result.num;
    denom = result.denom;
    return *this;
  }

  Fraction operator-(const Fraction& f) const{
    Fraction result(0, 1);
    result.num = -1 * f.num;
    return *this + f;
  }


  bool operator==(const Fraction& f) const{
    return num == f.num && denom == f.denom;
  }

  bool operator!=(const Fraction& f) const{
  return !(*this == f);
  }

  bool operator==(const int& i) const{
    return num == denom * i;
  }

  bool operator>(const Fraction& f) const{
    return num * f.denom > denom * f.num;
  }

  bool operator<(const Fraction& f) const{
    return !(*this > f || *this == f);
  }

  bool operator<(const double& d) const{
    return num < d * denom;
  }

  friend Fraction operator*(int64_t m, const Fraction& f);
  friend ostream& operator<<(ostream& s, Fraction& f);

};


Fraction operator*(int64_t m, const Fraction& f){
  return f * m;
}

ostream& operator<<(ostream& s, Fraction& f){
  if(f.num  == 0)
    s << 0;
  else{
    if(f.denom == 1)
      s << f.num;
    else
      s << f.num << "/" << f.denom;
  }
}

Fraction abs(Fraction& f1){
  Fraction result;
  result.set_n(abs(f1.n()));
  result.set_d(f1.d());
  return result;
}
