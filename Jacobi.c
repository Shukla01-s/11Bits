#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#define NX 20
#define NY 20
#define MAX_ITER 10000
#define TOL 1e-6

int main() {
    double phi[NX+1][NY+1] = {0.0};
    double phi_new[NX+1][NY+1] = {0.0};
    double f[NX+1][NY+1] = {0.0};
    double h = 1.0 / NX;
    double error;
    int i, j, iter;

    // Boundary conditions
    for (i = 0; i <= NX; i++) {
        phi[i][NY] = sin(M_PI * i * h); // top
    }

    for (iter = 1; iter <= MAX_ITER; iter++) {
        error = 0.0;

        for (i = 1; i < NX; i++) {
            for (j = 1; j < NY; j++) {
                phi_new[i][j] = 0.25 * (phi[i+1][j] + phi[i-1][j] +
                                        phi[i][j+1] + phi[i][j-1] -
                                        h * h * f[i][j]);
                error += fabs(phi_new[i][j] - phi[i][j]);
            }
        }

        for (i = 1; i < NX; i++)
            for (j = 1; j < NY; j++)
                phi[i][j] = phi_new[i][j];

        if (error < TOL) break;
    }

    printf("Jacobi converged in %d iterations with error = %e\n", iter, error);

    // Save output
   FILE *fp = fopen("jacobi.txt", "w");
    for (i = 0; i <= NX; i++) {
        for (j = 0; j <= NY; j++) {
            fprintf(fp, "%lf %lf %lf\n", i*h, j*h, phi[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}
