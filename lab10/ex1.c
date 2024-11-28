#include <stdio.h>
#include <unistd.h>

int main()
{
	int i,j;
	
	for(i = 2; i < 10; i++){
		for(j = 2; j < 10 ; j++){
			printf("%d X %d = %d \n",i,j,i*j); }
		sleep(1);
	}
}
