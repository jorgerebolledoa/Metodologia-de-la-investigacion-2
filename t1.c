#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------- MÉTODO 1: factoriales ----------------
unsigned long long factorial(unsigned int n) {
    unsigned long long res = 1;
    for (unsigned int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

unsigned long long binomial_factorial(unsigned int n, unsigned int k) {
    if (k > n) return 0;
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// ----------- MÉTODO 2: recursión de Pascal ----------------
unsigned long long binomial_pascal(unsigned int n, unsigned int k) {
    if (k == 0 || k == n) return 1;
    return binomial_pascal(n - 1, k - 1) + binomial_pascal(n - 1, k);
}

// ----------- MÉTODO 3: multiplicativo ----------------
unsigned long long binomial_multiplicativo(unsigned int n, unsigned int k) {
    if (k > n) return 0;
    if (k > n - k) k = n - k; // simetría
    unsigned long long res = 1;
    for (unsigned int i = 1; i <= k; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// ----------- MÉTODO 4: DP con memoria estática ----------------
#define MAXN 1000  // límite arbitrario
unsigned long long binomial_estatico(unsigned int n, unsigned int k) {
    static unsigned long long C[MAXN+1][MAXN+1]; // tabla estática
    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int j = 0; j <= i && j <= k; j++) {
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    return C[n][k];
}

// ----------- MÉTODO 5: DP con memoria dinámica ----------------
unsigned long long binomial_dinamico(unsigned int n, unsigned int k) {
    unsigned long long **C = malloc((n+1) * sizeof(unsigned long long*));
    for (unsigned int i = 0; i <= n; i++) {
        C[i] = malloc((k+1) * sizeof(unsigned long long));
    }

    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int j = 0; j <= k && j <= i; j++) {
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    unsigned long long result = C[n][k];

    for (unsigned int i = 0; i <= n; i++) {
        free(C[i]);
    }
    free(C);

    return result;
}

// ----------- MAIN ----------------
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s -o n k\n", argv[0]);
        return 1;
    }

    int metodo = atoi(argv[1]);
    unsigned int n = atoi(argv[2]);
    unsigned int k = atoi(argv[3]);

    clock_t inicio, fin;
    double tiempo;
    unsigned long long resultado = 0;

    inicio = clock();

    switch (metodo) {
        case 1:
            resultado = binomial_factorial(n, k);
            break;
        case 2:
            resultado = binomial_pascal(n, k);
            break;
        case 3:
            resultado = binomial_multiplicativo(n, k);
            break;
        case 4:
            resultado = binomial_estatico(n, k);
            break;
        case 5:
            resultado = binomial_dinamico(n, k);
            break;
        default:
            printf("Método no válido. Use 1, 2, 3, 4 o 5.\n");
            return 1;
    }

    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("C(%u, %u) = %llu\n", n, k, resultado);
    printf("Tiempo de ejecución: %.6f segundos\n", tiempo);

    return 0;
}
