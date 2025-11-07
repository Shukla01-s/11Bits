#include <stdio.h>
#include <math.h>

int main() {
    int nx = 100, ny = 100;     // grid points
    double phi[100][100] = {0};
    double f[100][100] = {0};   // source term
    double tol = 1e-4;        // tolerance
    double error;
    double omega = 1.7;       // relaxation factor
    double h = 1.0 / (nx - 1);  // ✅ grid spacing defined properly
    int iter,max_iter=10000,i,j;

    // Boundary Conditions
    for (i = 0; i < nx; i++) {
        phi[i][nx-1] = 100.0;   // Right boundary = 100V
        phi[i][0] = 0.0;       // Left boundary = 0V
        phi[0][i] = 0.0;       // Bottom boundary = 0V
        phi[nx-1][i] = 0.0;     // Top boundary = 0V
    }

    printf("Iteration\tError\n");
    printf("----------------------\n");

    // SOR Iteration Loop
    for (iter = 1; iter <= max_iter; iter++) {
        error = 0.0;  // Reset error for new iteration

        for (i = 1; i < nx-1; i++) {
            for (j = 1; j < ny-1; j++) {
                double old = phi[i][j];

                // SOR formula (Laplace equation, f(x,y)=0)
                phi[i][j] = (1 - omega) * phi[i][j]
                          + (omega / 4.0) * (phi[i+1][j] + phi[i-1][j]
                                           + phi[i][j+1] + phi[i][j-1]-h*h*f[i][j]);

                // Accumulate total change
                error += fabs(phi[i][j] - old);
            }
        }

        // Print error after every 100 iterations (optional)
        if (iter % 100 == 0 || iter == 1)
            printf("%5d\t\t%.6f\n", iter, error);

        // Stop if error is smaller than tolerance
        if (error < tol) {
            printf("%5d\t\t%.6f  <-- Converged ✅\n", iter, error);
            break;
        }
    }

    printf("\nConverged after %d iterations.\n\n", iter);
    printf("Final potential distribution (phi):\n");

   // Save phi values to file for visualization
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            fprintf(fp, "%.4f ", phi[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    printf("Phi values saved to output.txt\n");
    return 0;
}
