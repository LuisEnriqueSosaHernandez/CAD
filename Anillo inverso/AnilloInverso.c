#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define max 100
int main(int argc,char * argv[]){
	int rango,procesos,fuente,destino,etiqueta=0;
	char mensaje[max];
	char cad[max];
	MPI_Status estado;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);
		if(procesos!=5){
			printf("El numero de procesadores no es el requerido\n");
			exit(1);
		}else{
		switch(rango){
			case 0:
			destino=4;
			fuente=1;
			MPI_Recv(mensaje,max,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 1:
			destino=0;
			fuente=2;
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 2:
			destino=1;
			fuente=3;
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 3:
			destino=2;
			fuente=4;
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 4:
			printf("Anillo Estatico\n");
			destino=3;
			fuente=0;
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);
			break;
		}
	}
	MPI_Finalize();
	return 0;
}


