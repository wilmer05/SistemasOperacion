#ifndef std
	#define std
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
#endif

#ifndef largo
	#define largo 300
#endif

#ifndef estructuras
	#define estructuras
#endif


//Estructura que representa una caja de una lista generica
typedef struct Caja{
	void *cont;
	struct Caja *next,*prev;
} caja;


//Estructura que representa una lista
typedef struct {
	caja *first;
	int tam;
} lista;


//Estructura que representa un archivo a "crear"
typedef struct F{
	char *ruta;
	char *nombre;
	int tipo;
	lista *hijos;
} file;


