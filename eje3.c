#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SZ 256

void crearHijo(){

    /*Dependiendo del texto que se ingrese así hay que evaluar y manejar la cadena para los parametros y para mandar a llamar el execve*/
    pid_t pid = vfork();
    if (pid == 0)
    {    
            char *arg[]={
            "/usr/bin/ncal",
            NULL
            };

            char *amb[]={
            "HOME=/home/uca",
            "DISPLAY=:0.0",
            NULL
            };
        execve(arg[0],arg,amb);
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
        crearHijo();
        wait(NULL);
        printf("%s\n",comando);
        free (comando);
    }
      return 0;
}