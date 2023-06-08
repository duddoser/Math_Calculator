package com.example.mathcalculator;

import static java.lang.Math.abs;

import android.util.Log;

import java.util.ArrayList;

public class math {
    private double eps = 0.0000000001;
    private int drob = 1000000;


    public double det(int n, double[] mat) //определитель только для квадратных матриц размера n
    {
        double res = 1;
        double [] vec = new double[n*n];
        for(int i=0;i<n*n;i++) vec[i] = mat[i];

        for (int i = 0; i < n; i++)
        {
            if (vec[i*n+i] == 0)
            {
                int k = i;
                while ((vec[k*n+k] == 0 ) || ( k < n))
                {
                    k++;
                }
                if (k == n) return 0;

                for (int j = 0; j < n; j++) {
                    double t = vec[i*n+j];
                    vec[i*n+j] = vec[k*n+j];
                    vec[k*n+j] = t;
                }
            }

            double a = vec[i*n+i];
            for (int j = i + 1; j < n; j++)
            {
                double b = vec[j*n+i];
                vec[j*n+i] = 0;
                for (int k = i + 1; k < n; k++)
                {
                    vec[j*n+k] -= (vec[i*n+k] / a) * b;
                }
            }
        }

        for (int i = 0; i < n; i++) res *= vec[i*n+i];

        return res;
    }

    int matrixRank(double[][] M)
    {
        int rank = M.length; int k = -1, i;
        boolean null_row = true;
        while (null_row) {
            for (i = 0; i < M[0].length; i++)
                if (M[rank - k - 2][i] != 0) null_row = false;
            k++;
        }
        return rank - k;
    }

    double[][] gauss(double[][] a)
    {
        double[][] c = a;
        int i, j, k;
        for (i = 0; i < c.length; ++i)
        {
            // находим строку с максимальным первым элементом
            int iMax = i;
            for (j = i + 1; j < c.length; j++)
                if (abs(c[j][i]) > abs(c[iMax][i]))
                    iMax = j;
            if (abs(c[iMax][i]) < eps)
                continue;
            if (i != iMax) {
                for (k = 0; k < c[0].length; k++) {
                    double t = c[i][k];
                    c[i][k] = c[iMax][k];
                    c[iMax][k] = t;
                }
            }

            //  вычитаем текущую строку из всех остальных
            for (j = i + 1; j < c.length; j++)
            {
                double q = -1 * (c[j][i] / c[i][i]);
                for (k = c[0].length - 1; k >= i; k--) {
                    c[j][k] += q * c[i][k];
                }
            }
        }
        return c;
    }

// Алгоритм обратного хода Гаусса для определенных систем
    double[][] reverseGauss(double[][] tr_matrix)
    {
        int cur_row, k, j;
        int n = tr_matrix.length;
        double reserve;
        for (cur_row = n - 1; cur_row > 0; cur_row--)
        {
            reserve = tr_matrix[cur_row][cur_row];
            for (k = cur_row; k < tr_matrix[0].length; k++)
                tr_matrix[cur_row][k] /= reserve;

            for (j = 1; j <= cur_row; j++) {
                if (tr_matrix[cur_row - j][cur_row] != 0) {
                    double q = (-1) * (tr_matrix[cur_row - j][cur_row] / tr_matrix[cur_row][cur_row]);
                    for (k = cur_row; k < tr_matrix[0].length; k++)
                        tr_matrix[cur_row - j][k] += q * tr_matrix[cur_row][k];
                }
            }
        }
        reserve = tr_matrix[0][0];
        for (k = 0; k < tr_matrix[0].length; k++)
            tr_matrix[0][k] /= reserve;
        return tr_matrix;
    }

    double[][] identityMatrix(int height, int width) {
        double[][] result = new double[height][width];
        for(int i = 0; i < height; i++)
            result[i][i] = 1;
        return result;
    }

    double[][] concateMatrix(double[][] a, double[][] b)
    {
        if (a.length != b.length) {
            double[][] res = new double[2][2];
            return res;
        }
        double[][] result = new double[a.length][a[0].length + b[0].length];
        for (int i = 0; i < a.length; i++){
            for (int j = 0; j < a[0].length; j++)
                result[i][j] = a[i][j];
            for (int j = 0; j < b[0].length; j++)
                result[i][j + a[0].length] = b[i][j];
        }
        return result;
    }

    double[][] getInverseMatrix(double[][] m) {
        double[][] id_m = identityMatrix(m.length, m[0].length);
        double[][] exp_matrix = concateMatrix(m, id_m);
        exp_matrix = gauss(exp_matrix);
        double[][] new_exp_matrix = reverseGauss(exp_matrix);
        double[][] result = new double[m.length][m[0].length];
        for (int i = 0; i < m.length; i++) {
            for (int j = 0; j < m[0].length; j++)
                result[i][j] = new_exp_matrix[i][m.length + j];
        }
        return result;
    }

    double[][] transpose(double[][] a) {
        double[][] Result = new double[a[0].length][a.length];
        for(int i = 0; i < a.length; i++){
            for(int j = 0; j < a[0].length; j++){
                Result[j][i] = a[i][j];
            }
        }
        return Result;
    }

    double[][] mult(double[][] a, double[][] b) {
        double[][] Result = new double[a.length][b[0].length];
        double cur_element;
        for(int i = 0; i < a.length; i++){
            for(int j = 0; j < b[0].length; j++){
                cur_element = 0;
                for(int k = 0; k < a[0].length; k++)
                    cur_element += a[i][k] * a[k][j];
                Result[i][j] = cur_element;
            }
        }
        return Result;

    }

    double[][] pseudoInverseMatrix(double[][] coef_matrix)
    {
        double[][] m_t = coef_matrix;
        double[][] m_t1 = transpose(m_t);
        double[][] product1 = mult(m_t1, coef_matrix);
        double[][] product2 = getInverseMatrix(product1);
        double[][] result = mult(product2, m_t1);
        return result;
    }


    String[] getSolutionRG(double[][] tr_matrix) {
        String[] res;
        int n = tr_matrix.length, i;
        int w = tr_matrix[0].length;
        String[] R = new String[n];
        int t = 0;
        for (i = 0; i < n; i++) {
            String a = "x" + String.valueOf(i + 1) + " = " + String.valueOf(tr_matrix[i][w - 1]);
            R[i] = a;
        }
        return R;
    }


// Алгоритм обратного хода Гаусса для неопределенных систем
    void underReverseGauss(double[][] tr_matrix, double[][] const_values, int rank)
    {
        int cur_row, i, k, cur_el, base_el_ind;
        int n = tr_matrix.length;
        int[] free_variables = new int[tr_matrix[0].length - rank - 1];
        int[] base_variables = new int[rank];
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
        for (i = base_el_ind + 1; i < tr_matrix[0].length - 1; i++) {
            free_variables[free_var_number] = i;
            free_var_number++;
        }

        //  Обратный ход Гаусса на миноре коэффициентов базисных неизвестных
        for (cur_row = n - 1; cur_row >= 0; cur_row--)
        {
            //    Делим все элементы текущей строки на коэффициент текущего элемента
            cur_el = 0;
            Log.e("AAAAAAAAAAAA", "n: " + n + "  " + "cur_row: " + cur_row);
            while (tr_matrix[cur_row][cur_el] == 0) {
                Log.e("BBBBBBBBBBBB", "cur_el: " + cur_el);
                cur_el++;}
            double reserve = tr_matrix[cur_row][cur_el];

            for (i = cur_el; i < tr_matrix[0].length; i++) {
                tr_matrix[cur_row][i] /= reserve;
            }

            //    Вычитаем из строк выше текущей, текущую, умноженную на соответсвующий множитель
            for (k = 1; k <= cur_row; k++) {
                if (tr_matrix[cur_row - k][cur_el] != 0) {
                    double q = (-1) * (tr_matrix[cur_row - k][cur_el]);
                    for (i = cur_el; i < tr_matrix[0].length; i++) {
                        tr_matrix[cur_row - k][i] += q * tr_matrix[cur_row][i];
                    }
                }
            }
        }

        // Формируем коэффициенты свободных переменных в матрице const_values
        int const_ind;
        for (i = 0; i < rank; i++) {
            int ind = base_variables[i];
            for (k = 0; k < tr_matrix[0].length - rank - 1; k++) {
                const_ind = free_variables[k];
                const_values[ind][k] = (-1) * tr_matrix[i][const_ind];
            }
            const_values[ind][tr_matrix[0].length - rank - 1] = tr_matrix[i][tr_matrix[0].length - 1];
        }

        free_var_number = 0;
        for (int ind : free_variables) {
            const_values[ind][free_var_number] = 1;
            free_var_number++;
        }
    }

    void underReverseGauss(double[][] tr_matrix, double[][] const_values)
    {
        int cur_row, i, k, cur_el, base_el_ind;
        int rank = 0;
        int n = tr_matrix.length;
        int[] free_variables = new int[tr_matrix[0].length - rank - 1];
        int[] base_variables = new int[rank];
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
        for (i = base_el_ind + 1; i < tr_matrix[0].length - 1; i++) {
            free_variables[free_var_number] = i;
            free_var_number++;
        }

        //  Обратный ход Гаусса на миноре коэффициентов базисных неизвестных
        for (cur_row = n - 1; cur_row >= 0; cur_row--)
        {
            //    Делим все элементы текущей строки на коэффициент текущего элемента
            cur_el = 0;
            while (tr_matrix[cur_row][cur_el] == 0) cur_el++;
            double reserve = tr_matrix[cur_row][cur_el];

            for (i = cur_el; i < tr_matrix[0].length; i++) {
                tr_matrix[cur_row][i] /= reserve;
            }

            //    Вычитаем из строк выше текущей, текущую, умноженную на соответсвующий множитель
            for (k = 1; k <= cur_row; k++) {
                if (tr_matrix[cur_row - k][cur_el] != 0) {
                    double q = (-1) * (tr_matrix[cur_row - k][cur_el]);
                    for (i = cur_el; i < tr_matrix[0].length; i++) {
                        tr_matrix[cur_row - k][i] += q * tr_matrix[cur_row][i];
                    }
                }
            }
        }

        // Формируем коэффициенты свободных переменных в матрице const_values
        int const_ind;
        for (i = 0; i < rank; i++) {
            int ind = base_variables[i];
            for (k = 0; k < tr_matrix[0].length - rank - 1; k++) {
                const_ind = free_variables[k];
                const_values[ind][k] = (-1) * tr_matrix[i][const_ind];
            }
            const_values[ind][tr_matrix[0].length - rank - 1] = tr_matrix[i][tr_matrix[0].length - 1];
        }

        free_var_number = 0;
        for (int ind : free_variables) {
            const_values[ind][free_var_number] = 1;
            free_var_number++;
        }
    }

    String[] getSolutionURG(double[][] const_terms) {
        int n = const_terms.length, i, k;
        int w = const_terms[0].length;

        String[] R = new String[n];
        boolean first_in_row;

        for (i = 0; i < n; i++) {
            StringBuilder a = new StringBuilder("");
            first_in_row = true;
            a.append("x" + (i + 1) + " = ");
            for (k = 0; k < w - 1; k++) {
                if (!first_in_row) {
                    if (const_terms[i][k] > 0) {
                        a.append("+ ");
                    }
                }
                if (const_terms[i][k] != 0) {
                    if (const_terms[i][k] != 1) {
                        a.append(const_terms[i][k] + "*C" +
                                (k + 1) + " ");
                    }
                    else {
                        a.append("C" + (k + 1) + " ");
                    }
                    first_in_row = false;
                }

            }
            if (!first_in_row) {
                if (const_terms[i][w - 1] > 0) {
                    a.append("+ ");
                }
            }
            if (const_terms[i][w - 1] != 0)
            {
                a.append(const_terms[i][w - 1]);
            }
            R[i] = a.toString();
        }

        return R;
    }

// Решение системы линейных уравнений
    int sleCalculator(double[][] coef_matrix, double[][] const_terms, double null_el)
    {
        //  Строим расширенную матрицу, приводим ее к верхне-треугольному виду
        double[][] exp_matrix = concateMatrix(coef_matrix, const_terms);
        double[][] triangular_matrix = gauss(exp_matrix);

        //  Находим ранг верхне-треугольной матрицы
        int rank = matrixRank(triangular_matrix);

        boolean is_null_row = true;
        for (int j = 0; j < triangular_matrix[0].length - 1; j++)
            if (triangular_matrix[rank - 1][j] != 0)
                is_null_row = false;

        //  Если система несовместна, она не имеет решений либо существует приближенное решение
        if (is_null_row && triangular_matrix[rank - 1][triangular_matrix[0].length - 1] != 0) {
            int width = coef_matrix[0].length;
            if (rank > width) {
                //      Проверяем, если в треугольной матрице матрица А имеет ранг равный числу неизвестных
                is_null_row = true;
                for (int j = 0; j < triangular_matrix[0].length - 1; j++) {
                    if (triangular_matrix[width - 1][j] != 0)
                        is_null_row = false;
                }
                if (!is_null_row) {
                    //        Находим псевдорешение
                    double[][] pseudo_matrix = pseudoInverseMatrix(coef_matrix);
                    double[][] answer = mult(pseudo_matrix, const_terms);
                    Log.e("E", "Inconsistent system - there can be only pseudoanswer");
                    getSolutionRG(answer);
                    return 0;
                }
            }
            Log.e("E", "Inconsistent system - there is no solution");
            return 0;
        }

        //  Система совместна и определена - имеет единственное решение
        if (rank == coef_matrix[0].length) {
            reverseGauss(triangular_matrix);
            getSolutionRG(triangular_matrix);
            return 0;
        }

        //  Система совместна и не определена - имеет бесконечное множество решений
        if (rank < coef_matrix[0].length) {
            double[][] const_values = new double[coef_matrix[0].length][triangular_matrix[0].length - rank];
            for (int i = 0; i < coef_matrix[0].length; i++) {
                for (int j = 0; j < triangular_matrix[0].length - rank; j++) {
                    const_values[i][j] = null_el;
                }
            }

            underReverseGauss(triangular_matrix, const_values, rank);
            getSolutionURG(const_values);
            return 0;
        }
        return rank;
    }

    String[] sleCalculator_vec_char(double[][] coef_matrix, double[][] const_terms, double null_el)
    {
        String[] res = new String[0];
        //  Строим расширенную матрицу, приводим ее к верхне-треугольному виду
        double[][] exp_matrix = concateMatrix(coef_matrix, const_terms);
        double[][] triangular_matrix = gauss(exp_matrix);

        //  Находим ранг верхне-треугольной матрицы
        int rank = matrixRank(triangular_matrix);

        boolean is_null_row = true;
        for (int j = 0; j < triangular_matrix[0].length - 1; j++)
            if (triangular_matrix[rank - 1][j] != 0)
                is_null_row = false;

        //  Если система несовместна, она не имеет решений либо существует приближенное решение
        if (is_null_row && triangular_matrix[rank - 1][triangular_matrix[0].length - 1] != 0) {
            int width = coef_matrix[0].length;
            if (rank > width) {
                //      Проверяем, если в треугольной матрице матрица А имеет ранг равный числу неизвестных
                is_null_row = true;
                for (int j = 0; j < triangular_matrix[0].length - 1; j++) {
                    if (triangular_matrix[width - 1][j] != 0)
                        is_null_row = false;
                }
                if (!is_null_row) {
                    //        Находим псевдорешение
                    double[][] pseudo_matrix = pseudoInverseMatrix(coef_matrix);
                    double[][] answer = mult(pseudo_matrix, const_terms);
                    Log.e("E", "Inconsistent system - there can be only pseudoanswer");
                    return getSolutionRG(answer);

                }
            }
            Log.e("E", "Inconsistent system - there is no solution");
            return res;
        }

        //  Система совместна и определена - имеет единственное решение
        if (rank == coef_matrix[0].length) {
            reverseGauss(triangular_matrix);
            return getSolutionRG(triangular_matrix);

        }

        //  Система совместна и не определена - имеет бесконечное множество решений
        if (rank < coef_matrix[0].length) {
            double[][] const_values = new double[coef_matrix[0].length][triangular_matrix[0].length
                    - rank];
            for (int i = 0; i < coef_matrix[0].length; i++) {
                for (int j = 0; j < triangular_matrix[0].length - rank; j++) {
                    const_values[i][j] = null_el;
                }
            }

            underReverseGauss(triangular_matrix, const_values, rank);
            return getSolutionURG(const_values);
        }
        return res;
    }

    String[] slau(int n, int m, double[] B, double[] A)
    {
        int v, eq, i, p;
        ArrayList<Double> f = new ArrayList<>();
        ArrayList<Double> b1 = new ArrayList<>();
        double null_el = 0;

        v = m; eq = n;
        for (i = 0; i < eq; i++) {
            for(int j=0;j<v;j++) {
                double el = A[i*n+j];
                f.add(el);
            }
        }

        double[][] M = new double[eq][v]; //(eq, v, f);
        for (i = 0; i < eq; i++) {
            for (int j = 0; j < v; j++)
                M[i][j] = f.get(i * v + j);
        }

        for (i = 0; i < eq; i++) {
            b1.add(B[i]);
        }

        double[][] b = new double[eq][1]; //(eq, 1, b1);
        for (i = 0; i < eq; i++) {
            b[i][0] = b1.get(i);
        }

        return sleCalculator_vec_char(M, b, null_el);
    }

}
