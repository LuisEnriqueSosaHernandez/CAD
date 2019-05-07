//Importación de librerias
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define tam 2//Variable estática que define el tamaño del arreglo

int fibonacci(int n);//DEclaración de funciones

int main(int argc,char * argv[]) {
	//Declaración de variables
    int rango,procesos,fuente,destino,etiqueta=0;
    int matriz1[tam][tam];
    int matrizResultante[tam][tam];
    int vector1[tam];
    int vector2[tam];
    int i,j,llenado;
    MPI_Status estado;
    
    //Llamado a funciones MPI necesarias para el control del ambiente paralelo
    MPI_Init(&argc,&argv);//Se inicializa el ambiente paralelo MPI para trabajar mediante el paso de mensajes
    MPI_Comm_rank(MPI_COMM_WORLD,&rango);//Se asigna a la variable rank, el puntero que indica el número de proceso
	//que se esta ejecutando
    MPI_Comm_size(MPI_COMM_WORLD,&procesos);// Se asigna a la variable size, el número de procesadores disponibles para usar
    
    //Área de lógica
    if(procesos!=3) {//Validación del número de procesadores a utilizar mediante un if
        printf("El numero de procesadores no es el requerido\n");
        exit(1);
    } else {
        switch(rango) {//Sentencia case usada para identificar el procesador en turno mediante la variable rango
			//y asignarle acciones diferentes a los procesos
        case 0:
        //Llenado e impresión de la matriz 1
            printf("Matriz 1\n");
            llenado=10;
            for(i=0; i<tam; i++) {
                for(j=0; j<tam; j++) {
                    matriz1[i][j]=llenado;
                    llenado++;
                    printf("%d ",matriz1[i][j]);
                }
                printf("\n");
            }
            //Envío de las matrices 
            for(i=0; i<tam; i++) {
                destino=i+1;//Variable que alberga el número del proceso destino
                MPI_Send(&matriz1[i],2,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);//Se envia la dirección de las filas de la matriz 1
            }
            //Recepción de la matriz resultante
            for(i=0; i<tam; i++) {
                fuente=i+1;//Variable que alberga el número del proceso emisor del mensaje
                MPI_Recv(&matrizResultante[i],2,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepción del vector resultante
                //posterior a la operación(suma)realizada en cada proceso
            }
            //Impresión de la matriz resultante
            printf("\nMatriz resultante\n");
            for(i=0; i<tam; i++) {
                for(j=0; j<tam; j++) {
                    printf("%d ",matrizResultante[i][j]);
                }
					printf("\n");
            }
            break;
        default:
            destino=0;//Variable que alberga el número del proceso destino
            fuente=0;//Variable que alberga el número del proceso emisor del mensaje
            MPI_Recv(vector1,2,MPI_INT,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepcion del vector en la posición 0 de la matriz 1
            //Suma de las posiciones del vector recibido
            for(i=0; i<tam; i++) {
				if(vector1[i]<1){
					vector2[i]=fibonacci(vector1[i]);//Suma y  asignación de la suma en un vector resultante
				}else{
					vector2[i]=fibonacci(vector1[i]-1);//Suma y  asignación de la suma en un vector resultante
				}
            }
            MPI_Send(vector2,2,MPI_INT,destino,etiqueta,MPI_COMM_WORLD);//Envío del vector resultante al proceso 0
            break;
        }
    }
    MPI_Finalize();//Se finaliza el ambiente paralelo
    return 0;
}
//Implementación de la función
int fibonacci(int n){
	 if (n>1){
       return fibonacci(n-1) + fibonacci(n-2);  //función recursiva
    }
    else if (n==1||n==2) {  // caso base
        return 1;
    }
    else if (n==0){  // caso base
        return 0;
    }
    else{ //numero negativo
        return n; 
    }
}	


