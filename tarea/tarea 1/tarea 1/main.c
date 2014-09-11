#ifndef std
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
#endif

#ifndef operaciones
	#define operaciones
	#include"operaciones.h"
#endif

const int MAX_TAM = 10000;

int main(int argc, char **argv){

	FILE *fptr;
	char comando[MAX_TAM];

	if(argc<2) {
		perror("Faltan argumentos, la llamada debe ser: Ejecutable < nombre_archivo >");
		return 1;
	}

	//Abro el archivo de entrada
	fptr = fopen(argv[1],"r");
	if(fptr==NULL) {
		perror("Error al abrir archivo");
		return 1;
	}


	//Veo cual es la funcion comparadora usada para agregar archivos
	int (*funcptr)(caja *, caja *);
	funcptr = &comparador;

	//creo un arbol vacio
	lista *arbol;
	arbol = (lista *) malloc(sizeof(lista));
	inicializar(arbol);

	//Para cada linea de comando procedo
	while(fgets(comando,MAX_TAM,fptr)!=NULL){
		int size = strlen(comando);
		int indice = size-1;
		comando[indice]='\0';
		indice--;

		//Busco cual es el nombre real del archivo
		while(indice>=0 && comando[indice]!='/') 
			indice--;
		indice++;

		int opcion=-1;
		//Veo cual es la opcion (comando) a utilizar
		if(comando[0]=='m') opcion=0;
		if(comando[1]=='m') opcion=1;
		if(opcion==-1) continue;
		caja *nueva;
		file *arch;

		//Creo una nueva caja que se refiere al archivo en el comando a ejecutar
		nueva = (caja *) malloc(sizeof(caja));
		arch = (file *) malloc(sizeof(file));
		arch->hijos = (lista *) malloc(sizeof(lista));
		inicializar(arch->hijos);
		arch->nombre= (char *) malloc((size-indice+100)*(sizeof(char)));
		arch->ruta= (char *) malloc(size*sizeof(char));

		memset(arch->nombre,0,sizeof (arch->nombre));

		
		if(!opcion && comando[1]=='d') arch->tipo = 0;
		else if(!opcion) arch->tipo=1;
		strcpy(arch->ruta,comando+3);	
		strcpy(arch->nombre,comando+indice);
		nueva->next=nueva->prev=NULL;
		nueva->cont = (void *) arch;


		//Agrego o elimino el archivo dependiendo de la opcion
		mk_md_rm(comando,arbol,nueva,4,indice,opcion,funcptr);		
	}

	bfs(arbol);
	fclose(fptr);
	liberar_memoria(arbol);
	free(arbol);	
	
	return 0;
}
