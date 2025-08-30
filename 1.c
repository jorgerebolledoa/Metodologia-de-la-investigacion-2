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

/*
 *
 */

void Usage(char *mess) {

   printf("\nUsage: %s mode n k\n",mess);
   printf("\n mode in {FF1 (First Formula mode 1), SF1 (Second Formula mode 2) , etc}\n");
}

/*
 *
 */

void main(int argc, char **argv) {

   int n, k;
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
         //Aqui iria lo importante de la función
         cec = clock();
         te = time(NULL);
         E_wall = (long)(te - ts);
         E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;
//      printf("%d - Elapsed CPU Time %f Wall Time %ld\n",k,E_cpu,E_wall);
      }
      if (strcmp("-SF1",argv[1]) == 0) {
         csc = clock();
         ts = time(NULL);
         //Funcion a calcular tiempo
         cec = clock();
         te = time(NULL);
         E_wall = (long)(te - ts);
         E_cpu = (float)(cec - csc) / CLOCKS_PER_SEC;
//      printf("%d - Elapsed CPU Time %f Wall Time %ld\n",k,E_cpu,E_wall);
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