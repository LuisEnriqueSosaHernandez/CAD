//Importación de librerias
#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define max 100//Variable estática que define el tamaño del arreglo

int main(int argc,char * argv[]){
	//Declaración de variables
	int rango,procesos,fuente,destino,etiqueta=0;
	char mensaje[max];
	char cad[max];
	MPI_Status estado;
	
	//Llamado a funciones MPI necesarias para el control del ambiente paralelo
	MPI_Init(&argc,&argv);//Se inicializa el ambiente paralelo MPI para trabajar mediante el paso de mensajes
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);//Se asigna a la variable rank, el puntero que indica el número de proceso
	//que se esta ejecutando
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);// Se asigna a la variable size, el número de procesadores disponibles para usar
	
		if(procesos!=5){//Validación del número de procesadores a utilizar mediante un if
			printf("El numero de procesadores no es el requerido\n");
			exit(1);
		}else{
		switch(rango){//Sentencia case usada para identificar el procesador en turno mediante la variable rango
			//y asignarle acciones diferentes a los procesos
			case 0:
			destino=4;//Variable que indica el destino del mensaje
			fuente=1;//Variable que indica fuente de donde proviene el mensaje
			MPI_Recv(mensaje,max,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepción del mensaje entrante proveniente
			//del mensaje del proceso 1
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);//Impresión del mensaje entrante concatenado de la fuente haciendo uso
			//de la variable estado
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);//Se copia la cadena concatenado con el proceso destino
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);//Envío de la cadena del proceso 0
			break;
			case 1:
			destino=0;//Variable que indica el destino del mensaje
			fuente=2;//Variable que indica fuente de donde proviene el mensaje
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepción del mensaje entrante proveniente
			//del mensaje del proceso 2
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);//Impresión del mensaje entrante concatenado de la fuente haciendo uso
			//de la variable estado
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);//Se copia la cadena concatenado con el proceso destino
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);//Envío de la cadena del proceso 1
			break;
			case 2:
			destino=1;//Variable que indica el destino del mensaje
			fuente=3;//Variable que indica fuente de donde proviene el mensaje
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepción del mensaje entrante proveniente
			//del mensaje del proceso 3
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);//Impresión del mensaje entrante concatenado de la fuente haciendo uso
			//de la variable estado
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);//Se copia la cadena concatenado con el proceso destino
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);//Envío de la cadena del proceso 2
			break;
			case 3:
			destino=2;//Variable que indica el destino del mensaje
			fuente=4;//Variable que indica fuente de donde proviene el mensaje
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepción del mensaje entrante proveniente
			//del mensaje del proceso 4
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);//Impresión del mensaje entrante concatenado de la fuente haciendo uso
			//de la variable estado
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);//Se copia la cadena concatenado con el proceso destino
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);//Envío de la cadena del proceso 3
			break;
			case 4:
			printf("Anillo Invertido\n");//Impresión del título de la práctica
			destino=3;//Variable que indica el destino del mensaje
			fuente=0;//Variable que indica fuente de donde proviene el mensaje
			sprintf(cad,"Yo soy P%d recibiendo mensaje de",destino);//Se copia la cadena concatenado con el proceso destino
			MPI_Send(cad,strlen(cad)+1,MPI_CHAR,destino,etiqueta,MPI_COMM_WORLD);//Envío de la cadena del proceso 4
			MPI_Recv(mensaje,100,MPI_CHAR,fuente,etiqueta,MPI_COMM_WORLD,&estado);//Recepción del mensaje entrante proveniente
			//del mensaje del proceso 0
			printf("%s P%d\n",mensaje,estado.MPI_SOURCE);//Impresión del mensaje entrante concatenado de la fuente haciendo uso
			//de la variable estado
			break;
		}
	}
	MPI_Finalize();
	return 0;
}


