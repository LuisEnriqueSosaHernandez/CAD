#include <stdio.h>
#define TAM 20

int main(void)
{
  FILE *fichero;
  int i,j,opcion;
  long double num;
  char nombre_ficheroW[] = "contadorW.bin";
  char nombre_ficheroR[] = "contadorR.bin";
  size_t resultado;
  long double matrizR[TAM][TAM];
  long double matrizW[TAM][TAM] = {
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
							{20.0,21.0,34.0,6.0,5.0,8.0,3.0,6.0,6.9,6.1,50.0,32.0,3.0,14.0,15.0,16.0,7.0,6.0,2.0,1.0},
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
  resultado = fwrite(matrizW[i], sizeof(long double), TAM, fichero);
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
			 printf("%Lf ",matrizW[i][j]);
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
    resultado = fread(&num, sizeof(long double), 1, fichero);
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
			 printf("%Lf ",matrizR[i][j]);
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

