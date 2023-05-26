﻿#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Fraction.cpp"
#include "Matrix.cpp"




using namespace std;

int n = 10; //это для рядов ^^
double pi = 3.14159265; // мы калькулятор
double e = 2.71828183; // экспонента
const double eps = 0.000000001; // эпсилон для сравнений
const int drob = 1000000;


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

//сашка если что функции sin(), cos(), exp(), log(), log10(), pow(a,b), abs(), sqrt() юзай

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

double det(int n, vector<double> mat) //определитель только для квадратных матриц размера n
{
    double res = 1;
    vector<double> vec = mat;
    
    for (int i = 0; i < n; i = i + n + 1)
    {
        if (vec[i] == 0)
        {
            int k = i;
            while ((vec[k] == 0 ) || ( k < n))
            {
                k += n + 1;
            }
            if (k == 0) return 0;

            for (int j = 0; j < n; j++)
                vec[i + j], vec[k + j] = vec[k + j], vec[i + j];
        }

        double a = vec[i];
        for (int j = i + 1; j < n; j++)
        {
            double b = vec[j * n + i];
            vec[j * n + i] = 0;
            for (int k = i + 1; k < n; k++)
            {
                vec[j * n + k] -= (vec[i * n + k] / a) * b;
            }
        }
    }

    for (int i = 0; i < n; i++) res *= vec[i * n + i];

    return res;
}

//лизины СЛАУ начинаются



// Нахождение ранга верхне-треугольной матрицы
template <class T>
int matrixRank(Matrix<T> M)
{
    int rank = M.h(); int k = -1, i;
    bool null_row = true;
    while (null_row) {
        for (i = 0; i < M.w(); i++)
            if (M[rank - k - 2][i] != 0) null_row = false;
        k++;
    }
    return rank - k;
}

// Алгоритм прямого хода Гаусса
template <class T>
Matrix<T> gauss(Matrix<T>& a)
{
    Matrix<T> c(a);
    int i, j, k;
    for (i = 0; i < c.h(); ++i)
    {
        // находим строку с максимальным первым элементом
        int iMax = i;
        for (j = i + 1; j < c.h(); j++)
            if (abs(c[j][i]) > abs(c[iMax][i]))
                iMax = j;
        if (abs(c[iMax][i]) < eps)
            continue;
        if (i != iMax) {
            for (k = 0; k < c.w(); k++)
                swap(c[i][k], c[iMax][k]);
        }

        //  вычитаем текущую строку из всех остальных
        for (j = i + 1; j < c.h(); j++)
        {
            T q = -1 * (c[j][i] / c[i][i]);
            for (k = c.w() - 1; k >= i; k--) {
                c[j][k] += q * c[i][k];
            }
        }
    }
    return c;
}

// Алгоритм обратного хода Гаусса для определенных систем
template <class T>
Matrix<T> reverseGauss(Matrix<T>& tr_matrix)
{
    int cur_row, k, j;
    int n = tr_matrix.h();
    T reserve;
    for (cur_row = n - 1; cur_row > 0; cur_row--)
    {
        reserve = tr_matrix[cur_row][cur_row];
        for (k = cur_row; k < tr_matrix.w(); k++)
            tr_matrix[cur_row][k] /= reserve;

        for (j = 1; j <= cur_row; j++) {
            if (tr_matrix[cur_row - j][cur_row] != 0) {
                T q = (-1) * (tr_matrix[cur_row - j][cur_row] / tr_matrix[cur_row][cur_row]);
                for (k = cur_row; k < tr_matrix.w(); k++)
                    tr_matrix[cur_row - j][k] += q * tr_matrix[cur_row][k];
            }
        }
    }
    reserve = tr_matrix[0][0];
    for (k = 0; k < tr_matrix.w(); k++)
        tr_matrix[0][k] /= reserve;
    return tr_matrix;
}

template <class T>
Matrix<T> getInverseMatrix(Matrix<T>& m) {
    Matrix<T> id_m(m.identityMatrix());
    Matrix<T> exp_matrix(m.concateMatrix(id_m));
    exp_matrix = gauss(exp_matrix);
    Matrix<T> new_exp_matrix(reverseGauss(exp_matrix));
    Matrix<T> result(m.h(), m.w());
    for (int i = 0; i < m.h(); i++) {
        for (int j = 0; j < m.w(); j++)
            result[i][j] = new_exp_matrix[i][m.h() + j];
    }
    return result;
}

template <class T>
Matrix<T> pseudoInverseMatrix(Matrix<T>& coef_matrix)
{
    Matrix<T> m_t = coef_matrix;
    Matrix<T> m_t1 = +m_t;
    Matrix<T> product1 = m_t1 * coef_matrix;
    Matrix<T> product2 = getInverseMatrix(product1);
    Matrix<T> result(product2 * m_t1);
    return result;
}


template <class T>
void getSolutionRG(Matrix<T>& tr_matrix) {
    int n = tr_matrix.h(), i;
    int w = tr_matrix.w();
    for (i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << tr_matrix[i][w - 1] << "\n";
    }
}


// Алгоритм обратного хода Гаусса для неопределенных систем
template <class T>
void underReverseGauss(Matrix<T>& tr_matrix, Matrix<T>& const_values, int rank)
{
    int cur_row, i, k, cur_el, base_el_ind;
    int n = tr_matrix.h();
    int free_variables[tr_matrix.w() - rank - 1];
    int base_variables[rank];
    int free_var_number = 0;

    // Записываем индексы свободных переменных
    for (i = 0; i < rank - 1; i++) {
        base_el_ind = 0;
        while (tr_matrix[i][base_el_ind] == 0) base_el_ind++;
        base_variables[i] = base_el_ind;
        while (tr_matrix[i + 1][base_el_ind + 1] == 0) {
            base_el_ind++;
            free_variables[free_var_number] = base_el_ind;
            free_var_number++;
        }
    }
    base_el_ind = 0;
    while (tr_matrix[rank - 1][base_el_ind] == 0) base_el_ind++;
    base_variables[i] = base_el_ind;
    for (i = base_el_ind + 1; i < tr_matrix.w() - 1; i++) {
        free_variables[free_var_number] = i;
        free_var_number++;
    }

    //  Обратный ход Гаусса на миноре коэффициентов базисных неизвестных
    for (cur_row = n - 1; cur_row >= 0; cur_row--)
    {
        //    Делим все элементы текущей строки на коэффициент текущего элемента
        cur_el = 0;
        while (tr_matrix[cur_row][cur_el] == 0) cur_el++;
        T reserve = tr_matrix[cur_row][cur_el];

        for (i = cur_el; i < tr_matrix.w(); i++) {
            tr_matrix[cur_row][i] /= reserve;
        }

        //    Вычитаем из строк выше текущей, текущую, умноженную на соответсвующий множитель
        for (k = 1; k <= cur_row; k++) {
            if (tr_matrix[cur_row - k][cur_el] != 0) {
                T q = (-1) * (tr_matrix[cur_row - k][cur_el]);
                for (i = cur_el; i < tr_matrix.w(); i++) {
                    tr_matrix[cur_row - k][i] += q * tr_matrix[cur_row][i];
                }
            }
        }
    }

    // Формируем коэффициенты свободных переменных в матрице const_values
    int const_ind;
    for (i = 0; i < rank; i++) {
        int ind = base_variables[i];
        for (k = 0; k < tr_matrix.w() - rank - 1; k++) {
            const_ind = free_variables[k];
            const_values[ind][k] = (-1) * tr_matrix[i][const_ind];
        }
        const_values[ind][tr_matrix.w() - rank - 1] = tr_matrix[i][tr_matrix.w() - 1];
    }

    free_var_number = 0;
    for (auto ind : free_variables) {
        const_values[ind][free_var_number] = 1;
        free_var_number++;
    }
}

template <class T>
void getSolutionURG(Matrix<T>& const_terms) {
    int n = const_terms.h(), i, k;
    int w = const_terms.w();
    bool first_in_row = true;
    for (i = 0; i < n; i++) {
        first_in_row = true;
        cout << "x" << i + 1 << " = ";
        for (k = 0; k < w - 1; k++) {
            if (!first_in_row) {
                if (const_terms[i][k] > 0) {
                    cout << "+ ";
                }
            }
            if (const_terms[i][k] != 0) {
                if (const_terms[i][k] != 1)
                    cout << const_terms[i][k] << "*C" << k + 1 << " ";
                else
                    cout << "C" << k + 1 << " ";
                first_in_row = false;
            }

        }
        if (!first_in_row) {
            if (const_terms[i][w - 1] > 0) cout << "+ ";
        }
        if (const_terms[i][w - 1] != 0)
            cout << const_terms[i][w - 1];
        cout << "\n";
    }
    cout << "Where Ci are const values\n";
}

// Решение системы линейных уравнений
template<class T>
int sleCalculator(Matrix<T>& coef_matrix, Matrix<T>& const_terms, T null_el)
{
    //  Строим расширенную матрицу, приводим ее к верхне-треугольному виду
    Matrix<T> exp_matrix = coef_matrix.concateMatrix(const_terms);
    Matrix<T> triangular_matrix = gauss(exp_matrix);

    //  Находим ранг верхне-треугольной матрицы
    int rank = matrixRank(triangular_matrix);

    bool is_null_row = true;
    for (int j = 0; j < triangular_matrix.w() - 1; j++)
        if (triangular_matrix[rank - 1][j] != 0)
            is_null_row = false;

    //  Если система несовместна, она не имеет решений либо существует приближенное решение
    if (is_null_row && triangular_matrix[rank - 1][triangular_matrix.w() - 1] != 0) {
        int width = coef_matrix.w();
        if (rank > width) {
            //      Проверяем, если в треугольной матрице матрица А имеет ранг равный числу неизвестных
            is_null_row = true;
            for (int j = 0; j < triangular_matrix.w() - 1; j++) {
                if (triangular_matrix[width - 1][j] != 0)
                    is_null_row = false;
            }
            if (!is_null_row) {
                //        Находим псевдорешение
                Matrix<T> pseudo_matrix(pseudoInverseMatrix(coef_matrix));
                Matrix<T> answer(pseudo_matrix * const_terms);
                cout << "Inconsistent system - there can be only pseudoanswer:" << "\n";
                getSolutionRG(answer);
                return 0;
            }
        }
        cout << "Inconsistent system - there is no solution" << "\n";
        return 0;
    }

    //  Система совместна и определена - имеет единственное решение
    if (rank == coef_matrix.w()) {
        reverseGauss(triangular_matrix);
        getSolutionRG(triangular_matrix);
        return 0;
    }

    //  Система совместна и не определена - имеет бесконечное множество решений
    if (rank < coef_matrix.w()) {
        Matrix<T> const_values(coef_matrix.w(), triangular_matrix.w() - rank, null_el);
        underReverseGauss(triangular_matrix, const_values, rank);
        getSolutionURG(const_values);
        return 0;
    }
}


int slau(int n, int m, vector<double> B, vector<double> A) //n - количество строк и соотв количество элементов в B; m - столбцы; A -матрица; B - свободные коэф
{
    int v, eq, i, p;
    vector<Fraction> f;
    vector<Fraction> b1;
    Fraction null_el(0);

    v = m; eq = n;
    for (i = 0; i < v * eq; i++) {
        Fraction el(int(A[i]*drob), drob);
        f.push_back(el);
    }
    Matrix<Fraction> M(eq, v, f);

    for (i = 0; i < eq; i++) {
        Fraction el(int(B[i] * drob), drob);
        b1.push_back(el);
    }
    Matrix<Fraction> b(eq, 1, b1);

    return sleCalculator(M, b, null_el);
}


//определенный интеграл
double f(double x)
{
    return sin(x);
}

double inegral(double a, double b)//a - нижний предел; b - верхний
{
    double h = 0.01;
    double Integral;
    double n; 
    n = (b - a) / h;

    Integral = 0.0;
    for (int i = 1; i <= n; i++)
        Integral = Integral + h * f(a + h * (i - 0.5));

    return Integral;
}

int main()
{
    vector <double> a = {1, 2, 0, 1};
    vector <double> b = { 3,1 };
    
    cout << inegral(0, 1);
    
}

