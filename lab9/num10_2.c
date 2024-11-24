#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2;

    // 첫 번째 fork() 호출 - 자식 프로세스 생성
    pid1 = fork();

    if (pid1 < 0) {
        // fork() 실패 처리
        perror("fork1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        // 자식 프로세스에서 두 번째 fork() 호출 - 손자 프로세스 생성
        
        pid2 = fork();
        
        if (pid2 < 0) {
            perror("fork2 failed");
            exit(1);
        }

        if (pid2 == 0) {
            // 손자 프로세스
	      printf("2nd: my PID = %d, parent PID = %d, child PID = ",
			      getpid(), getppid());
            printf("%d\n", getpid());
            exit(0);
        } else {
		 printf("1st: my PID = %d, parent PID = %d, child PID = ", 
				 getpid(), getppid());
            printf("%d\n", pid2);
            exit(0);
        }
    } else {
        // 부모 프로세스
        printf("0th: my PID = %d, parent PID = %d, child PID = %d\n", getpid(), getppid(), pid1);
        
        // 자식 프로세스가 끝날 때까지 기다림
        wait(NULL);
    }

    return 0;
}

