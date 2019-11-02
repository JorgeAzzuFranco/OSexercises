
#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#define N  4

pthread_t tids[N];
int n = N;
int gCont=0;

int step = 1;

typedef struct hilo{
	pthread_t* tid;
    int index;
} hilo;


void handle_sighup(int signum){
		//holi
}

void *threads(void *vargp) {
    while(1){
		pause();
		sleep(1);
        //fflush(stdout);
		printf("tid: %ld \n",pthread_self());
		kill(getpid(),4);
	}
} 

int main(){
   
    signal(SIGINT, handle_sighup);
    
    
    for(int i=0;i<n;i++){
        pthread_t tid; 
	    hilo* hilos = (hilo *)malloc(sizeof(hilo));
    	hilos->tid = &tid;
	    hilos->index = i;
        pthread_create(&tid, NULL, threads, (void *)hilos );
        //pthread_join(tid,NULL);
        tids[i]=tid;
    }

    while(1){
    	pthread_kill(tids[gCont], 4);
    	pause();
    	gCont = gCont + step;
    	if(gCont == N){
    		gCont =0;
    	}
    	if(gCont < 0){
    		gCont =N-1;
    	}
    }

 	pthread_exit(NULL); 
    return 0;
}

