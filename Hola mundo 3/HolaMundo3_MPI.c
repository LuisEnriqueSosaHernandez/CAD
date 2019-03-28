#include <string.h>
#include <stdio.h>
#include <mpi.h>
int main(int argc,char * argv[]){
	int rango,procesos,fuente,destino,etiqueta=0;
	char mensaje[100];
	MPI_Status estado;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);
	if(rango!=0){
		printf("Proceso Esclavo %d de %d\n",rango,procesos);
		MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
		printf("%s\n",mensaje);
	}else{
		strcpy(mensaje,"Hello world\0");
		printf("Proceso Maestro 0,Procesos = %d\n",procesos);
		for(fuente=1;fuente<procesos;fuente++){
			destino=fuente;
			MPI_Send(mensaje,strlen(mensaje)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
			}
		}
	MPI_Finalize();
	return 0;
}

