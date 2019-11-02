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

typedef struct myThread{
	pthread_t* tid;
	int index;
} hilo;


void handle_sighup(int sig){
   
		step = step * -1;

}

void *myThreadFun(void *vargp) 
{ 
    // Store the value argument passed to this thread 
    while(1){
		pause();
		sleep(2);	
		printf("tid: %ld \n",pthread_self());
		kill(getpid(),4);
	}
} 

int main(){
    
    signal(SIGINT, handle_sighup);
    
    
    for(int i=0;i<n;i++){
        pthread_t tid; 
		hilo* myThread = (hilo *)malloc(sizeof(hilo));
    	myThread->tid = &tid;
    	myThread->index = i;
        pthread_create(&tid, NULL, myThreadFun, (void *)myThread ); 
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

