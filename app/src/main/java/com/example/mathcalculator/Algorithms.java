package com.example.mathcalculator;

public class Algorithms {

    // Dimension of input square matrix
    static final int N = 4;
    private static final int MAXN = 100;

    // Function to get determinant of matrix
    static int determinantOfMatrix(int mat[][], int n)
    {
        int num1, num2, det = 1, index,
                total = 1; // Initialize result

        // temporary array for storing row
        int[] temp = new int[n + 1];

        // loop for traversing the diagonal elements
        for (int i = 0; i < n; i++) {
            index = i; // initialize the index

            // finding the index which has non zero value
            while (mat[index][i] == 0 && index < n) {
                index++;
            }
            if (index == n) // if there is non zero element
            {
                // the determinant of matrix as zero
                continue;
            }
            if (index != i) {
                // loop for swapping the diagonal element row
                // and index row
                for (int j = 0; j < n; j++) {
                    swap(mat, index, j, i, j);
                }
                // determinant sign changes when we shift
                // rows go through determinant properties
                det = (int)(det * Math.pow(-1, index - i));
            }

            // storing the values of diagonal row elements
            for (int j = 0; j < n; j++) {
                temp[j] = mat[i][j];
            }

            // traversing every row below the diagonal
            // element
            for (int j = i + 1; j < n; j++) {
                num1 = temp[i]; // value of diagonal element
                num2 = mat[j][i]; // value of next row element

                // traversing every column of row
                // and multiplying to every row
                for (int k = 0; k < n; k++) {
                    // multiplying to make the diagonal
                    // element and next row element equal
                    mat[j][k] = (num1 * mat[j][k])
                            - (num2 * temp[k]);
                }
                total = total * num1; // Det(kA)=kDet(A);
            }
        }

        // multiplying the diagonal elements to get
        // determinant
        for (int i = 0; i < n; i++) {
            det = det * mat[i][i];
        }
        return (det / total); // Det(kA)/k=Det(A);
    }

    static int[][] swap(int[][] arr, int i1, int j1, int i2,
                        int j2)
    {
        int temp = arr[i1][j1];
        arr[i1][j1] = arr[i2][j2];
        arr[i2][j2] = temp;
        return arr;
    }

    public static void partialPivot(double[][] A, int n) {
        for (int i = 0; i < n; i++) {
            int pivotRow = i;
            for (int j = i+1; j < n; j++) {
                if (Math.abs(A[j][i]) > Math.abs(A[pivotRow][i])) {
                    pivotRow = j;
                }
            }
            if (pivotRow != i) {
                for (int j = i; j <= n; j++) {
                    double temp = A[i][j];
                    A[i][j] = A[pivotRow][j];
                    A[pivotRow][j] = temp;
                }
            }
            for (int j = i+1; j < n; j++) {
                double factor = A[j][i] / A[i][i];
                for (int k = i; k <= n; k++) {
                    A[j][k] -= factor * A[i][k];
                }
            }
        }
    }

    public static void backSubstitute(double[][] A, int n, double[] x) {
        for (int i = n-1; i >= 0; i--) {
            double sum = 0;
            for (int j = i+1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            x[i] = (A[i][n] - sum) / A[i][i];
        }
    }

    // Driver code
    public static void main(String[] args)
    {
        int mat[][] = { { 1, 0, 2, -1 },
                { 3, 0, 0, 5 },
                { 2, 1, 4, -3 },
                { 1, 0, 5, 0 } };

        // Function call
        System.out.printf(
                "Determinant of the matrix is : %d",
                determinantOfMatrix(mat, N));

        int n = 3;
        double[][] A = {{3.0, 2.0,-4.0, 3.0},
                {2.0, 3.0, 3.0, 15.0},
                {5.0, -3, 1.0, 14.0}
        };
        double[] x = new double[MAXN];

        partialPivot(A, n);
        backSubstitute(A, n, x);

        System.out.println("Solution for the system:");
        for (int i = 0; i < n; i++) {
            System.out.println(x[i]);
        }
    }
}
