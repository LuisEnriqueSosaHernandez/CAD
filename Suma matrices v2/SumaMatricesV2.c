#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define tam 5
int main(int argc,char * argv[]){
	int rango,procesos,fuente,destino,etiqueta=0;
	int matriz1[tam][tam];
	int matriz2[tam][tam];
	int matrizResultante[tam][tam];
	int arreglo1[tam];
	int arreglo2[tam];
	int arreglo3[tam];
	int i,j,llenado;
	MPI_Status estado;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);
		if(procesos!=6){
			printf("El numero de procesadores no es el requerido\n");
			exit(1);
		}else{
		switch(rango){
			case 0:
			printf("Matriz 1\n");
			llenado=1;
			for(i=0;i<tam;i++){
				for(j=0;j<tam;j++){
					matriz1[i][j]=llenado;
					llenado++;	
					printf("%d ",matriz1[i][j]);
				}
				printf("\n");
			}
			llenado=1;
			printf("\nMatriz 2\n");
			for(i=0;i<tam;i++){
				for(j=0;j<tam;j++){
					matriz2[i][j]=llenado;
					llenado++;	
					printf("%d ",matriz2[i][j]);
				}
				printf("\n");
			}
			printf("\nMatriz resultante\n");
			for(i=0;i<tam;i++){
				destino=i+1;
				fuente=i+1;
				for(j=0;j<tam;j++){
					MPI_Send(&matriz1[i][j],1,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
					MPI_Send(&matriz2[i][j],1,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
				}
				MPI_Recv(&matrizResultante[i],5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			}
			for(i=0;i<tam;i++){
				for(j=0;j<tam;j++){
					printf("%d ",matrizResultante[i][j]);
				}
				printf("\n");
			}
			break;
			case 1:
			for(i=0;i<tam;i++){
			destino=0;
			fuente=0;
			MPI_Recv(&arreglo1[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			MPI_Recv(&arreglo2[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			arreglo3[i]=arreglo1[i]+arreglo2[i];
			}
			MPI_Send(&arreglo3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 2:
			for(i=0;i<tam;i++){
			destino=0;
			fuente=0;
			MPI_Recv(&arreglo1[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			MPI_Recv(&arreglo2[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			arreglo3[i]=arreglo1[i]+arreglo2[i];
			}
			MPI_Send(&arreglo3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 3:
			for(i=0;i<tam;i++){
			destino=0;
			fuente=0;
			MPI_Recv(&arreglo1[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			MPI_Recv(&arreglo2[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			arreglo3[i]=arreglo1[i]+arreglo2[i];
			}
			MPI_Send(&arreglo3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 4:
			for(i=0;i<tam;i++){
			destino=0;
			fuente=0;
			MPI_Recv(&arreglo1[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			MPI_Recv(&arreglo2[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			arreglo3[i]=arreglo1[i]+arreglo2[i];
			}
			MPI_Send(&arreglo3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
			break;
			case 5:
			for(i=0;i<tam;i++){
			destino=0;
			fuente=0;
			MPI_Recv(&arreglo1[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			MPI_Recv(&arreglo2[i],1,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
			arreglo3[i]=arreglo1[i]+arreglo2[i];
			}
			MPI_Send(&arreglo3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
			break;
		}
	}
	MPI_Finalize();
	return 0;
}


