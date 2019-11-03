#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
	int fd[2];
	int fd2[2];
	int var = atoi(argv[1]);
	int var2 = var/2;
	int contP=1, contP2=1;

	pipe(fd);
	pipe(fd2);

	if (fork() != 0) {
		close(fd[0]);		
		write(fd[1], &var2, sizeof(var2));
		close(fd[1]);
		for(int i=var; i>var2;i--){
			contP = contP * i;
			printf("La parte mayor del factorial es: %d\n", contP);
		}
		close(fd2[0]);		
		write(fd2[1], &contP, sizeof(contP));
		close(fd2[1]);
		
	} else {
		close(fd[1]);
		read(fd[0], &var2, sizeof(var2));
		printf("Child(%d) received childID: %d\n", getpid(), var2);
		for(int i=1; i<=var2;i++){
			contP2 = contP2 * i;
			printf("La parte menor del factorial es: %d\n", contP2);
		}
		close(fd[0]);
		
		close(fd2[1]);
		read(fd2[0], &contP, sizeof(contP));
		
		printf("El factorial de %d es: %d\n", var,contP2*contP);		

		close(fd2[0]);
	}
	return 0;
}
