#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define tam 5
int main(int argc,char * argv[]) {
    int rango,procesos,fuente,destino,etiqueta=0;
    int matriz1[tam][tam];
    int matriz2[tam][tam];
    int matrizResultante[tam][tam];
    int vector1[tam];
    int vector2[tam];
    int vector3[tam];
    int i,j,llenado;
    MPI_Status estado;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rango);
    MPI_Comm_size(MPI_COMM_WORLD,&procesos);
    if(procesos!=6) {
        printf("El numero de procesadores no es el requerido\n");
        exit(1);
    } else {
        switch(rango) {
        case 0:
            printf("Matriz 1\n");
            llenado=1;
            for(i=0; i<tam; i++) {
                for(j=0; j<tam; j++) {
                    matriz1[i][j]=llenado;
                    llenado++;
                    printf("%d ",matriz1[i][j]);
                }
                printf("\n");
            }
            llenado=1;
            printf("\nMatriz 2\n");
            for(i=0; i<tam; i++) {
                for(j=0; j<tam; j++) {
                    matriz2[i][j]=llenado;
                    llenado++;
                    printf("%d ",matriz2[i][j]);
                }
                printf("\n");
            }
            printf("\nMatriz resultante\n");
            for(i=0; i<tam; i++) {
                destino=i+1;
                //fuente=i+1;
                MPI_Send(&matriz1[i],5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
                MPI_Send(&matriz2[i],5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
                //MPI_Recv(&matrizResultante[i],5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            }
            for(i=0; i<tam; i++) {
                fuente=i+1;
                MPI_Recv(&matrizResultante[i],5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            }
            for(i=0; i<tam; i++) {
                for(j=0; j<tam; j++) {
                    printf("%d ",matrizResultante[i][j]);
                }
                printf("\n");
            }
            break;
        case 1:
            destino=0;
            fuente=0;
            MPI_Recv(vector1,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            MPI_Recv(vector2,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            for(i=0; i<tam; i++) {
                vector3[i]=vector1[i]+vector2[i];
            }
            MPI_Send(vector3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
            break;
        case 2:
            destino=0;
            fuente=0;
            MPI_Recv(vector1,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            MPI_Recv(vector2,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            for(i=0; i<tam; i++) {
                vector3[i]=vector1[i]+vector2[i];
            }
            MPI_Send(vector3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
            break;
        case 3:
            destino=0;
            fuente=0;
            MPI_Recv(vector1,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            MPI_Recv(vector2,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            for(i=0; i<tam; i++) {
                vector3[i]=vector1[i]+vector2[i];
            }
            MPI_Send(vector3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
            break;
        case 4:
            destino=0;
            fuente=0;
            MPI_Recv(vector1,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            MPI_Recv(vector2,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            for(i=0; i<tam; i++) {
                vector3[i]=vector1[i]+vector2[i];
            }
            MPI_Send(vector3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
            break;
        case 5:
            destino=0;
            fuente=0;
            MPI_Recv(vector1,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            MPI_Recv(vector2,5,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);
            for(i=0; i<tam; i++) {
                vector3[i]=vector1[i]+vector2[i];
            }
            MPI_Send(vector3,5,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);
            break;
        }
    }
    MPI_Finalize();
    return 0;
}


