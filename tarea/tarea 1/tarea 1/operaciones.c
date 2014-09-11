#ifndef operaciones
	#define operaciones
	#include"operaciones.h"
#endif

#ifndef listas
	#define listas
	#include"lista.h"
#endif


//Funcion utilizada para liberar la memoria de forma recursiva del arbol de 
//directorios
void liberar_memoria(lista *arbol){
	caja *c = arbol->first;
	while(c!=NULL){
		caja *otr = c;
		liberar_memoria(((file *)(c->cont))->hijos);

		c = c->next;
		liberar(otr);
	}
}

//Funcion utilizada para hacer un recorrido en bfs en el arbol de directorios
//Es una implementacion iterativa del algoritmo BFS, y que utiliza como
//Estructura auxiliar una lista

void bfs(lista *arbol){
	lista *aux = (lista *) malloc(sizeof(lista));
	inicializar(aux);
	caja *f = arbol->first;
	while(f!=NULL){
		caja *nuev;
		nuev = (caja*) malloc(sizeof(caja));
		nuev->cont = (void *) f;
		f = f->next;
		agregar_elem(aux,nuev,&comparador2);
	}

	caja *recorrido = aux->first;
	
	while(NULL!=recorrido){
		file *ptr = (file *)(((caja *)(recorrido->cont))->cont);
		printf("%s\n",ptr->ruta);
		caja *ptr2 = (ptr->hijos)->first;
		while(ptr2!=NULL){
			caja *nuev;
			nuev = (caja *) malloc(sizeof(caja));
			nuev->cont=(void *) ptr2;
			agregar_elem(aux,nuev,&comparador2);
			ptr2=ptr2->next;
		}
		recorrido = recorrido->next;
		
	}

	recorrido = aux->first;

	while(NULL!=recorrido){
		f=  recorrido;
		recorrido = recorrido->next;
		free(f);

	}

	free(aux);
	
}


//Funcion recursiva utilizada para llegar hasta el directorio correcto
//al que se debe agregar un archivo o un directorio

void mk_md_rm(char *ruta, lista *l, caja *c,int ind1, int ind2, int opc, int (*fptr)(caja *, caja*)){

	//Si ya es el directorio en el que debo agregar o eliminar, entonces procedo
	if(ind1>=ind2){
		if(!opc) agregar_elem(l,c,fptr);
		else eliminar_elem(l,c,fptr);
		return; 
	}

	//sino busco en cual directorio ahora me tengo que mover para poner el
	//archivo
	char *sig;
	int tmp = ind1;
	while(ruta[ind1]!='/') ind1++;
	int tam = ind1-tmp+5;
	sig = (char *) malloc(tam);
	memset(sig,0,sizeof sig);

	for(int i = tmp ;i<ind1;i++) sig[i-tmp] = ruta[i];	
	caja *busc = l->first;

	//Busco el directorio al cual me debo move	
	while(busc!=NULL){
		if(!strcmp(sig,((file *)(busc->cont))->nombre)) break;
		busc=busc->next;
	}
	
	ind1++;
	free(sig);
	//Si no existe entonces no agrego nada
	if(busc==NULL) return;
	//Sino sigo buscando recursivamente
	if((((file *)(busc->cont))->tipo)==0)
		mk_md_rm(ruta,((file*)(busc->cont))->hijos,c,ind1,ind2,opc,fptr);
	else liberar(c);

}
