#include<stdio.h>
#include<stdlib.h>

#ifndef estructuras
#define estructuras
	
	typedef struct{
		int tam, i ,id,dir;
		char fecha[30];
		char last[30];
		char permisos[10];

	} inodo;
	
	typedef struct{
	  int x;
	  int y;
	} par;
	
	int P,N,I; //numero de hijos concurrentes y numero de particiones, respectivamente
	inodo inodos[110];
	FILE *files[110];//particiones
	
	//Funcion que imprime un nodo con todos sus campos
	void print_inodo(inodo *i){
	  printf("%d, %d, %d, %s, %s, %s, %d\n",i->i,i->tam,i->id,\
				i->fecha,i->last,i->permisos,i->dir);
	  
	}
	
	//funcion que inicializa un nodo
	void inic_inodo(inodo *i, int tam,int ii,int id,char *fecha,char *last, int dir, char *perm){
		i->tam = tam;
		i->i = ii;
		i->id = id;
		i->dir = dir;
		strcpy(i->fecha, fecha);
		strcpy(i->last, last);
		strcpy(i->permisos, perm);

	}
	
	
	//Funcion que busca en que particion se encuentra
	//un nodo y retorna sus referencia
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

	
	//Funcion que se encarga de modificar el nodo en
	//memoria principal
	void modificar_inodo(inodo *ptr,char *m, char *f){
	  if(m[0]=='F'){
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
	
	//Imprime todos los nodos de una particion
	void imprimirParticion(int val){
	  inodo k;
	  char f[] = "Part.      ";
	  snprintf(f+5,5,"%d",val+1);
	  
	  FILE *fp;
	  fp = fopen(f,"r+");
	  fseek(fp, 0,SEEK_SET);
	  
	  for(int i=0;i<I/N;i++){
	    fread(&k,sizeof (inodo),1,fp);
	    print_inodo(&k);
	  }
	  if(val==N-1)
	    for(int i=0;i<I%N;i++){
	      fread(&k,sizeof (inodo),1,fp);
	      print_inodo(&k);
	    }
	   fclose(fp);
	  
	}
	
	
	//Imprime todas las particiones en orden, solo
	//las posiciones ocupadas en las particiones
	void imprimirTodo(){
	  for(int i=0;i<N;i++){
	    printf("Particion %d:\n\n",i+1);
	    imprimirParticion(i);
	    printf("\n\n");
	  }
	  
	}

	//Funcion engargada de abrir una particion para
	//escritura, se utiliza inicialmente
	void abroParticiones(){
	  char f[] = "Part.      ";
	  for(int i=0;i<N;i++){
	    
	    snprintf(f+5,5,"%d",i+1);
	    //printf("%s\n",f);
	    files[i] = fopen(f,"w");
	  }
	    
	}
	
	//Abre una particion para modificacion
	void abro_particiones_modif(){
	  char f[] = "Part.      ";
	  for(int i=0;i<N;i++){
	    
	    snprintf(f+5,5,"%d",i+1);
	    //printf("%s\n",f);
	    files[i] = fopen(f,"r+");
	    
	  }
	}
	
	//Cierra los descriptores de las particiones
	void cierroParticiones(){
	  for(int i=0;i<N;i++)
	    fclose(files[i]);
	}
	
	
	//Verifica si hubo una modificacion en un inodo
	int diferentes(inodo *p1, inodo *p2){
	  return (p1->tam!=p2->tam) || strcmp(p1->last,p2->last) \
			  || (p1->dir!=p2->dir);
	}
	
	//Se encarga de modificar un inodo de la particion
	//En memoria secundaria
	void modificar_particion(int part,int lugar){
	  inodo tmp;
	  fseek(files[part], sizeof(inodo)*lugar,SEEK_SET);
	  fread(&tmp,sizeof (inodo),1,files[part]);
	  inodo *ptr = buscar_inodo(tmp.i);
	  //print_inodo(ptr);
	  if(diferentes(ptr,&tmp)){
	    //arreglo el valor si son distintos
	    fseek(files[part], sizeof(inodo)*lugar,SEEK_SET);
// 	    printf("escribo\n");
	    fwrite(ptr,sizeof(inodo),1,files[part]);
	  }
	  
	}
	

#endif
