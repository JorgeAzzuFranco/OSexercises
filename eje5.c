
#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct hiloStruct{
	pthread_t* tid;
} hiloStruct;

int direccion = 1;

void handler_signal(int sig){
	if (sig ==  18){
		direccion *= -1;
	}else if(sig == 4){
		//solo es para omitir la instruccion ilegal
		return;
	}else if(sig == 15){
		exit(0);
	}
}

void *threads(void *vargp) {
    while(1){
		pause();
		printf("TID: %ld \n",pthread_self());
		sleep(1);
		kill(getpid(),4);
	}
} 

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	pthread_t tids[n];
	int c=0;
    signal(SIGTSTP, handler_signal);
    signal(SIGILL, handler_signal);
    signal(SIGTERM, handler_signal);
    
    for(int i=0;i<n;i++){
		hiloStruct* hilos = (hiloStruct *)malloc(sizeof(hiloStruct));
        pthread_t tid; 
    	hilos->tid = &tid;

        pthread_create(&tid, NULL, threads, (void *)hilos );
        //pthread_join(tid,NULL);
        tids[i]=tid;
    }

    while(1){
    	pthread_kill(tids[c], 4);
    	pause();
		sleep(1);
    	c = c + direccion;
    	if(c == n){
    		c =0;
    	}else if(c < 0){
    		c =n-1;
    	}
    }

 	pthread_exit(NULL); 
    return 0;
}

