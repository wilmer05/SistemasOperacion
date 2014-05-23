#include<stdio.h>

#ifdef estructuras
#define estructuras
	
	typedef struct{
		int tam, id, modif;
		char *fecha;
		char *last;
		void *dir;
		char *permisos;

	} inodo;

	void liberar_inodo(inodo *i){
		free(fecha);
		free(last);
		free(dir);
		free(permisos);
	}

	void inic_inodo(inodo *i, int tam,int id,int modif,char *fecha,char *last, void *dir, char *perm){
		i->tam = tam;
		i->id = id;
		i->modif = modif;
		i->dir = dir;

		i->fecha = (char *) malloc(strlen(fecha));
		strcpy(i->fecha, fecha);

		i->last = (char *) malloc(strlen(last));
		strcpy(i->last, last);

		i->perm = (char *) malloc(strlen(perm));
		strcpy(i->perm, perm);

	}

	int p,n; //numero de hijos concurrentes y numero de particiones, respectivamente
	inodo inodos[110];	

#endif
