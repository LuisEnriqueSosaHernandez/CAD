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
		sprintf(mensaje,"Hola fui enviado del proceso %d",rango);
		printf("Proceso Esclavo %d de %d\n",rango,procesos);
		destino=0;
		MPI_Send(mensaje,strlen(mensaje)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);
	}else{
		printf("Proceso Maestro 0,Procesos = %d\n",procesos);
		for(fuente=1;fuente<procesos;fuente++){
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			printf("%s\n",mensaje);
		}
	}
	MPI_Finalize();
	return 0;
}
