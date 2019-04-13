//Importación de librerias
#include <string.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc,char * argv[]){
	//Declaración de variables
	int rango,procesos,fuente,destino,etiqueta=0;
	char mensaje[100];
	MPI_Status estado;
	
	//Llamado a funciones MPI necesarias para el control del ambiente paralelo
	MPI_Init(&argc,&argv);//Se inicializa el ambiente paralelo MPI para trabajar mediante el paso de mensajes
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);//Se asigna a la variable rank, el puntero que indica el número de proceso
	//que se esta ejecutando
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);// Se asigna a la variable size, el número de procesadores disponibles para usar
	
	//Área de lógica
	if(rango!=0){//Uso de la variable rango mediante un if, para asignar una acción a todo proceso distinto de 0
		printf("Proceso Esclavo %d de %d\n",rango,procesos);//Impresión de los procesos esclavos
		MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepción del mensaje entrante al proceso en turno
		printf("%s recibido de %d\n",mensaje,fuente);//Impresión del mensaje entrante, concatenado con el proceso emisor
	}else{
		strcpy(mensaje,"Hello world\0");//Se copia la cadena al arreglo
		printf("Proceso Maestro 0,Procesos = %d\n",procesos);//Impresión del proceso maestro concatenado con el número
		//total de procesos
		for(fuente=1;fuente<procesos;fuente++){//Ciclo for para la emisión de mensajes al proceso en turno
			destino=fuente;//Variable que indica a que proceso será enviado el mensaje
			MPI_Send(mensaje,strlen(mensaje)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);//Envío del arreglo al proceso en turno
			}
		}
		
	MPI_Finalize();//Se finaliza el ambiente paralelo
	return 0;
}

