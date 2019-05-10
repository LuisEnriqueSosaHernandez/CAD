#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define tam 16

int fibonacci(int n);

int main(int argc,char * argv[]){
	clock_t t_inicial,t_final;
	int rango,procesos,etiqueta=0;
	int i,j,llenado,contProcesos,divisionTrabajo;
	long long int matriz[tam][tam];
	long long int matrizResultante[tam][tam];
	long long int matrizTemporal[tam][tam];
	long long int vector[tam];
	
	double seg;
	
    MPI_Status estado;	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);
	
	 if(procesos!=3) {
        printf("El numero de procesadores no es el requerido\n");
        exit(1);
    } else {
		divisionTrabajo=tam/(procesos-1);
	switch(rango){
		case 0:
		 printf("Matriz a calcular\n");         
            for(i=0; i<tam; i++) {
                for(j=0; j<tam; j++) {
					//llenado=rand()%35;
					llenado=15;
                    matriz[i][j]=llenado;
                    printf("%lld ",matriz[i][j]);
                }
                printf("\n");
            }
            i=0;
            contProcesos=1;
		while(i<tam){
			for(j=0;j<divisionTrabajo;j++){
		MPI_Send(&matriz[i],tam,MPI_LONG_LONG_INT,contProcesos,etiqueta,MPI_COMM_WORLD);
		i++;
		//printf("Enviado desde %d\n",rango);
	}
	contProcesos++;
	}
	
	//Recibir desornado
	
	for(i=0;i<tam;i++){		
		MPI_Recv(&matrizResultante[i],100,MPI_LONG_LONG_INT,MPI_ANY_SOURCE,etiqueta,MPI_COMM_WORLD,&estado);
		//printf("Recibido en %d desde %d\n",rango,estado.MPI_SOURCE);
	}
	
	//Recibibir en orden
	
	 /*i=0;
            contProcesos=1;
		while(i<tam){
			for(j=0;j<divisionTrabajo;j++){
		MPI_Recv(&matrizResultante[i],100,MPI_LONG_LONG_INT,contProcesos,etiqueta,MPI_COMM_WORLD,&estado);
		i++;	
	}
	contProcesos++;
	}*/
	
	 printf("\nMatriz fibonacci\n");
            for(i=0; i<tam; i++) {
                for(j=0; j<tam; j++) {
                    printf("%lld ",matrizResultante[i][j]);
                }
					printf("\n");
            }
	break;
		default:
		t_inicial=clock();
		for(i=0;i<divisionTrabajo;i++){
		MPI_Recv(vector,tam,MPI_LONG_LONG_INT,0,etiqueta,MPI_COMM_WORLD,&estado);
		//printf("Recibido en procesador %d desde %d\n",rango,estado.MPI_SOURCE);
		for(j=0;j<tam;j++){
			matrizTemporal[i][j]=fibonacci(vector[j]);			
		}
	}
		for(i=0;i<divisionTrabajo;i++){
		MPI_Send(&matrizTemporal[i],tam,MPI_LONG_LONG_INT,0,etiqueta,MPI_COMM_WORLD);
		//printf("Enviado desde procesador %d\n",rango);
	}
	t_final=clock();
	seg=(double)(t_final-t_inicial)/CLOCKS_PER_SEC;
	printf("%.16g milisegundos procesador %d\n",seg*1000.00,rango);
	break;
		}
	}
	MPI_Finalize();
	return 0;
}
int fibonacci(int n){
	 if (n>1){
       return fibonacci(n-1) + fibonacci(n-2); 
    }
    else if (n==1||n==2) { 
        return 1;
    }
    else if (n==0){ 
        return 0;
    }
    else{ 
        return n; 
    }
}	
