#include <stdio.h>
#define TAM 20

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
							{20,21,34,6,5,4,6,4,8,6,12,34,11,23,22,23,15,15,16,20},
							{18,28,37,14,11,9,2,1,3,11,12,4,3,2,21,21,15,2,6,7},
							{33,21,4,15,15,14,16,14,18,16,1,4,1,3,2,3,4,8,3,1},
							{2,2,3,3,2,11,11,11,6,1,22,2,6,7,2,22,2,6,4,8},
							{2,2,3,16,15,14,8,9,4,3,2,4,12,23,22,23,12,36,2,22},
							{9,1,12,15,14,18,19,20,19,7,5,3,1,3,6,5,23,24,25,26},
							{6,21,19,18,26,31,25,34,28,29,26,34,12,2,3,9,2,4,7,9},
							{15,1,25,14,6,8,1,7,5,8,22,34,33,25,12,19,3,4,14,26},
							{33,2,34,16,15,14,16,17,29,28,18,25,33,5,2,3,12,14,12,25},
							{20,1,1,2,2,2,3,3,8,6,11,1,12,25,21,20,14,12,13,14},
							{20,21,34,26,25,24,16,4,12,11,20,30,20,10,4,2,12,24,23,25},
							{29,27,34,6,5,4,6,4,8,6,12,34,11,23,22,23,14,15,13,14},
							{6,7,9,1,5,4,6,7,7,9,11,24,34,25,20,21,13,12,11,10},
							{3,19,31,7,27,18,16,14,18,16,12,11,1,22,24,22,12,10,10,10},
							{6,1,4,16,15,14,8,7,32,34,11,12,10,20,20,20,14,35,14,15},
							{4,3,1,1,11,7,1,1,19,5,7,7,2,3,2,5,12,14,14,15},
							{3,34,14,12,12,8,1,17,19,15,7,27,26,23,20,24,31,32,12,31},
							{15,34,14,12,12,8,1,16,19,5,17,27,6,23,20,4,14,14,12,14},
							{34,34,9,8,7,8,1,16,18,15,17,7,26,3,20,6,12,14,13,10},
							{34,34,14,12,12,8,1,16,19,15,17,7,12,23,2,15,1,1,2,2}
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

