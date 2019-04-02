#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define max 100
int main(int argc,char * argv[]){
	int rango,procesos,fuente,destino,etiqueta=0;
	char mensaje[max];
	char cad0[]="mensaje 0",
	cad1[]="mensaje 1",
	cad2[]="mensaje 2",
	cad3[]="mensaje 3",
	cad4[]="mensaje 4";
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
			printf("Anillo Estatico\n");
			destino=1;
			fuente=4;
			MPI_Send(cad0,strlen(cad0)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			MPI_Recv(mensaje,max,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("Yo soy %d recibiendo  %s de P%d\n",rango,mensaje,estado.MPI_SOURCE);
			break;
			case 1:
			destino=2;
			fuente=0;
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("Yo soy %d recibiendo  %s de P%d\n",rango,mensaje,estado.MPI_SOURCE);
			MPI_Send(cad1,strlen(cad1)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 2:
			destino=3;
			fuente=1;
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("Yo soy %d recibiendo  %s de P%d\n",rango,mensaje,estado.MPI_SOURCE);
			MPI_Send(cad2,strlen(cad2)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 3:
			strcpy(mensaje,"El mensaje\0");
			destino=4;
			fuente=2;
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("Yo soy %d recibiendo  %s de P%d\n",rango,mensaje,estado.MPI_SOURCE);
			MPI_Send(cad3,strlen(cad3)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 4:
			strcpy(mensaje,"El mensaje\0");
			destino=0;
			fuente=3;
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("Yo soy %d recibiendo  %s de P%d\n",rango,mensaje,estado.MPI_SOURCE);
			MPI_Send(cad4,strlen(cad4)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			break;
		}
	}
	MPI_Finalize();
	return 0;
}


