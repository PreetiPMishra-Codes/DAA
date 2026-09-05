/* ============================================================
   Q3: Convolution of two vectors in O(n log n) via
       Divide-and-Conquer (Cooley-Tukey FFT)
   ============================================================
   C[k] = sum_{j=0}^{m-1} A[j] * B[k-j],  lengths m and n (n >= m)

   Idea: Zero-pad A and B (length m and n) to length
   N = next power of two >= m+n-1.
   Compute FFT(A), FFT(B) in O(N log N) via the D&C radix-2 FFT
   (splitting each polynomial into even/odd index coefficients,
   recursing on two halves of size N/2, and combining in O(N)
   using the butterfly operation) -- this recursion satisfies
   T(N) = 2T(N/2) + O(N)  =>  T(N) = O(N log N).
   Then pointwise multiply the two transforms in O(N),
   and apply the Inverse FFT (also O(N log N)) to get C.
   Total: O(N log N) = O(n log n) since N = O(m+n) = O(n).
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

typedef double complex cplx;

/* Recursive radix-2 Cooley-Tukey FFT (in place).
   invert = 0 for forward transform, 1 for inverse transform.
   len must be a power of two. */
void fft(cplx *a, int len, int invert) {
    if (len == 1) return;

    cplx even[len/2], odd[len/2];
    for (int i = 0; i < len/2; i++) {
        even[i] = a[2*i];
        odd[i]  = a[2*i + 1];
    }

    fft(even, len/2, invert);   /* T(n/2) */
    fft(odd,  len/2, invert);   /* T(n/2) */

    double angleSign = invert ? 1.0 : -1.0;
    for (int k = 0; k < len/2; k++) {
        double angle = angleSign * 2.0 * M_PI * k / len;
        cplx w = cos(angle) + I * sin(angle);
        cplx t = w * odd[k];
        a[k]         = even[k] + t;   /* O(1) butterfly combine step */
        a[k + len/2] = even[k] - t;   /* -> O(n) total combine per level */
    }
}

int nextPowerOfTwo(int x) {
    int p = 1;
    while (p < x) p <<= 1;
    return p;
}

/* Convolution using FFT: O(n log n) */
void convolve(double *A, int m, double *B, int n, double *C /* size m+n-1 */) {
    int resultLen = m + n - 1;
    int N = nextPowerOfTwo(resultLen);

    cplx *fa = calloc(N, sizeof(cplx));
    cplx *fb = calloc(N, sizeof(cplx));
    for (int i = 0; i < m; i++) fa[i] = A[i];
    for (int i = 0; i < n; i++) fb[i] = B[i];

    fft(fa, N, 0);
    fft(fb, N, 0);

    for (int i = 0; i < N; i++) fa[i] *= fb[i];   /* O(N) pointwise multiply */

    fft(fa, N, 1); /* inverse FFT: O(N log N) */

    for (int i = 0; i < resultLen; i++)
        C[i] = creal(fa[i]) / N;

    free(fa); free(fb);
}

int main() {
    int m, n;
    printf("Enter length of vector A (m): ");
    scanf("%d", &m);
    double A[m];
    printf("Enter %d elements of A: ", m);
    for (int i = 0; i < m; i++) scanf("%lf", &A[i]);

    printf("Enter length of vector B (n, n >= m): ");
    scanf("%d", &n);
    double B[n];
    printf("Enter %d elements of B: ", n);
    for (int i = 0; i < n; i++) scanf("%lf", &B[i]);

    int resultLen = m + n - 1;
    double *C = malloc(resultLen * sizeof(double));
    convolve(A, m, B, n, C);

    printf("\nConvolution C (length %d):\n", resultLen);
    for (int i = 0; i < resultLen; i++) printf("%.2f ", C[i]);
    printf("\n\n[Overall complexity: O(N log N) with N = O(m+n), i.e. O(n log n)]\n");

    free(C);
    return 0;
}
