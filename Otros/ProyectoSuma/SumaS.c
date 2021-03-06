
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
	int i,j;
	long long int numero;
	long long int matriz[tMatriz][tMatriz];
	long long int matriz2[tMatriz][tMatriz];
	long long int matrizAlmacen[tMatriz][tMatriz];
	double seg;
	FILE *fichero;
	char nombre_ficheroR[] = "SumaW.bin";
	char nombre_ficheroR2[] = "SumaW2.bin";
	char nombre_ficheroW[] = "SumaR.bin";
	size_t resultado;
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
    resultado = fread(&numero, sizeof(long long int), 1, fichero);
	if (resultado != 1)
	{
		break;
	}
	matriz[i][j]=numero;
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
    resultado = fread(&numero, sizeof(long long int), 1, fichero);
	if (resultado != 1)
	{
		break;
	}
	matriz2[i][j]=numero;
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
 
 //Procesando la matriz
 for(i=0;i<tMatriz;i++){
				for(j=0;j<tMatriz;j++){
					matrizAlmacen[i][j]=Sumando(matriz[i][j],matriz2[i][j]);		
				}
		}
	
	
	 //Escritura de la matriz Write
	 fichero = fopen(nombre_ficheroW, "wb");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para escritura.\n");
	  return -1;
  }
  for(i=0;i<tMatriz;i++){
  resultado = fwrite(matrizAlmacen[i], sizeof(long long int), tMatriz, fichero);
  if (resultado!=tMatriz)
  {
	  printf("No se han escrito todos los %d números del array.\n", tMatriz);
  }
}

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }else{
	  printf("La matriz resultante ha sido escrita en el archivo\n");
  }
	t_final=clock();
	seg=(double)(t_final-t_inicial)/CLOCKS_PER_SEC;
	printf("%.16g milisegundos procesador %d\n",seg*1000.00,0);
	return 0;
}
int Sumando(int n,int n2){
	return n+n2;
}	
