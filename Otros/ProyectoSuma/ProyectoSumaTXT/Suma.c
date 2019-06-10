#include <string.h>
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define tMatriz 20

int Sumando(int n,int n2);

int main(int argc,char * argv[]){
	clock_t t_inicial,t_final;
	t_inicial=clock();
	int rango,procesos,etiqueta=0;
	int i,j,contadorProcesos;
	long long int numero;
	long long int matriz[tMatriz][tMatriz];
	long long int matriz2[tMatriz][tMatriz];
	long long int matrizAlmacen[tMatriz][tMatriz];
	long long int matrizRespuesta[tMatriz][tMatriz];
	long long int vector1[tMatriz];
	long long int vector2[tMatriz];
	float partirMatriz;
	double seg;
	FILE *fichero;
	char nombre_ficheroR[] = "SumaR.txt";
	char nombre_ficheroR2[] = "SumaR2.txt";
	char nombre_ficheroW[] = "SumaW.txt";
	size_t resultado;
    MPI_Status estado;	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);
	MPI_Comm_size(MPI_COMM_WORLD,&procesos);
	
	 if(procesos!=11) {
        printf("El numero de procesadores no es el requerido\n");
        exit(1);
    } else {
		partirMatriz=(float)tMatriz/(float)(procesos-1);
		partirMatriz=round(partirMatriz);
		int acumulador=0;
		int vectorTrabajo[procesos-1];
		for(i=0;i<(procesos-2);i++){
		acumulador+=partirMatriz;
		vectorTrabajo[i]=partirMatriz;
	}
	vectorTrabajo[procesos-2]=tMatriz-acumulador;
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
    resultado = fscanf(fichero,"%lld",&matriz[i][j]);
	if (resultado != 1)
	{
		break;
	}
	j++;
	if(j>=tMatriz){
		j=0;
		i++;
	}
  }

  if (ferror(fichero)!=0)
  {
	  printf("Ha ocurrido algún error en la lectura de números.\n");
  }
  
  		//LLenado de la matriz 2  Read    
            fichero = fopen(nombre_ficheroR2, "rb");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para lectura.\n");
	  return -1;
  }
  i=0;
  j=0;
  while (!feof(fichero))
  {
     resultado = fscanf(fichero,"%lld",&matriz2[i][j]);
	if (resultado != 1)
	{
		break;
	}
	j++;
	if(j>=tMatriz){
		j=0;
		i++;
	}
  }

  if (ferror(fichero)!=0)
  {
	  printf("Ha ocurrido algún error en la lectura de números.\n");
  }
  

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }
  
  //enviar
            i=0;
            contadorProcesos=1;
		while(i<tMatriz){
			for(j=0;j<vectorTrabajo[contadorProcesos-1];j++){
		MPI_Send(&matriz[i],tMatriz,MPI_LONG_LONG_INT,contadorProcesos,etiqueta,MPI_COMM_WORLD);
		MPI_Send(&matriz2[i],tMatriz,MPI_LONG_LONG_INT,contadorProcesos,etiqueta,MPI_COMM_WORLD);
		i++;
		//printf("Enviado desde %d\n",rango);
	}
	contadorProcesos++;
	}
	
	 i=0;
            contadorProcesos=1;
		while(i<tMatriz){
			for(j=0;j<vectorTrabajo[contadorProcesos-1];j++){
		MPI_Recv(&matrizAlmacen[i],100,MPI_LONG_LONG_INT,contadorProcesos,etiqueta,MPI_COMM_WORLD,&estado);
		i++;	
	}
	contadorProcesos++;
	}
	
	
	 //Escritura de la matriz Write
	 fichero = fopen(nombre_ficheroW, "wb");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para escritura.\n");
	  return -1;
  }
  for(i=0;i<tMatriz;i++){
			for(j=0;j<tMatriz;j++){
				resultado=fprintf(fichero,"%lld ",matrizAlmacen[i][j]);
				if(resultado<0){
					printf("No se han escrito todos los numeros\n");
					break;
				}
			}
			resultado=fprintf(fichero,"%c" ,'\n');
			if(resultado<0){
					printf("No se han escrito todos los numeros\n");
					break;
				}
		}

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }else{
	  printf("La matriz resultante ha sido escrita en el archivo\n");
  }
	break;
		default:
		
		for(i=0;i<vectorTrabajo[rango-1];i++){
		MPI_Recv(vector1,tMatriz,MPI_LONG_LONG_INT,0,etiqueta,MPI_COMM_WORLD,&estado);
		MPI_Recv(vector2,tMatriz,MPI_LONG_LONG_INT,0,etiqueta,MPI_COMM_WORLD,&estado);
		//printf("Recibido en procesador %d desde %d\n",rango,estado.MPI_SOURCE);
		for(j=0;j<tMatriz;j++){
			matrizRespuesta[i][j]=Sumando(vector1[j],vector2[j]);			
		}
	}
		for(i=0;i<vectorTrabajo[rango-1];i++){
		MPI_Send(&matrizRespuesta[i],tMatriz,MPI_LONG_LONG_INT,0,etiqueta,MPI_COMM_WORLD);
		//printf("Enviado desde procesador %d\n",rango);
	}
	break;
		}
	}
	MPI_Finalize();
	t_final=clock();
	seg=(double)(t_final-t_inicial)/CLOCKS_PER_SEC;
	printf("%.16g milisegundos procesador %d\n",seg*1000.00,rango);
	return 0;
}
int Sumando(int n,int n2){
	return n+n2;
}	
