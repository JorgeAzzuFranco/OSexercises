#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SZ 1000



void crearHijo(char cadena[]){
    //creo un respaldo de mi cadena
    char aux[strlen (cadena)];
    strcpy(aux,cadena);

    char delim[] = " ";
    int counter=1;

    //Separo la cadena con mi limitador
    char *ptr = strtok(cadena, delim);

    /*cuento de cuantas posiciones necesito mi arreglo*/
  while(ptr != NULL)
	{
        counter=counter+1;
		ptr = strtok(NULL, delim);
	}

    char *arg[counter];
    char *ptr2 = strtok(aux,delim);
    counter = 0;

    while(ptr2 != NULL)
	{
        arg[counter] = ptr2;
        counter = counter+1;
		ptr2 = strtok(NULL, delim);
	}
    arg[counter] = NULL;

    char home[50] = "HOME=";
    char display[12] = "DISPLAY=";

    strcat(home,getenv("OLDPWD"));
    strcat(display,getenv("DISPLAY"));

    pid_t pid = vfork();
    if (pid == 0)
    {
            char *amb[]={
            home,
            display,
            NULL
            };
           
        if(execve(arg[0],arg,amb) == -1){
            printf("No se encontro el comando debe ser del tipo /usr/bin/<comando> -param1 -param2 ...\n");
        }
    }
}


int main(){
while(1){
        printf("Ingrese comando\n");


        char *comando = malloc(MAX_NAME_SZ);
    if (comando == NULL) {
        printf("No memory\n");
        return 1;
    }
    fgets(comando, MAX_NAME_SZ, stdin);
    if ((strlen(comando) > 0) && (comando[strlen (comando) - 1] == '\n'))
        comando[strlen (comando) - 1] = '\0';
    
    /*-------------------------------*/
        crearHijo(comando);
        //wait(NULL);
        free (comando);
    }
      return 0;
}