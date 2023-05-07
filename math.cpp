
#include <iostream>


using namespace std;



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

double pow(double a, double b)
{
    //лол мне самой или можно cmath?
}

double abs(double a)
{
    if (a >= 0)
        return a;
    if (a < 0)
        return -a;
}

int factorial(int a)
{
    int res = 1;
    for (int i = 0; i <= a; i++)
        res *= i;
}



int main()
{
    std::cout << "Hello World!\n";
}

