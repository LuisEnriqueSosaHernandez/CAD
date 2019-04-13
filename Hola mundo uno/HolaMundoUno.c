//Importación de librerias
#include <stdio.h>
#include <mpi.h>

int main(int argc,char** argv){
	//Declaración de variables
	int rank,size;
	
	//Llamado a funciones MPI necesarias para el control del ambiente paralelo
	MPI_Init(&argc,&argv);//Se inicializa el ambiente paralelo MPI para trabajar mediante el paso de mensajes
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);//Se asigna a la variable rank, el puntero que indica el número de proceso
	//que se esta ejecutando
	MPI_Comm_size(MPI_COMM_WORLD,&size);// Se asigna a la variable size, el número de procesadores disponibles para usar
	
	//Área de lógica
	printf("Hello from proccessor %d of %d\n",rank,size);//Se imprime un hola mundo desde cada proceso, concatenado 
	//con el número de procesadores total 
	
	MPI_Finalize();//Se finaliza el ambiente paralelo
	return 0;
}
