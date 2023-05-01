#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "roots.h"

typedef struct Complex {
    float real;
    float imag;
} Complex;

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
    FILE *inputFile = fopen("Data.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    FILE *outputFile = fopen("Result.txt", "w");
    if (outputFile == NULL) {
        printf("Error creating output file.\n");
        fclose(inputFile);
        return 1;
    }

    float a1, a2, y0, y1;
    while (fscanf(inputFile, "%f %f %f %f", &a1, &a2, &y0, &y1) == 4) {
        Complex root1, root2;
        find_roots(a1, a2, &root1, &root2);

        if (root1.imag == 0 && root2.imag == 0) {
            if (root1.real == root2.real) { // Repeating real roots
                float C1, C2;
                C1 = y0;
                C2 = y1 - root1.real * y0;
                fprintf(outputFile, "2 %.2f %.2f\n", C1, C2);
            } else { // Distinct real roots
                float C1, C2;
                C1 = compute_c1(a1, a2, y0, y1, root1.real, root2.real);
                C2 = compute_c2(a1, a2, y0, y1, root1.real, root2.real);
                fprintf(outputFile, "1 %.2f %.2f\n", C1, C2);
            }
        } else { // Complex conjugate roots
            float alpha = root1.real;
            float beta = root1.imag;
            float C = sqrt(y0 * y0 + (y1 - alpha * y0) * (y1 - alpha * y0)) / beta;
            float theta = compute_theta(alpha, beta, y0, y1) * 180 / M_PI;
            fprintf(outputFile, "3 %.2f %.2f\n", C, theta);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Results saved to Result.txt\n");
    return 0;
}
