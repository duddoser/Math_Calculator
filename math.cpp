
#include <iostream>



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




int main()
{
    cout << cos(3*pi/2);
}

