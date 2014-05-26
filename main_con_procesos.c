#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
 #include <sys/wait.h>
#include"entrada.h"
#include"estructuras.h"

int status;

void act(int part){
  
	  for(int i=0;i<I/N;i++)
	      modificar_particion(part,i);
	  
	  if(part==N-1)
	    for(int i=0;i<I%N;i++)
	      modificar_particion(part,I/N+i);
}


//el main se encarga de realizar el flush
int main (int argc, char *argv[]){

	validar_inicializar(argc, argv);
	
	abro_particiones_modif();
	//modifico todo lo que tenga que modificar en las 
	//particiones

	//aqui es donde se realiza el flush
	
	
	int j=0;
	for(int i=0;i<N;i++){
	  if(i>=P)
	    wait(&status);
	  if(!fork()){
	    act(i);
	    exit(0);
	  }
	}
	
	for(int i=0;i<P;i++)
	  wait(&status);
	
	//termine de modificar y espere a que se modificara todo
	//y cierro los descriptores para que se guarde
	cierroParticiones();
	
	
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
