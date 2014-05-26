//Codigo hecho por: Wilmer Bandres. Carnet: 10-10055
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include"tiempo.h"
#include"entrada.h"
#include"estructuras.h"

par hilos[110];

pthread_mutex_t ms[110]; //mutex utilizados para la cantidad
			 //de hilos ejecutandose al mismo tiempo
pthread_t ids[110];

void *act(void *ptr){
	  int hilo = ((par *)ptr)->y;
	  int tiempo_solo = Tomar_Tiempo();
	  pthread_mutex_lock(&ms[hilo]);
	  int part = ((par *)ptr)->x;
	  
	  for(int i=0;i<I/N;i++)
	      modificar_particion(part,i);
	  
	  if(part==N-1)
	    for(int i=0;i<I%N;i++)
	      modificar_particion(part,I/N+i);
	  
	  pthread_mutex_unlock(&ms[hilo]);
	  printf("Tiempo de ejecucion de la unidad de hilo %d, \
encargado de la particion %d es : %d\n",\
				  hilo,part,Tomar_Tiempo()-tiempo_solo);
}


int main (int argc, char *argv[]){

	t_total1 = Tomar_Tiempo();
	validar_inicializar(argc, argv);
	
	
	for(int i=0;i<110;i++)
	   pthread_mutex_init(&ms[i],NULL);
	
	abro_particiones_modif();
	
	//medidor del tiempo de ejecucion de todos los procesos
	total_proc1 = Tomar_Tiempo();
	
	//modifico todo lo que tenga que modificar en las 
	//particiones
	
	//la variable j representa a que hilo
	//le tocara modificar la particion i del ciclo for
	int j=0;
	for(int i=0;i<N;i++){
	  hilos[i].y=j;
	  hilos[i].x=i;
	  
	  //Actualizo la particion i con el thread j
	  tiempo_creac1 = Tomar_Tiempo();
	  pthread_create(&ids[i],NULL,act,(void *)&hilos[i]);
	  printf("Tiempo de creacion de la unidad encargada \
de la particion %d es: %d\n",i,Tomar_Tiempo()-tiempo_creac1);
	  j++;
	  j%=P;
	}
	for(int i=0;i<N;i++)
	  pthread_join(ids[i],NULL);
	total_proc2 = Tomar_Tiempo();
	
	//termine de modificar y espere a que se modificara todo
	//y cierro los descriptores para que se guarden las 
	//modificaciones hechas en las particiones
	cierroParticiones();
	
	t_total2 = Tomar_Tiempo();
	
	printf("\nTiempo total de los procesos: %d\n",total_proc2-total_proc1);
	printf("Tiempo total de ejecucion: %d\n",t_total2-t_total1);
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
