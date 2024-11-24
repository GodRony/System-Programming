#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2;

    // 첫 번째 fork() 호출 - 첫 번째 자식 프로세스 생성
    pid1 = fork();

    if (pid1 < 0) {
        // fork() 실패 처리
        perror("fork1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        // 자식 프로세스에서 두 번째 fork() 호출 - 두 번째 자식 프로세스 생성
        printf("Child 1 Process (PID: %d)\n", getpid());
        pid2 = fork();
        
        if (pid2 < 0) {
            perror("fork2 failed");
            exit(1);
        }

        if (pid2 == 0) {
            // 두 번째 자식 프로세스 (Child 2)
            printf("Child 2 Process (PID: %d), Parent PID: %d\n", getpid(), getppid());
            exit(0);
        } else {
            // 첫 번째 자식 프로세스에서 두 번째 자식의 PID 출력
            printf("Child 1 Process (PID: %d), Created Child 2 (PID: %d)\n", getpid(), pid2);
            exit(0);
        }
    } else {
        // 부모 프로세스
        printf("Parent Process (PID: %d), Created Child 1 (PID: %d)\n", getpid(), pid1);
        wait(NULL);  // 자식 프로세스들이 끝날 때까지 기다림
        wait(NULL);
    }

    return 0;
}

