#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define tam 16

int fibonacci(int n);

int main(int argc,char * argv[]){
	clock_t t_inicial,t_final;
	int rango,procesos,etiqueta=0;
	int i,j,llenado,contProcesos;
	long long int num;
	long long int matriz[tam][tam];
	long long int matrizResultante[tam][tam];
	long long int matrizTemporal[tam][tam];
	long long int vector[tam];
	float divisionTrabajo;
	double seg;
	FILE *fichero;
	char nombre_ficheroR[] = "fibonacciW.bin";
	char nombre_ficheroW[] = "fibonacciR.bin";
	size_t resultado;
    MPI_Status estado;	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);
	
	 if(procesos!=7) {
        printf("El numero de procesadores no es el requerido\n");
        exit(1);
    } else {
		divisionTrabajo=(float)tam/(float)(procesos-1);
		divisionTrabajo=round(divisionTrabajo);
		int acumulador=0;
		int vectorTrabajo[procesos-1];
		for(i=0;i<(procesos-2);i++){
		acumulador+=divisionTrabajo;
		vectorTrabajo[i]=divisionTrabajo;
	}
	vectorTrabajo[procesos-2]=tam-acumulador;
	switch(rango){
		case 0:
		 printf("Procesando archivo...\n");   
		
		//LLenado de la matriz  Read    
            fichero = fopen(nombre_ficheroR, "rb");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para lectura.\n");
	  return -1;
  }
  i=0;
  j=0;
  while (!feof(fichero))
  {
    resultado = fread(&num, sizeof(long long int), 1, fichero);
	if (resultado != 1)
	{
		break;
	}
	matriz[i][j]=num;
	j++;
	if(j>=tam){
		j=0;
		i++;
	}
  }

  if (ferror(fichero)!=0)
  {
	  printf("Ha ocurrido algún error en la lectura de números.\n");
  }
  /*else
  {
	 for(i=0;i<tam;i++){
		 for(j=0;j<tam;j++){
			 printf("%lld ",matriz[i][j]);
		 }
		 printf("\n");
	 }
  }*/

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }
  
  
            i=0;
            contProcesos=1;
		while(i<tam){
			for(j=0;j<vectorTrabajo[contProcesos-1];j++){
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
	
	
	 //Escritura de la matriz Write
	 fichero = fopen(nombre_ficheroW, "wb");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para escritura.\n");
	  return -1;
  }
  for(i=0;i<tam;i++){
  resultado = fwrite(matrizResultante[i], sizeof(long long int), tam, fichero);
  if (resultado!=tam)
  {
	  printf("No se han escrito todos los %d números del array.\n", tam);
  }
}

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }else{
	  printf("La matriz resultante ha sido escrita en el archivo\n");
  }
	 /*for(i=0;i<tam;i++){
		 for(j=0;j<tam;j++){
			 printf("%lld ",matrizResultante[i][j]);
		 }
		 printf("\n");
	 }*/
	break;
		default:
		t_inicial=clock();
		for(i=0;i<vectorTrabajo[rango-1];i++){
		MPI_Recv(vector,tam,MPI_LONG_LONG_INT,0,etiqueta,MPI_COMM_WORLD,&estado);
		//printf("Recibido en procesador %d desde %d\n",rango,estado.MPI_SOURCE);
		for(j=0;j<tam;j++){
			matrizTemporal[i][j]=fibonacci(vector[j]);			
		}
	}
		for(i=0;i<vectorTrabajo[rango-1];i++){
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
