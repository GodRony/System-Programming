#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int status;
	pid_t pid;

	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}	

	if( pid == 0){
		printf("Child process");
		sleep(3);
		exit(3);
	}

	printf("--> Parent process\n");

	while(waitpid(pid,&status,WNOHANG) == 0){
		printf("Parent still wait...\n");
		sleep(1);
	}
	printf("Child Exit status : %d\n",status >> 7);
}
