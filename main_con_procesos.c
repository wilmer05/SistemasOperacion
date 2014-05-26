#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include"entrada.h"
#include"estructuras.h"

par hilos[110];

pthread_mutex_t ms[110]; //mutex utilizados para la cantidad
			 //de hilos ejecutandose al mismo tiempo
pthread_t ids[110];

void *act(void *ptr){
	  int hilo = ((par *)ptr)->y;
	  pthread_mutex_lock(&ms[hilo]);
	  int part = ((par *)ptr)->x;
	  
	  for(int i=0;i<I/N;i++)
	      modificar_particion(part,i);
	  
	  if(part==N-1)
	    for(int i=0;i<I%N;i++)
	      modificar_particion(part,I/N+i);
	  
	  pthread_mutex_unlock(&ms[hilo]);
}


//el main se encarga de realizar el flush
int main (int argc, char *argv[]){

	validar_inicializar(argc, argv);
  
	
	for(int i=0;i<110;i++)
	   pthread_mutex_init(&ms[i],NULL);
	
	abro_particiones_modif();
	//modifico todo lo que tenga que modificar en las 
	//particiones

	//aqui es donde se realiza el flush
	
	int j=0;
	for(int i=0;i<N;i++){
	  hilos[i].y=j;
	  hilos[i].x=i;
	  
	  //Actualizo la particion i con el thread j
	  pthread_create(&ids[i],NULL,act,(void *)&hilos[i]);
	  j++;
	  j%=P;
	}
	for(int i=0;i<N;i++)
	  pthread_join(ids[i],NULL);
	//termine de modificar y espere a que se modificara todo
	//y cierro los descriptores para que se guarde
	cierroParticiones();
	
	
	/*
	 * Descomentar el siguiente codigo si quiere que 
	 * se impriman las particiones
	 * leidas desde los archivos luego de su modificacion
	*/
	
	 
	
	imprimirTodo();
	
	
	
	
	return 0;
}
