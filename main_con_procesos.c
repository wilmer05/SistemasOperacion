#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
 #include <sys/wait.h>
#include"tiempo.h"
#include"entrada.h"
#include"estructuras.h"

int status;

void act(int part){
	  int tiempo_solo = Tomar_Tiempo();
	  for(int i=0;i<I/N;i++)
	      modificar_particion(part,i);
	  
	  if(part==N-1)
	    for(int i=0;i<I%N;i++)
	      modificar_particion(part,I/N+i);
	  printf("Tiempo de la ejecucion de la unidad encargada de\
la particion %d es: %d\n",part,Tomar_Tiempo()-tiempo_solo);
}


//el main se encarga de realizar el flush
int main (int argc, char *argv[]){

	t_total1 = Tomar_Tiempo();
	validar_inicializar(argc, argv);
	
	abro_particiones_modif();
	//modifico todo lo que tenga que modificar en las 
	//particiones
	
	//y empiezo a tomar el tiempo desde aqui
	total_proc1 = Tomar_Tiempo();
	
	//aqui es donde se realiza el flush
	int j=0;
	for(int i=0;i<N;i++){
	  if(i>=P)
	    wait(&status);
	  int t1 = Tomar_Tiempo();
	  if(!fork()){
	     printf("Tiempo de creacion de la unidad encargada \
de la particion %d es: %d\n",i,Tomar_Tiempo()-t1);
	    act(i);
	    exit(0);
	  }
	}
	
	for(int i=0;i<P;i++)
	  wait(&status);
	total_proc2 = Tomar_Tiempo();
	
	//termine de modificar y espere a que se modificara todo
	//y cierro los descriptores para que se guarde
	cierroParticiones();
	
	t_total2 = Tomar_Tiempo();
	
	printf("\nTiempo total de los procesos: %d\n",total_proc2-total_proc1);
	printf("Tiempo total: %d\n",t_total2-t_total1);
	
	/*
	 * Descomentar el siguiente codigo si quiere que 
	 * se impriman las particiones
	 * leidas desde los archivos luego de su modificacion
	*/
	
	 
	/*
	imprimirTodo();
	*/
	
	
	
	return 0;
}
