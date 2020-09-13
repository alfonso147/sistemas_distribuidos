/*
 ============================================================================
 Name        : MPI_EPSILON.cpp
 Author      : Irvin
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h>
#include "mpi.h"   
#include <cstdlib> 
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[])
{
    int n, 
		rank, 
		size; 
    double EPSILON = 2.718281828459045235360;
    double startval, endval;
    double accum;
    double factorial;
    double sum = 0.0;

    double epsilon;


    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

   
	if (rank == 0) {
		cout<<"introduce la precision del calculo (n > 0): ";
		cin>>n;
	}

	startval = 4*n*rank/size+1;
	endval = 4*n*(rank+1)/size;

	factorial = 1;

	for(int i = startval; i <= endval; i = i+1){
		
		factorial=(factorial*i);
		sum+= (1/factorial);
	}


	MPI_Bcast(&n, // Puntero al dato que vamos a enviar
			  1,  // Numero de datos a los que apunta el puntero
			  MPI_INT, // Tipo del dato a enviar
			  0, // Identificacion del proceso que envia el dato
			  MPI_COMM_WORLD);

	if (n <= 0){
		MPI_Finalize();
		exit(0);

	}else {

		for(int j = 1; j < size; j = j+1) {

				sum = sum + accum;
		}
		
		printf("rank %d s = %f \n",rank,sum);



		MPI_Reduce(&sum, 	
					&epsilon,  	
					1,	    	// Numero de datos que vamos a reducir
					MPI_DOUBLE,  // Tipo de dato que vamos a reducir
					MPI_SUM,  	// Operacion que aplicaremos
					0, 			// proceso que va a recibir el dato reducido
					MPI_COMM_WORLD);

		
		if (rank == 0)
			cout<< "El valor aproximado de E es: " <<setprecision(16)<<epsilon<< ", con un error de "  << fabs(EPSILON - epsilon)<< endl;
	}


    MPI_Finalize();
    return 0;
}
