
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define tam 20

long double contador(long double n);

int main(int argc,char * argv[]){
	clock_t t_inicial,t_final;
	t_inicial=clock();
	int i,j;
	long double num;
	long double matriz[tam][tam];
	long double matrizResultante[tam][tam];
	double seg;
	FILE *fichero;
	char nombre_ficheroR[] = "contadorW.bin";
	char nombre_ficheroW[] = "contadorR.bin";
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
    resultado = fread(&num, sizeof(long double), 1, fichero);
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
  
  //Procesar la matriz
  for(i=0;i<tam;i++){
	  for(j=0;j<tam;j++){
		  matrizResultante[i][j]=contador(matriz[i][j]);
	  }
  }
	
	
	 //Escritura de la matriz Write
	 fichero = fopen(nombre_ficheroW, "wb");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para escritura.\n");
	  return -1;
  }
  for(i=0;i<tam;i++){
  resultado = fwrite(matrizResultante[i], sizeof(long double), tam, fichero);
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
			 printf("%Lf ",matrizResultante[i][j]);
		 }
		 printf("\n");
	 }*/
	t_final=clock();
	seg=(double)(t_final-t_inicial)/CLOCKS_PER_SEC;
	printf("%.16g milisegundos procesador %d\n",seg*1000.00,0);
	return 0;
}
long double contador(long double n){
	 if((int)n%2==0){
		 return n*n;
	 }else{
		 return sqrt(n);
	 }
}	
