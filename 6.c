#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
	char *dato;
	struct lista *sig;
} lista;

lista *inicio=NULL;
lista *fin=NULL;

//Mostrar lista
void mostrarLista(lista *inicio){
	printf("contenido de la lista: \n");
	lista *saltanodos=inicio;
	while(saltanodos != NULL){
		printf("%s -> ", saltanodos->dato);
		saltanodos = saltanodos->sig;
	}
	printf("null\n");
}

//Añadir a la lista
void *crearNodo (char *linea){
	lista *nuevo=NULL;
	nuevo=(lista *)malloc(sizeof(lista));
	if(nuevo==NULL){
        printf("Error asignando memoria");
         exit(0);
    }
    
    //scanf("%s",&nuevo->dato);
    nuevo->dato = linea; //Not works
    //strcpy(linea, nuevo->dato);
    nuevo->sig = NULL;
    if(inicio==NULL){ //lista vacia
        inicio = nuevo;
        fin = inicio;
    }
    else{ //lista no vacia
        fin->sig = nuevo;
        fin = fin->sig;
    }
    mostrarLista(inicio);
}

//CAPTURA ctrl+C 
//MOSTRARÁ LISTA DE INTERRUPCIONES HECHAS
void signalInt(int sig){
    //printf("\nAqui va la lista we :v\n");
    mostrarLista(inicio);

}
//CAPTURA kill -SIGTERM
void signalTerm(int sig){
    printf("BLOQUEADO SIGTERM %d\n", sig);
    crearNodo("SIGTERM");
}
//CAPTURA kill -SIGIO
void signalIo(int sig){
    printf("BLOQUEADO SIGIO %d\n", sig);
    crearNodo("SIGIO");
}
//CAPTURA kill -SIGABRT
void signalAbrt(int sig){
    printf("BLOQUEADO SIGABRT %d\n", sig);
    crearNodo("SIGABRT");
}
//CAPTURA kill -SIGTRAP
void signalTrap(int sig){
    printf("BLOQUEADO SIGTRAP %d\n", sig);
    crearNodo("SIGTRAP");
}
//CAPTURA kill -SIGHUP
void signalHup(int sig){
    printf("BLOQUEADO SIGHUP %d\n", sig);
    crearNodo("SIGHUP");
}
//CAPTURA kill -SIGQUIT
void signalQuit(int sig){
    printf("BLOQUEADO SIGTRAP %d\n", sig);
}
//CAPTURA kill -SIGILL
void signalIll(int sig){
    printf("BLOQUEADO SIGILL %d\n", sig);
    crearNodo("SIGILL");
}
//CAPTURA kill -SIGBUS
void signalBus(int sig){
    printf("BLOQUEADO SIGBUS %d\n", sig);
    crearNodo("SIGBUS");
}
//CAPTURA kill -SIGFPE
void signalFpe(int sig){
    printf("BLOQUEADO SIGFPE %d\n", sig);
}
//CAPTURA kill -SIGUSR1
void signalUsr1(int sig){
    printf("BLOQUEADO SIGUSR1 %d\n", sig);
    crearNodo("SIGUSR1");
}
//CAPTURA kill -SIGSEGV
void signalSegv(int sig){
    printf("BLOQUEADO SIGSEGV %d\n", sig);
    crearNodo("SIGSEGV");
}
//CAPTURA kill -SIGUSR2
void signalUsr2(int sig){
    printf("BLOQUEADO SIGUSR2 %d\n", sig);
    crearNodo("SIGUSR2");
}
//CAPTURA kill -SIGPIPE
void signalPipe(int sig){
    printf("BLOQUEADO SIGPIPE %d\n", sig);
    crearNodo("SIGPIPE");
}
//CAPTURA kill -SIGALRM
void signalAlrm(int sig){
    printf("BLOQUEADO SIGALRM %d\n", sig);
    crearNodo("SIGALRM");
}
//CAPTURA kill -SIGTSTP
void signalTstp(int sig){
    printf("BLOQUEADO SIGTSTP %d\n", sig);
    crearNodo("SIGTSTP");
}
//CAPTURA kill -SIGTTIN
void signalTtin(int sig){
    printf("BLOQUEADO SIGTTIN %d\n", sig);
    crearNodo("SIGTTIN");
}
//CAPTURA kill -SIGTTOU
void signalTtou(int sig){
    printf("BLOQUEADO SIGTTOU %d\n", sig);
    crearNodo("SIGTTOU");
}
//CAPTURA kill -SIGXCPU
void signalXcpu(int sig){
    printf("BLOQUEADO SIGXCPU %d\n", sig);
    crearNodo("SIGXCPU");
}
//CAPTURA kill -SIG
void signalXfsz(int sig){
    printf("BLOQUEADO SIGXFSZ %d\n", sig);
    crearNodo("SIGXFSZ");
}
//CAPTURA kill -SIGVTALRM
void signalVtalrm(int sig){
    printf("BLOQUEADO SIGVRALRM %d\n", sig);
    crearNodo("SIGVRALRM");
}
//CAPTURA kill -SIGPROF
void signalProf(int sig){
    printf("BLOQUEADO SIGPROF %d\n", sig);
    crearNodo("SIGPROF");
}
//CAPTURA kill -SIGPWR
void signalPwr(int sig){
    printf("BLOQUEADO SIGPWR %d\n", sig);
    crearNodo("SIGPWR");
}
//CAPTURA kill -SIGSYS
void signalSys(int sig){
    printf("BLOQUEADO SIGSYS %d\n", sig);
    crearNodo("SIGSYS");
}

int main (){
    signal(SIGINT, &signalInt);
    signal(SIGTERM, &signalTerm);
    signal(SIGABRT, &signalAbrt);
    signal(SIGIO, &signalIo);
    signal(SIGTRAP, &signalTrap);
    signal(SIGHUP, &signalHup);
    signal(SIGQUIT, &signalQuit);
    signal(SIGBUS, &signalBus);
    signal(SIGFPE, &signalFpe);
    signal(SIGUSR1, &signalUsr1);
    signal(SIGSEGV, &signalSegv);
    signal(SIGUSR2, &signalUsr2);
    signal(SIGPIPE, &signalPipe);
    signal(SIGALRM, &signalAlrm);
    signal(SIGTSTP, &signalTstp);
    signal(SIGTTIN, &signalTtin);
    signal(SIGTTOU, &signalTtou);
    signal(SIGXCPU, &signalXcpu);
    signal(SIGXFSZ, &signalXfsz);
    signal(SIGVTALRM, &signalVtalrm);
    signal(SIGPROF, &signalProf);
    signal(SIGPWR, &signalPwr);
    signal(SIGSYS, &signalSys);

    while(1){
        printf("Hey... Aquí\n");
        sleep(2);
    }

    return 0;
}