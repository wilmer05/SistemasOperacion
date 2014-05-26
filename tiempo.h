#include <sys/time.h>


int t_total1,t_total2,t_proc,t_proc_2;
int total_proc1,total_proc2;
int proc_solo1,proc_solo2;
int tiempo_creac1,tiempo_creac2;
/***************************************************************************
 * Definicion de la funcion para tomar los tiempos en Solaris o Linux.
 * Retorna el tiempo en microsegundos
 ***************************************************************************/
int Tomar_Tiempo()
{
  struct timeval t;     /* usado para tomar los tiempos */
  int dt;
  gettimeofday ( &t, (struct timezone*)0 );
  dt = (t.tv_sec)*1000000 + t.tv_usec;
  return dt;
}   