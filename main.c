#include<stdio.h>
#include"estructuras.h"

#define TAM 1000

char comando[TAM];

int IsaNumber(int num, char arg)
{
  if (!num) {
    printf("Error en linea de argumentos \n");
    printf("El argumento %c debe ser un entero \n",arg);
    printf("USO: argumentos I [-n N] [-p P] [-f F] arch1 arch2 \n");
    return (0);
  }
  return (1);
}

main (int argc, char *argv[]){
	int num_I, num_P, num_N, num_F;
  	char *arch1, *arch2;
	int posicion;
  /***************************************************************
  /* Chequea el numero de argumentos minimo y maximo
  /***************************************************************/

  	if ((argc < 4) || (argc > 10)) {
    	printf("Error en linea de argumentos \n");
	    printf("USO: argumentos I [-n N] [-p P] [-f F] arch1 arch2 \n");
	    exit(1);
  	}

  /***************************************************************
  /* Chequea que I sea un entero valido.
  /***************************************************************/

  	num_I= atoi(argv[1]);

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
      		num_N = atoi(argv[++posicion]);
      		if (!IsaNumber(num_N,'N')) {
				exit(1);
      		}
      		posicion = posicion + 1;
      		continue;
    	}
    	if (!strcmp(argv[posicion],"-p")) {
      		num_P = atoi(argv[++posicion]);
      		if (!IsaNumber(num_P,'P')) {
				exit(1);
      		}
      		posicion = posicion + 1;
	      	continue;
	    }
	    if (!strcmp(argv[posicion],"-f")) {
	      	num_F = atoi(argv[++posicion]);
	      	if (!IsaNumber(num_F,'F')) {
				exit(1);
	      	}
	      	posicion = posicion + 1;
	      	continue;
	    } else {
	    // Caso por defecto 
	     	printf("Error en linea de argumentos \n");
	      	printf("USO: argumentos I [-n N] [-p P] [-f F] arch1 arch2 \n");
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

	f1 = fopen(arch1,"r");
	f2 = fopen(arch2,"r");
  /***************************************************************
  /* Despues vendria el chequeo de que los archivos arch1 y arch2 
  /* existan
  /***************************************************************/

	while(fgets(comando,TAM,f1)!=NULL){
		sscanf(comando,"%d,%d,%d,%[^,],%[^,],%[^,],%d",&t1,&t2,&t3,fecha1,fecha2,perm,&t4);
		printf("%d %d %d %s %s %s %d\n",t1,t2,t3,fecha1, fecha2,perm,t4);

		//creo inodo

	}
	close(f1);
	
	char modo[5];
	while(fgets(comando,TAM,f2)!=NULL){
		sscanf(comando,"%d %s %s",&t1,modo,fecha2);
		printf("%d %s %s\n",t1,modo,fecha2);

		//creo inodo

	}
	close(f2);
	

	return 0;
}
