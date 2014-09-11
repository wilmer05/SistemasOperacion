#ifndef std
	#define std
	#include<stdio.h>
	#include<string.h>
	#include<stdlib>
#endif

#ifndef estructuras
	#define estructuras
	#include"estructura.h"
#endif

#ifndef listas
	#define listas
#endif


//Funciones que seran explicada en el archivo que contiene su codigo fuente (lista.c)

int comparador2(caja *, caja *);

int comparador(caja *, caja *);

void inicializar(lista *);

void agregar_elem(lista *, caja *, int (*fptr)(caja *,caja *));

void eliminar_elem(lista *, caja *, int (*fptr)(caja *,caja *));

int puedoBorrar(caja *);

void liberar(caja *);

caja *esta(lista *, caja *, int (*fptr)(caja *, caja *), int);
