#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "roots.h"

float compute_c1(float a1, float a2, float y0, float y1, float lambda1, float lambda2) {
    return (y1 - (lambda2 * y0)) / (lambda1 - lambda2);
}

float compute_c2(float a1, float a2, float y0, float y1, float lambda1, float lambda2) {
    return ((lambda1 * y0) - y1) / (lambda1 - lambda2);
}

float compute_theta(float alpha, float beta, float y0, float y1) {
    return atan2(y1 - alpha * y0, y0);
}

int main() {
    float a1, a2, y0, y1;
    printf("Enter the coefficients (a1, a2) of the linear system: ");
    scanf("%f %f", &a1, &a2);
    printf("Enter the two initial conditions (y0, y1): ");
    scanf("%f %f", &y0, &y1);

    double complex root1, root2;
    find_roots(a1, a2, &root1, &root2);

    if (cimag(root1) == 0 && cimag(root2) == 0) {
        if (creal(root1) == creal(root2)) { // Repeating real roots
            float C1, C2;
            C1 = y0;
            C2 = y1 - creal(root1) * y0;
            printf("y(t) = (%.2f + %.2ft)e^(%.2ft)\n", C1, C2, creal(root1));
        } else { // Distinct real roots
            float C1, C2;
            C1 = compute_c1(a1, a2, y0, y1, creal(root1), creal(root2));
            C2 = compute_c2(a1, a2, y0, y1, creal(root1), creal(root2));
            printf("y(t) = %.2fe^(%.2ft) + %.2fe^(%.2ft)\n", C1, creal(root1), C2, creal(root2));
        }
    } else { // Complex conjugate roots
        float alpha = creal(root1);
        float beta = cimag(root1);
        float C = sqrt(y0 * y0 + (y1 - alpha * y0) * (y1 - alpha * y0)) / beta;
        float theta = compute_theta(alpha, beta, y0, y1) * 180 / M_PI;
        printf("y(t) = %.2f e^(%0.2f t)cos(%.2f t + %.2f)\n", C, alpha, beta, theta);
    }

    return 0;
}
