#include<stdio.h>
#include<stdlib.h>

#ifndef estructuras
#define estructuras
	
	typedef struct{
		int tam, i ,id,dir;
		char *fecha;
		char *last;
		char *permisos;

	} inodo;
	
	int P,N,I; //numero de hijos concurrentes y numero de particiones, respectivamente
	inodo inodos[110];
	FILE *files[110];//particiones
	
	void print_inodo(inodo *i){
	  printf("%d, %d, %d, %s, %s, %s, %d\n",i->i,i->tam,i->id,\
				i->fecha,i->last,i->permisos,i->dir);
	  
	}

	void liberar_inodo(inodo *i){
		free(i->fecha);
		free(i->last);
		free(i->permisos);
	}

	void inic_inodo(inodo *i, int tam,int ii,int id,char *fecha,char *last, int dir, char *perm){
		i->tam = tam;
		i->i = ii;
		i->id = id;
		i->dir = dir;

		i->fecha = (char *) malloc(strlen(fecha)+1);
		strcpy(i->fecha, fecha);

		i->last = (char *) malloc(strlen(last)+1);
		strcpy(i->last, last);

		i->permisos = (char *) malloc(strlen(perm)+1);
		strcpy(i->permisos, perm);

	}
	
	inodo *buscar_inodo(int id){
	  int indice1=0;
	  int indice2=0;
	  
	  for(int i=0;i<I;i++){
	    if(indice1>=I/N && indice2!=N-1)
		indice1=0,indice2++;
	    if(inodos[(I/N)*indice2+indice1].i==id)
		return &inodos[(I/N)*indice2+indice1];
	    indice1++;
	  }
	  return NULL;
	  
	}

	void modificar_inodo(inodo *ptr,char *m, char *f){
	  if(m[0]=='F'){
	    free(ptr->last);
	    ptr->last = (char *)malloc(strlen(f)+1);
	    strcpy(ptr->last,f);
	  }
	  else if(m[0]=='T'){
	    int t = atoi(f);
	    ptr->tam+=t;
	  }
	  else{
	    int t = atoi(f);
	    ptr->dir=t;
	  }
	}
	
	void imprimirTodo(){
	  for(int i=0;i<I;i++){
	    printf("inodo %d\n",i);
	    print_inodo(&inodos[i]);
	    printf("%c",'\n');
	  }
	}
	
	void liberar_memoria(){
	  int indice1,indice2;
	  indice1=indice2=0;
	  for(int i=0;i<I;i++){
	    if(indice1>=I/N && indice2!=N-1)
	      indice1=0,indice2++;
	      liberar_inodo(&inodos[(I/N)*indice2+indice1]);
	      indice1++; 
	  }
	}

	void abroParticiones(){
	  char f[] = "Part.      ";
	  for(int i=0;i<N;i++){
	    
	    snprintf(f+5,5,"%d",i+1);
	    printf("%s\n",f);
	    files[i] = fopen(f,"w");
	    fclose(files[i]);
	    files[i] = fopen(f,"ra+");
	    
	  }
	    
	}
	
	void cierroParticiones(){
	  for(int i=0;i<N;i++)
	    fclose(files[i]);
	}

#endif
