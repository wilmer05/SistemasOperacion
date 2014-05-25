#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"estructuras.h"


#define TAM 1000

char comando[TAM];

int IsaNumber(int num, char arg)
{
  if (!num) {
    printf("Error en linea de argumentos \n");
    printf("El argumento %c debe ser un entero \n",arg);
    printf("USO: argumentos I [-n N] [-p P] arch1 arch2 \n");
    return (0);
  }
  return (1);
}

int main (int argc, char *argv[]){
	int num_I, num_P, num_N;
  	char *arch1, *arch2;
	int posicion;
  /***************************************************************
  /* Chequea el numero de argumentos minimo y maximo
  /***************************************************************/
	P=N=1;
  	if ((argc < 4) || (argc > 8)) {
    	printf("Error en linea de argumentos \n");
	    printf("USO: argumentos I [-n N] [-p M] arch1 arch2 \n");
	    exit(1);
  	}

  /***************************************************************
  /* Chequea que I sea un entero valido.
  /***************************************************************/

  	I = num_I= atoi(argv[1]);

  	if (!IsaNumber(num_I,'I')) {
    	exit(1);
  	}

  /***************************************************************
  /* Chequea el resto de los parametros
  /*  while ((posicion < argc - 2))
  /*  Con este condicional valido solo las opciones con - (el - 2) 
  /*  evita que se procesen los dos ultimos argumentos dentro del while.
  /***************************************************************/
  	posicion=2;

  	while ((posicion < argc - 2)) {
    	if (!strcmp(argv[posicion],"-n")) {
      		N = num_N = atoi(argv[++posicion]);
      		if (!IsaNumber(num_N,'N')) {
				exit(1);
      		}
      		posicion = posicion + 1;
      		continue;
    	}
    	if (!strcmp(argv[posicion],"-p")) {
      		P = num_P = atoi(argv[++posicion]);
      		if (!IsaNumber(num_P,'M')) {
				exit(1);
      		}
      		posicion = posicion + 1;
	      	continue;
	    }
	 else {
	    // Caso por defecto 
	     	printf("Error en linea de argumentos \n");
	      	printf("USO: argumentos I [-n N] [-p M] arch1 arch2 \n");
	      	exit(1);
	    }
	}
	  
  	arch1 = argv[posicion++];
 	arch2 = argv[posicion];

	char fecha1[30],fecha2[30];
	char perm[30];
	FILE *f1;
	FILE *f2;
	int t1,t2,t3,t4;
	
	abroParticiones();
	
	f1 = fopen(arch1,"r");
	f2 = fopen(arch2,"r");
  /***************************************************************
  /* Despues vendria el chequeo de que los archivos arch1 y arch2 
  /* existan
  /***************************************************************/
	int indice1=0;
	int indice2=0;
	int val = (I%N)?1:0;
	
	
	while(fgets(comando,TAM,f1)!=NULL){
		if(indice1>=I/N && indice2!=N-1)
		  indice1=0,indice2++;
		sscanf(comando,"%d,%d,%d,%[^,],%[^,],%[^,],%d",&t1,&t2,&t3,fecha1,fecha2,perm,&t4);
		//printf("%d %d %d %s %s %s %d\n",t1,t2,t3,fecha1, fecha2,perm,t4);
		//printf("%d %d\n",indice1,indice2);
		//incicializo inodos del arreglo de particiones
		fprintf(files[indice2],comando);
		inic_inodo(&inodos[(I/N)*indice2+indice1], t2,t1, t3,fecha1,fecha2,t4,perm);
		indice1++;
		

	}
	fclose(f1);
	indice1=indice2=0;
	
	char modo[5];
	while(fgets(comando,TAM,f2)!=NULL){
		int ind1,ind2;
		sscanf(comando,"%d %s %s",&t1,modo,fecha2);
		//printf("%d %s %s\n",t1,modo,fecha2);
		inodo *ptr = buscar_inodo(t1);
		//printf("%d\n",ptr-inodos);
		//modifico inodos
		if(ptr)
		  modificar_inodo(ptr,modo,fecha2);

	}
	fclose(f2);
	
	
	//imprimirTodo();
	
	liberar_memoria();
	cierroParticiones();
	return 0;
}
