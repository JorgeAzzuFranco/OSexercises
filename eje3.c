#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SZ 1000



void crearHijo(char cadena[]){

    char delim[] = " ","-";

    char *ptr = strtok(cadena, delim);

    while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}

    pid_t pid = vfork();
    if (pid == 0)
    {    
            char *arg[]={
            ptr,
            NULL
            };

            /*
            char *amb[]={
            "HOME=/home/uca",
            "DISPLAY=:0.0",
            NULL
            };*/

        printf("Desde el hijo: %s \n",ptr);

        if(execve(arg[0],arg,NULL) == -1){
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
        wait(NULL);
        free (comando);
    }
      return 0;
}