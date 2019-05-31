#include <stdio.h>
#define TAM 16

int main(void)
{
  FILE *fichero;
  int i,j,opcion;
  long long int num;
  char nombre_ficheroW[] = "fibonacciW.bin";
  char nombre_ficheroR[] = "fibonacciR.bin";
  size_t resultado;
  long long int matrizR[TAM][TAM];
  long long int matrizW[TAM][TAM] = {
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23},
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23}
								};
	
//Write
do{
	printf("Que deseas hacer\n");
	printf("1.Escribir matriz\n");
	printf("2.Leer matriz resultante\n");
	printf("3.Salir\n");
	printf("Ingresa una opcion: \n");
	scanf("%d",&opcion);
	
	switch(opcion){
		case 1:
  fichero = fopen(nombre_ficheroW, "wb");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para escritura.\n");
	  return -1;
  }
  for(i=0;i<TAM;i++){
  resultado = fwrite(matrizW[i], sizeof(long long int), TAM, fichero);
  if (resultado!=TAM)
  {
	  printf("No se han escrito todos los %d números del array.\n", TAM);
  }
}

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }else{
	  printf("La matriz ha sido escrita en el archivo\n");
	  for(i=0;i<TAM;i++){
		 for(j=0;j<TAM;j++){
			 printf("%lld ",matrizW[i][j]);
		 }
		 printf("\n");
	 }
  }
  break;
  case 2:
  //Read
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
	matrizR[i][j]=num;
	j++;
	if(j>=TAM){
		j=0;
		i++;
	}
  }

  if (ferror(fichero)!=0)
  {
	  printf("Ha ocurrido algún error en la lectura de números.\n");
  }
  else
  {
	 for(i=0;i<TAM;i++){
		 for(j=0;j<TAM;j++){
			 printf("%lld ",matrizR[i][j]);
		 }
		 printf("\n");
	 }
  }

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }
  break;
  case 3:
  printf("Hasta luego");
  break;
  default:
  printf("Opcion incorrecta\n");
  break;
}
}while(opcion!=3);
  return 0;
}

