#ifndef std
	#define std
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
#endif

#ifndef estructuras
	#define estructuras
	#include"estructura.h"
#endif

#ifndef listas
	#define listas
	#include"lista.h"
#endif


//Funcion utilizada para siempre agregar una caja a una lista
int comparador2(caja *c1, caja*c2){
	return 0;
}



//Funcion que compara si dos cajas que apuntan a file se refieren al mismo file
//La comparacion se hace por los nombres
int comparador(caja *c1, caja *c2){
	return !strcmp(((file *)(c1->cont))->nombre,((file *)(c2->cont))->nombre);
}


//Funcion utilizada para inicializar una lista
void inicializar(lista *l){
	l->first=NULL;
	l->tam=0;
}


/*Funcion que se utiliza para agregar un elemento a una lista si
este no esta contenido en la misma*/

void agregar_elem(lista *l, caja *c, int (*fptr)(caja *,caja *)){
	if(esta(l,c,fptr,0)==NULL){

		//si esta vacia simplemente esta caja es el primer elemento de la lista
		if(l->first==NULL) 
			l->first=c,c->prev=NULL;
		else{
			caja *tmp = l->first;

			//Me voy hasta el final de la lista y lo agrego
			while(tmp->next!=NULL){
				tmp=tmp->next;
			}
			tmp->next = c;
			c->prev=tmp;
		}

		c->next=NULL;

		(l->tam)++;
	}
	else liberar(c);
}

//Funcion utilizada para eliminar un elemento de una lista
void eliminar_elem(lista *l, caja *c, int (*fptr)(caja *,caja *)){
	esta(l,c,fptr,1);
	liberar(c);
}


//Funcion utilizada para liberar la memoria correspondiente a una caja
void liberar(caja *c){
	c->next=c->prev=NULL;
	file *ptr = (file *) (c->cont);
	free(ptr->hijos);
	free(ptr->nombre);
	free(ptr->ruta);
	free(ptr);
	free(c);
}


//Funcion que verifica si un elemento del arbol de directorios se puede borrar
//Esto sucede cuando es un archivo o un directorio vacio
int puedoBorrar(caja *borrar){
	if(borrar==NULL) return 0;

	file *ptr = (file *)(borrar->cont);

	//Si es un archivo puedo borrar
	if(ptr->tipo) return 1;
	
	//Si no lo es, es un directorio por lo que verifico si tiene hijos
	return !((ptr->hijos)->tam);
}


//Funcion utilizada para verificar si una caja c esta en una lista l
//usando la funcion fptr como funcion comparadora
//Si la opcion es 0 significa que solo quiero ver si esta el elemento
//Si es uno, quiero ver si esta, y si es asi borrar el elemento
caja *esta(lista *l, caja *c, int (*fptr)(caja *, caja *), int opcion){
	caja *buscar = l->first;

	while(buscar!=NULL){
		if((*fptr)(buscar, c)) 
			break;
		buscar = buscar-> next;
	}

	
	//Si solo tengo que buscar, retorno
	if(!opcion) return buscar;

	//Si tengo que borrar libero memoria y actualizo
	if(puedoBorrar(buscar)){
		if(buscar->prev==NULL) 
			l->first = buscar->next;
		else
			(buscar->prev)->next = buscar->next;

		if(buscar->next!=NULL)
			(buscar->next)->prev = buscar->prev;

		(l->tam)--;
		liberar(buscar);
	}
	return NULL;

}
