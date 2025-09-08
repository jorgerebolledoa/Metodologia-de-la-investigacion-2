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
// ----------- MÉTODO 6: DP optimizado con arreglo de tamaño k+1 ----------------
unsigned long long binomial_dp_opt(unsigned int n, unsigned int k) {
    if (k > n) return 0;

    // Asignación dinámica con malloc
    unsigned long long *C = (unsigned long long *)malloc((k + 1) * sizeof(unsigned long long));
    if (C == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return 0;
    }

    // Inicializamos el arreglo a 0
    for (unsigned int i = 0; i <= k; i++) {
        C[i] = 0;
    }
    C[0] = 1; // C(n,0) = 1

    for (unsigned int i = 1; i <= n; i++) {
        // Recorremos de derecha a izquierda para no sobrescribir valores necesarios
        for (unsigned int j = (i < k ? i : k); j > 0; j--) {
            C[j] = C[j] + C[j - 1];
        }
    }

    unsigned long long result = C[k];
    free(C); // liberamos la memoria
    return result;
}
// ----------- MÉTODO 7: combinatoria factorial recursivo ----------------
unsigned long long factorial_rec(unsigned long long n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial_rec(n - 1);
}

unsigned long long binomial_factorial_rec(unsigned long n, unsigned long k) {
    if (k > n) return 0;
    return factorial_rec(n) / (factorial_rec(k) * factorial_rec(n - k));
}

// ----------- MÉTODO 8: descomposición en primos ----------------
#include <math.h>

// Genera todos los primos hasta n usando la criba de Eratóstenes
void generar_primos(int n, int **primos, int *num_primos) {
    int *es_primo = malloc((n+1) * sizeof(int));
    for(int i=0;i<=n;i++) es_primo[i]=1;
    es_primo[0]=es_primo[1]=0;

    for(int i=2;i*i<=n;i++){
        if(es_primo[i]){
            for(int j=i*i;j<=n;j+=i) es_primo[j]=0;
        }
    }

    int count=0;
    for(int i=2;i<=n;i++) if(es_primo[i]) count++;

    *primos = malloc(count * sizeof(int));
    int idx=0;
    for(int i=2;i<=n;i++) if(es_primo[i]) (*primos)[idx++] = i;

    *num_primos = count;
    free(es_primo);
}

// Calcula el exponente del primo p en n!
unsigned long long exponente_primo_factorial(unsigned int n, int p) {
    unsigned long long exp = 0;
    unsigned long long div = p;
    while(div <= n) {
        exp += n / div;
        div *= p;
    }
    return exp;
}

// Calcula C(n,k) usando descomposición en primos
unsigned long long binomial_primos(unsigned int n, unsigned int k) {
    if(k > n) return 0;
    if(k == 0 || k == n) return 1;

    int *primos, num_primos;
    generar_primos(n, &primos, &num_primos);

    unsigned long long resultado = 1;
    for(int i=0;i<num_primos;i++){
        int p = primos[i];
        unsigned long long exp = exponente_primo_factorial(n,p)
                               - exponente_primo_factorial(k,p)
                               - exponente_primo_factorial(n-k,p);
        for(unsigned long long j=0;j<exp;j++){
            resultado *= p;
        }
    }

    free(primos);
    return resultado;
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
        case 6:
            resultado = binomial_dp_opt(n, k);
            break;
        case 7:
            resultado = binomial_factorial_rec(n, k);
            break;
        case 8:
            resultado = binomial_primos(n, k);
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
