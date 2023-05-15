
#include <iostream>
#include <vector>


using namespace std;

int n = 10; //это для рядов ^^
double pi = 3.14159265; // мы калькулятор
double e = 2.71828183; // экспонента
double eps = 0.000000001; // эпсилон для сравнений


double sum(double a, double b)
{
    return a + b;
}

double subtraction(double a, double b)
{
    return a - b;
}

double multiplication(double a, double b)
{
    return a * b;
}

double division(double a, double b)
{
    if (b != 0)
        return a / b;
    //else
}

int factorial(int a)
{
    int res = 1;
    for (int i = 1; i <= a; i++)
        res *= i;
    return res;
}


double tg(double a)
{
    return (sin(a) / cos(a));
}

double ctg(double a)
{
    return (cos(a) / sin(a));
}

double sh(double a)
{
    return((exp(a) - exp(-a)) / 2);
}

double ch(double a)
{
    return((exp(a) + exp(-a)) / 2);
}

double lin_ur(double a, double b) //ax+b=0
{
    return (-b / a);
}

vector<double> cv_ur(double a, double b, double c) //ax^2+bx+c=0
{
    double x1, x2;
    int n;
    vector<double> res;
    double D = (b * b - 4 * a * c);
    if (D == 0)
    {
        x1 = (-b / (2 * a));
        n = 1;
        res.push_back(x1);
    }

    if (D > 0)
    {
        double Ds = sqrt(D);
        x1 = (-b + Ds) / (2 * a);
        x2 = (-b - Ds) / (2 * a);
        n = 2;
        res.push_back(x1);
        res.push_back(x2);
    }

    //if (D < 0) 
    return res;
}

template<class T>
class Uravnenie
{
protected:
    T* coef; // коэффициенты
    int n; // порядок уравнения
public:
    Uravnenie()
    {
        n = 0;
        coef = nullptr;
    }

    Uravnenie(int N)
    {
        n = N;
        coef = (T*)new T[n];
        for (int i = 0; i < n; i++)
            coef[i] = 0;
    }

    Uravnenie(const Uravnenie& u)
    {
        n = u.n;
        coef = (T*)new T[n];
        for (int i = 0; i < n; i++)
            coef[i] = u.coef[i];
    }

    Uravnenie(T* c, int n)
    {

    }
};


int main()
{
    vector <double> a = cv_ur(1,3,-4);
    for (auto i: a)
        cout << i << ' ';
}

