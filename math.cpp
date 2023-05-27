#include <bits/stdc++.h>
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

vector<string> cv_ur(double a, double b, double c) //ax^2+bx+c=0
{
    double x1, x2;
    int n;
    vector<string> res;
    double D = (b * b - 4 * a * c);
    if (D == 0)
    {
        x1 = (-b / (2 * a));
        n = 1;
        res.push_back(to_string(x1));
    }

    if (D > 0)
    {
        double Ds = sqrt(D);
        x1 = (-b + Ds) / (2 * a);
        x2 = (-b - Ds) / (2 * a);
        n = 2;
        res.push_back(to_string(x1));
        res.push_back(to_string(x2));
    }

    //if (D < 0)
    return res;
}

double det(int n, vector<vector<double>> mat) //определитель только для квадратных матриц размера n
{
    double res = 1;
    vector<vector<double>> vec = mat;

    for (int i = 0; i < n; i++)
    {
        if (vec[i][i] == 0)
        {
            int k = i;
            while ((vec[k][k] == 0 ) || ( k < n))
            {
                k++;
            }
            if (k == n) return 0;

            for (int j = 0; j < n; j++)
                vec[i][j], vec[k][j] = vec[k][j], vec[i][j];
        }

        double a = vec[i][i];
        for (int j = i + 1; j < n; j++)
        {
            double b = vec[j][i];
            vec[j][i] = 0;
            for (int k = i + 1; k < n; k++)
            {
                vec[j][k] -= (vec[i][k] / a) * b;
            }
        }
    }

    for (int i = 0; i < n; i++) res *= vec[i][i];

    return res;
}

//лизины СЛАУ начинаются

int64_t gcd(int64_t a, int64_t b) {
    return b != 0 ? gcd(b, a % b) : a;
}

class Fraction
{
protected:
    int64_t num;
    int64_t denom;
public:
    Fraction() {
        num = 0;
        denom = 1;
    }

    Fraction(int64_t n) {
        num = n;
        denom = 1;
    }

    Fraction(int64_t n, int64_t d) {
        num = n;
        if (d < 0) num *= -1;
        if (d != 0) denom = abs(d);
    }

    Fraction(const Fraction& f) {
        num = f.num;
        denom = f.denom;
    }

    int n() const {
        return num;
    }

    void set_n(int64_t n) {
        num = n;
    }

    int d() const {
        return denom;
    }

    void set_d(int64_t d) {
        denom = d;
    }

    Fraction& operator=(Fraction const& f) {
        num = f.num;
        denom = f.denom;
        return *this;
    }


    //  унарный -
    Fraction operator-() const {
        Fraction result(0, 1);
        result.num = -1 * num;
        result.denom = denom;
        return result;
    }

    Fraction operator*(int64_t m) const {
        Fraction result(0, 1);
        result.num = num * m;
        result.denom = denom;
        int64_t com_factor = gcd(abs(m), denom);
        result.num /= com_factor;
        result.denom /= com_factor;
        return result;
    }

    Fraction operator*(const Fraction& f) const {
        Fraction result(0, 1);
        result.num = num * f.num;
        result.denom = denom * f.denom;
        int64_t com_factor = gcd(abs(result.num), result.denom);
        result.num /= com_factor;
        result.denom /= com_factor;
        return result;
    }

    Fraction operator/(const Fraction& f) const {
        Fraction result(0, 1);
        if (f.num < 0) result.num = f.denom * (-1);
        else result.num = f.denom;
        result.denom = abs(f.num);
        return *this * result;
    }


    Fraction operator+(const Fraction& f) const {
        Fraction result(0, 1);
        result.num = num * f.denom + f.num * denom;
        result.denom = denom * f.denom;
        int64_t com_factor = gcd(abs(result.num), result.denom);
        result.num /= com_factor;
        result.denom /= com_factor;
        return result;
    }

    Fraction& operator+=(Fraction const& f) {
        Fraction result(*this + f);
        num = result.num;
        denom = result.denom;
        return *this;
    }

    Fraction& operator/=(Fraction const& f) {
        Fraction result;
        result = *this / f;
        num = result.num;
        denom = result.denom;
        return *this;
    }

    Fraction operator-(const Fraction& f) const {
        Fraction result(0, 1);
        result.num = -1 * f.num;
        return *this + f;
    }


    bool operator==(const Fraction& f) const {
        return num == f.num && denom == f.denom;
    }

    bool operator!=(const Fraction& f) const {
        return !(*this == f);
    }

    bool operator==(const int& i) const {
        return num == denom * i;
    }

    bool operator>(const Fraction& f) const {
        return num * f.denom > denom * f.num;
    }

    bool operator<(const Fraction& f) const {
        return !(*this > f || *this == f);
    }

    bool operator<(const double& d) const {
        return num < d* denom;
    }

    friend Fraction operator*(int64_t m, const Fraction& f);
    friend ostream& operator<<(ostream& s, Fraction& f);

};


Fraction operator*(int64_t m, const Fraction& f) {
    return f * m;
}

ostream& operator<<(ostream& s, Fraction& f) {
    if (f.num == 0)
        s << 0;
    else {
        if (f.denom == 1)
            s << f.num;
        else
            s << f.num << "/" << f.denom;
    }
}

Fraction abs(Fraction& f1) {
    Fraction result;
    result.set_n(abs(f1.n()));
    result.set_d(f1.d());
    return result;
}


using namespace std;
template<class T> class Matrix {
protected:
    T** ptr;
    int height;
    int width;
public:
    Matrix(int Height = 2, int Width = 2) {
        //конструктор
        height = Height;
        width = Width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++)
            ptr[i] = new T[width];
    }

    Matrix(const Matrix& M) {
        //конструктор копий
        height = M.height;
        width = M.width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }

    }

    Matrix(int H, int W, vector<T> array)
    {
        height = H;
        width = W;
        ptr = new T * [height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = array[i * width + j];
        }
    }

    Matrix(int H, int W, T elem)
    {
        height = H;
        width = W;
        ptr = new T * [height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = elem;
        }
    }


    Matrix(ifstream& ifs) {
        //конструктор для чтения матриц из файла
        ifs >> height;
        ifs >> width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++)
                ifs >> ptr[i][j];
        }
    }

    ~Matrix() {
        //деструктор
        if (ptr != NULL) {
            for (int i = 0; i < height; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = NULL;
        }
    }

    int h() {
        return height;
    }

    int w() {
        return width;
    }

    Matrix identityMatrix()
    {
        Matrix result(height, width);
        for (int i = 0; i < height; i++)
            result[i][i] = 1;
        return result;
    }

    Matrix concateMatrix(Matrix& b)
    {
        if (height != b.h())
            return Matrix();
        Matrix result(height, width + b.w());
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                result[i][j] = ptr[i][j];
            for (int j = 0; j < b.w(); j++)
                result[i][j + width] = b[i][j];
        }
        return result;
    }

    Matrix& operator=(Matrix const& M) {
        if (height == M.height && width == M.width) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++)
                    ptr[i][j] = M.ptr[i][j];
            }
        }
        else {
            throw WrongDimensions("Unequal size of matrices in operator= ", height, width, M.height, M.width);
        }
        return *this;
    }

    T* operator[](int index) {
        if (index < 0) {
            throw NegativeIndex("Negative index in opeartor[] ", index, -1);
        }
        if (index >= height) {
            throw TooWideIndex("Too wide index in operator[] ", index, -1);
        }
        else return ptr[index];
    }

    T& operator()(int index1, int index2) {
        if (index1 < 0 || index2 < 0) {
            throw NegativeIndex("Negative index in operator() ", index1, -1);
        }
        if (index1 >= height || index2 >= height) {
            throw TooWideIndex("Too wide index in operator() ", index1, -1);
        }
        else return ptr[index1][index2];
    }

    Matrix operator+() {
        // унарный плюс - транспонирование
        Matrix<T> Result(width, height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                Result.ptr[j][i] = ptr[i][j];
            }
        }
        return Result;
    }

    Matrix operator+(Matrix M) {
        if (width != M.width || height != M.height) {
            throw WrongDimensions("Unequal size of matrices: ", height, width, M.height, M.width);
        }
        else {
            Matrix<T> Result(height, width);
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    Result.ptr[i][j] = ptr[i][j] + M.ptr[i][j];
                }
            }
            return Result;
        }
    }

    Matrix operator*(Matrix M) {
        if (width != M.height) {
            throw WrongDimensions("Unequal size of matrices: ", height, width, M.height, M.width);
        }
        else {
            Matrix<T> Result(height, M.width);
            T cur_element;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < M.width; j++) {
                    cur_element = 0;
                    for (int k = 0; k < width; k++)
                        cur_element += ptr[i][k] * M.ptr[k][j];
                    Result.ptr[i][j] = cur_element;
                }
            }
            return Result;
        }
    }

    template<class T1> friend ostream& operator<<(ostream& s, Matrix<T1> M);
    template<class T1> friend istream& operator>>(istream& s, Matrix<T1>& M);

};


template<class T> ostream& operator<<(ostream& s, Matrix<T> M) {
    if (typeid(s) == typeid(ofstream)) {
        s << M.height << " " << M.width << " ";
        s << "\n";
    }
    for (int i = 0; i < M.height; i++) {
        for (int j = 0; j < M.width; j++) {
            s << M.ptr[i][j] << " ";
        }
        s << "\n";
    }

    return s;
}

template<class T> istream& operator>>(istream& s, Matrix<T>& M) {
    if (typeid(s) == typeid(ifstream)) {
        int h, w;
        s >> h >> w;
        if (w != M.width || h != M.height) {
            // При чтении из файла и несовпадении размеров матриц, очищаем выделенную памать
            // и выделяем ее по новой
            for (int i = 0; i < M.height; i++)
                delete[] M.ptr[i];
            delete[] M.ptr;
            M.ptr = new T * [M.height];
            for (int i = 0; i < M.height; i++)
                M.ptr[i] = new T[M.width];
        }
    }
    for (int i = 0; i < M.height; i++) {
        for (int j = 0; j < M.width; j++) {
            s >> M.ptr[i][j];
        }
    }
    return s;
}



class Exception : public exception {
protected:
    //сообщение об ошибке
    char* str;
public:
    Exception(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy_s(str, strlen(s) + 1, s);
    }
    Exception(char* s) {
        str = new char[strlen(s) + 1];
        strcpy_s(str, strlen(s) + 1, s);
    }
    Exception() {
        str = NULL;
    }
    Exception(const Exception& e) {
        str = new char[strlen(e.str) + 1];
        strcpy_s(str, strlen(e.str) + 1, e.str);
    }
    ~Exception() {
        delete[] str;
    }

    virtual void print() {
        cout << "Exception: " << str << "; " << what();
    }
};

class IndexOutOfBounds : public Exception {
protected:
    int row_index; int col_index;
public:
    //конструктор
    IndexOutOfBounds(char* s, int RowIndex, int ColIndex) : Exception(s) {
        row_index = RowIndex; col_index = ColIndex;
    }
    IndexOutOfBounds(const char* s, int RowIndex, int ColIndex) : Exception(s) {
        row_index = RowIndex; col_index = ColIndex;
    }

    IndexOutOfBounds(const IndexOutOfBounds& e) {
        str = new char[strlen(e.str) + 1];
        strcpy_s(str, strlen(e.str) + 1, e.str);
        row_index = e.row_index; col_index = e.col_index;
    }

    virtual void print() {
        cout << "IndexOutOfBounds: " << str << "; " << what();
    }
};

class TooWideIndex : public IndexOutOfBounds {
public:
    //конструкторы
    TooWideIndex(char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex) {}
    TooWideIndex(const char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex) {}
    TooWideIndex(const TooWideIndex& e) : IndexOutOfBounds(e) {}

    virtual void print() {
        cout << "TooWideIndex: " << str << row_index << " " << col_index << "; " << what();
    }

};

class NegativeIndex : public IndexOutOfBounds {
public:
    //конструкторы
    NegativeIndex(char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex) {}
    NegativeIndex(const char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex) {}
    NegativeIndex(const NegativeIndex& e) : IndexOutOfBounds(e) {}

    virtual void print() {
        cout << "NegativeIndex: " << str << row_index << " " << col_index << "; " << what();
    }

};

class WrongDimensions : public Exception {
protected:
    int rows1; int cols1; int rows2; int cols2;

public:
    //конструктор
    WrongDimensions(char* s, int Rows1, int Cols1, int Rows2, int Cols2) : Exception(s) {
        rows1 = Rows1; cols1 = Cols1; rows2 = Rows2; cols2 = Cols2;
    }

    WrongDimensions(const char* s, int Rows1, int Cols1, int Rows2, int Cols2) : Exception(s) {
        rows1 = Rows1; cols1 = Cols1; rows2 = Rows2; cols2 = Cols2;
    }

    WrongDimensions(const WrongDimensions& e) {
        str = new char[strlen(e.str) + 1];
        strcpy_s(str, strlen(e.str) + 1, e.str);
        rows1 = e.rows1; cols1 = e.cols1; rows2 = e.rows2; cols2 = e.cols2;
    }

    virtual void print() {
        cout << "WrongDimensions: " << str << "; " << what();
    }
};

class WrongSize : public WrongDimensions {
public:
    //конструкторы
    WrongSize(char* s, int Rows, int Cols) : WrongDimensions(s, Rows, Cols, 1, 1) {}
    WrongSize(const char* s, int Rows, int Cols) : WrongDimensions(s, Rows, Cols, 1, 1) {}
    WrongSize(const WrongSize& e) : WrongDimensions(e) {}

    virtual void print() {
        cout << "WrongSize: " << str << "; " << what();
    }

};

// Добавим исключение, выпадающее в методах, которые написаны для матриц,
// сотстоящих из чисел
class NotANumber : public Exception {
protected:
    //  Название типа значений, которые лежат в многомерном массиве
    const char* TypeName;
public:
    //конструктор
    NotANumber(char* s, const char* type) : Exception(s) {
        TypeName = type;
    }
    NotANumber(const char* s, const char* type) : Exception(s) {
        TypeName = type;
    }

    NotANumber(const NotANumber& e) {
        str = new char[strlen(e.str) + 1];
        strcpy_s(str, strlen(e.str) + 1, e.str);
        TypeName = e.TypeName;
    }

    virtual void print() {
        cout << "NotANumber: " << str << "; " << what();
    }
};

string to_string(Fraction f)
{
    string a="";
    if (f.d() == 1)
        a = to_string(f.n());
    else
        a = to_string(f.n())+"/"+to_string(f.d());
    return a;
}

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
vector<string> getSolutionRG(Matrix<T>& tr_matrix) {
    vector<string> res;
    int n = tr_matrix.h(), i;
    int w = tr_matrix.w();
    for (i = 0; i < n; i++) {
        string a = "";
        a = "x" + to_string(i + 1) + " = " + to_string(tr_matrix[i][w - 1]);
        res.push_back(a);
    }
    return res;
}


// Алгоритм обратного хода Гаусса для неопределенных систем
template <class T>
void underReverseGauss(Matrix<T>& tr_matrix, Matrix<T>& const_values, int rank = 0)
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
vector<string> getSolutionURG(Matrix<T>& const_terms) {
    vector<string> res;
    int n = const_terms.h(), i, k;
    int w = const_terms.w();
    bool first_in_row = true;
    for (i = 0; i < n; i++) {
        string a = "";
        first_in_row = true;
        a = "x" + to_string(i + 1) + " = ";
        for (k = 0; k < w - 1; k++) {
            if (!first_in_row) {
                if (const_terms[i][k] > 0) {
                    a += "+ ";
                }
            }
            if (const_terms[i][k] != 0) {
                if (const_terms[i][k] != 1)
                    a = a + to_string(const_terms[i][k]) + "*C" + to_string(k + 1) + " ";
                else
                    a = a + "C" + to_string(k + 1) + " ";
                first_in_row = false;
            }

        }
        if (!first_in_row) {
            if (const_terms[i][w - 1] > 0) a += "+ ";
        }
        if (const_terms[i][w - 1] != 0)
            a += to_string(const_terms[i][w - 1]);
        res.push_back(a);

    }
    return res;
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

template<class T>
vector<string> sleCalculator_vec(Matrix<T>& coef_matrix, Matrix<T>& const_terms, T null_el)
{
    vector<string> res;
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
                res = getSolutionRG(answer);
                return res;
            }
        }
        cout << "Inconsistent system - there is no solution" << "\n";
        return res;
    }

    //  Система совместна и определена - имеет единственное решение
    if (rank == coef_matrix.w()) {
        reverseGauss(triangular_matrix);
        res = getSolutionRG(triangular_matrix);
        return res;
    }

    //  Система совместна и не определена - имеет бесконечное множество решений
    if (rank < coef_matrix.w()) {
        Matrix<T> const_values(coef_matrix.w(), triangular_matrix.w() - rank, null_el);
        underReverseGauss(triangular_matrix, const_values, rank);
        res = getSolutionURG(const_values);
        return res;
    }
    return res;
}


vector<string> slau(int n, int m, vector<double> B, vector<vector<double>> A) //n - количество строк и соотв количество элементов в B; m - столбцы; A -матрица; B - свободные коэф
{
    int v, eq, i, p;
    vector<Fraction> f;
    vector<Fraction> b1;
    Fraction null_el(0);

    v = m; eq = n;
    for (i = 0; i < eq; i++) {
        for(int j=0;j<v;j++) {
            Fraction el(int(A[i][j] * drob), drob);
            f.push_back(el);
        }
    }
    Matrix<Fraction> M(eq, v, f);

    for (i = 0; i < eq; i++) {
        Fraction el(int(B[i] * drob), drob);
        b1.push_back(el);
    }
    Matrix<Fraction> b(eq, 1, b1);

    return sleCalculator_vec(M, b, null_el);
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

double proizvodnaya(double x) // точка, в которой вычисляем производную
{
    double h, fl, fr, fc;

    h = 0.1; // шаг, с которым вычисляем производную

    // приближенно вычисляем первую производную различными способами
    fl = (f(x) - f(x - h)) / h; // левая
    fr = (f(x + h) - f(x)) / h; // правая
    fc = (f(x + h) - f(x - h)) / (2 * h); // центральная

    return fc;
}

int main()
{
    vector <vector<double>> a = {{1, 2}, {0, 1}};
    vector <double> b = { 3,1 };
    vector<string> res = slau(2,2,b,a);
    for(int i=0;i<res.size();i++)
        cout << res[i] <<endl;
}

