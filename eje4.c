// C program for passing value from 
// child process to parent process 
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int iloc = 0;
int direction = 1;
int banderita = 0;
void handler_sigtstp(int sig){
	if (sig ==  18){
		if (direction == 1){
			direction = 0; 
		}
		else{
			direction = 1; 
		}
	}else if (sig == 15){
		exit(0);
	}
}
void print(int arreglo[], int tamanio, int sHorario){ 
	while (1) { 
		if (direction == 1) { 
			banderita = 0; 
			sleep(1); 
		if (iloc < 0 ){ 
			iloc = tamanio;
			}
		if (iloc > tamanio ){ 
			iloc = 0;
		}
		printf("Soy el nodo con pid: %d\n", arreglo[iloc]);
		iloc++;
		if (iloc == tamanio) { 
			iloc = 0; } 	
		}else{ 
			if (banderita == 1){
				iloc--; 
				if (iloc < 0 ){ 
					iloc = tamanio;
				}
				if (iloc > tamanio ){ 
					iloc = 0;
				}
				sleep(1);
				if(iloc <= tamanio && iloc >=0){
					printf("Soy el nodo con pid: %d\n", arreglo[iloc]);
				}
				if (iloc == 0){
					iloc = tamanio;
				}
			} else { 
				iloc--;
				banderita = 1; 
			} 
		} 
	}
}
int main(int argc, char *argv[]){	
	int father = getpid();
	int fd[2], i = 0;
	pipe(fd); 
	int pidc; 
	int n = atoi(argv[1]); 
	int pids[n]; 
	int hijos[n]; 
	for (int i = 0; i < n; i++) { 
		pid_t pid = fork(); 
		if (pid > 0) { 
		// padre
			close(0);
			close(fd[1]);
			dup(fd[0]);
			read(fd[0], &pidc, sizeof(pidc));
			pids[i] = pidc;
			wait(NULL); 
		}
		else if (pid == 0) { 
			pidc = getpid(); close(fd[0]);
			close(1);
			dup(fd[1]);
			write(1, &pidc, sizeof(pidc)); 
		}else{
			wait(NULL);
		}
	}
	if (father == getpid()) { 
		while (1) { 
			signal(SIGTSTP, handler_sigtstp); 
			if (direction == 0){
				print(pids, sizeof(pids) / sizeof(pids[0]), direction);
			}else{
				print(pids, sizeof(pids) / sizeof(pids[0]), direction); 
			} 
		} 
	}
}
