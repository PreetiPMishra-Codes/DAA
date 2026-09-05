/* ============================================================
   Q2: 2D Square Matrix Operations and their Worst-Case Complexities
   ============================================================
   Input representation: n x n matrix stored as a statically
   allocated 2D VLA (row-major), read from stdin.

   Operation                         Worst-case complexity
   -------------------------------   ----------------------
   (i)   Matrix addition             O(n^2)
   (ii)  Matrix multiplication       O(n^3)   (naive triple loop)
   (iii) Zero matrix check           O(n^2)
   (iv)  Symmetric matrix check      O(n^2)
   (v)   Determinant                 O(n^3)   (Gaussian elimination;
                                      naive cofactor expansion is O(n!))
   (vi)  Transpose in place          O(n^2)
   (vii) Eigenvalue / eigenvector    O(k*n^2) per run of Power
                                      Iteration (k = #iterations to
                                      converge) - gives the DOMINANT
                                      eigenpair only. In general, no
                                      closed-form root exists for n>4
                                      (Abel-Ruffini), so ALL eigenvalues
                                      are found only via O(n^3) per
                                      iteration numerical methods (e.g.
                                      the QR algorithm).
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* (i) O(n^2) */
void matAdd(int n, double A[n][n], double B[n][n], double C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

/* (ii) O(n^3) naive */
void matMul(int n, double A[n][n], double B[n][n], double C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

/* (iii) O(n^2) */
int isZeroMatrix(int n, double A[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0) return 0;
    return 1;
}

/* (iv) O(n^2) */
int isSymmetric(int n, double A[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (A[i][j] != A[j][i]) return 0;
    return 1;
}

/* (v) O(n^3) via Gaussian elimination (partial pivoting) */
double determinant(int n, double A[n][n]) {
    double M[n][n];
    memcpy(M, A, n * n * sizeof(double));
    double det = 1.0;

    for (int col = 0; col < n; col++) {
        int pivotRow = col;
        for (int r = col + 1; r < n; r++)
            if (fabs(M[r][col]) > fabs(M[pivotRow][col])) pivotRow = r;

        if (fabs(M[pivotRow][col]) < 1e-12) return 0.0; /* singular */

        if (pivotRow != col) {
            for (int k = 0; k < n; k++) {
                double t = M[col][k]; M[col][k] = M[pivotRow][k]; M[pivotRow][k] = t;
            }
            det = -det;
        }

        det *= M[col][col];
        for (int r = col + 1; r < n; r++) {
            double factor = M[r][col] / M[col][col];
            for (int k = col; k < n; k++)
                M[r][k] -= factor * M[col][k];
        }
    }
    return det;
}

/* (vi) O(n^2) - swap upper/lower triangle in place */
void transposeInPlace(int n, double A[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            double t = A[i][j]; A[i][j] = A[j][i]; A[j][i] = t;
        }
}

/* (vii) Power Iteration -> dominant eigenvalue & eigenvector.
   Cost: O(n^2) per iteration, O(k*n^2) total for k iterations. */
void dominantEigen(int n, double A[n][n], double *eigenvalue, double v[]) {
    for (int i = 0; i < n; i++) v[i] = 1.0; /* initial guess */
    double eigVal = 0;

    for (int iter = 0; iter < 1000; iter++) {
        double w[n];
        for (int i = 0; i < n; i++) {
            w[i] = 0;
            for (int j = 0; j < n; j++)
                w[i] += A[i][j] * v[j];
        }
        double norm = 0;
        for (int i = 0; i < n; i++) norm += w[i] * w[i];
        norm = sqrt(norm);
        if (norm < 1e-12) break;
        for (int i = 0; i < n; i++) w[i] /= norm;

        /* Rayleigh quotient estimate of eigenvalue */
        double num = 0;
        for (int i = 0; i < n; i++) {
            double Av_i = 0;
            for (int j = 0; j < n; j++) Av_i += A[i][j] * w[j];
            num += w[i] * Av_i;
        }
        eigVal = num;
        memcpy(v, w, n * sizeof(double));
    }
    *eigenvalue = eigVal;
}

void printMatrix(int n, double A[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%8.3f ", A[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    double A[n][n], B[n][n], C[n][n];
    printf("Enter matrix A (%d x %d): ", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%lf", &A[i][j]);

    printf("Enter matrix B (%d x %d): ", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%lf", &B[i][j]);

    printf("\n(i) A + B =   [O(n^2)]\n");
    matAdd(n, A, B, C);
    printMatrix(n, C);

    printf("\n(ii) A * B =   [O(n^3)]\n");
    matMul(n, A, B, C);
    printMatrix(n, C);

    printf("\n(iii) Is A zero matrix? %s   [O(n^2)]\n", isZeroMatrix(n, A) ? "Yes" : "No");

    printf("(iv) Is A symmetric? %s   [O(n^2)]\n", isSymmetric(n, A) ? "Yes" : "No");

    printf("(v) det(A) = %.4f   [O(n^3)]\n", determinant(n, A));

    double T[n][n];
    memcpy(T, A, n * n * sizeof(double));
    transposeInPlace(n, T);
    printf("(vi) Transpose of A (in place):   [O(n^2)]\n");
    printMatrix(n, T);

    double eigVal, v[n];
    dominantEigen(n, A, &eigVal, v);
    printf("(vii) Dominant eigenvalue of A ~= %.4f   [O(k*n^2)]\n", eigVal);
    printf("      Corresponding eigenvector: ");
    for (int i = 0; i < n; i++) printf("%.4f ", v[i]);
    printf("\n");

    return 0;
}
