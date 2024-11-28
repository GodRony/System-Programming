#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void sig_handler(int signo){
	psignal(signo,"Received Signal");
}

int main(){
	signal(SIGALRM,sig_handler);

	alarm(2);
	printf("Wait...\n");
	sleep(3);
	printf("3초 기다리구 프린트해보겟기\n");
	sleep(2);
	printf("또 2초 기다리구 프린트해보겟기\n");
}
