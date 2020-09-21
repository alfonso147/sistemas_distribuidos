#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "omp.h"

int main(void) {



    int n=4;
    double factorial[n];
    factorial[1] = 1;
    double ValEpsilon = 0;
    double ValorEpsilon =0;
    double EPSILON = 2.718281828459045235360;
    double ErrorEpsilon;


    #pragma omp parallel
    {
        int ithread = omp_get_thread_num();
        int  nthreads = omp_get_num_threads();

        double prod = 1;

        #pragma omp for schedule(static,8) nowait
        for (int i=1; i<=n; i++) {
            prod *= i;

            factorial[i] = 1/prod;

            ValEpsilon += 1/prod;
            //
        }


    }

    ValorEpsilon = ValEpsilon +1;
    ErrorEpsilon = EPSILON-ValorEpsilon;

    

    printf("Epsilon es: ");
    printf("%.10f", ValorEpsilon);
  printf(putchar('\n');
