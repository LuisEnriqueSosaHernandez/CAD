//Importación de librerias
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define tam 20 //Variable estática que define las dimensiones de las matrices

int fibonacci(int n);//Función para calcular fibonnaci de un número dado por parametro

int main(int argc,char * argv[]){
	//Declaración de variables
	clock_t t_inicial,t_final;
	t_inicial=clock();
	int i,j;
	long long int num;
	long long int matriz[tam][tam];
	long long int matrizResultante[tam][tam];
	double seg;
	FILE *fichero;
	char nombre_ficheroR[] = "fibonacciW.bin";
	char nombre_ficheroW[] = "fibonacciR.bin";
	size_t resultado;
		 printf("Procesando archivo...\n");   
		
		//Lectura de archivo para escritura en memoria   
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

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }
  
  //Procesando la matriz con fibonnaci
		for(i=0;i<tam;i++){
			for(j=0;j<tam;j++){
				matrizResultante[i][j]=fibonacci(matriz[i][j]);
			}
		}
	
	
	 //Escritura de la matriz en archivo
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
	t_final=clock();
	seg=(double)(t_final-t_inicial)/CLOCKS_PER_SEC;
	printf("%.16g milisegundos tiempo secuencial\n",seg*1000.00);
	return 0;
}
//Función fibonnaci
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
