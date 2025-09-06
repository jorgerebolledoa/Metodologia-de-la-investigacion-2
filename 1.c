/*****************************************************
 *
 * Factorial: Calculates a factorial number
 *
 * Programmer: nosotro :D
 *
 * Santiago de Chile, 30/08/2025
 *
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h> 

/*
 *
 */

// Declaraciones de funciones
unsigned long long factorialr(int n);
unsigned long long factoriali(unsigned long long n);
void FF1(int n, int k);
void FF2(unsigned long long  n, unsigned long long  k);
void Usage(char *mess);

/*
 *
 */

//Forma recursiva de primera formula
void FF1(int i, int j) {
   int resultado, n, k, m = 0;
   n = factorialr(i);
   k = factorialr(j);
   m = factorialr(i - j);
   resultado= n / (k * m);
}

//Forma recursiva de primera formula
void FF2(unsigned long long i, unsigned long long j) {

   unsigned long long resultado, n, k, m = 0;
   n = factoriali(i);
   k = factoriali(j);
   m = factoriali(i - j);
   if (k == 0 || m == 0) {
      printf("Error: división por cero en FF1/FF2\n");
      exit(1);
   }
   resultado= n / (k * m);
}

//Factorial recursivo
unsigned long long factorialr(int n) {
   if (n == 0)
      return(1);
   else
      return(n * factorialr(n-1));
}
//Factorial iterativo
unsigned long long factoriali(unsigned long long n) {
   int i;
   unsigned long long f = 1;
   for (i = 1; i <= n; i++)
      f = f * i;
   return(f);
}

void Usage(char *mess) {

   printf("\nUsage: %s -mode n k\n",mess);
   printf("\n mode in {FF1 (First Formula mode 1), SF1 (Second Formula mode 2) , etc}\n");
}

/*
 *
 */

void main(int argc, char **argv) {

    unsigned long long n, k;
    float E_cpu;
    long E_wall;
    time_t  ts, te;
    clock_t csc, cec;


    if (argc == 4) {
      n = atoi(argv[2]);
      k = atoi(argv[3]);
      if (strcmp("-FF1",argv[1]) == 0) {
         csc = clock();
         ts = time(NULL);
         FF1(n,k);
         cec = clock();
         te = time(NULL);
         E_wall = (long)(te - ts);
         E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;
         printf("%llu - Elapsed CPU Time %f Wall Time %ld\n",k,E_cpu,E_wall);
      }
      if (strcmp("-FF2",argv[1]) == 0) {
         csc = clock();
         ts = time(NULL);
         FF2(n,k);
         cec = clock();
         te = time(NULL);
         E_wall = (long)(te - ts);
         E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;
         printf("%llu - Elapsed CPU Time %f Wall Time %ld\n",k,E_cpu,E_wall);
      }
      if (strcmp("-SF2",argv[1]) == 0) {
         csc = clock();
         ts = time(NULL);
         //Funcion a calcular tiempo
         cec = clock();
         te = time(NULL);
         E_wall = (long)(te - ts);
         E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;
//      printf("%d - Elapsed CPU Time %f Wall Time %ld\n",k,E_cpu,E_wall);
      }
   }
   else
      Usage(argv[0]);
}