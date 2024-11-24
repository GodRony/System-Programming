#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // fork()를 호출하여 자식 프로세스 생성
    if ((pid = fork()) < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // 자식 프로세스
        char cwd[1024];

        // 현재 디렉토리의 절대 경로를 얻기
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Child Process: Current directory (absolute path): %s\n", cwd);
        } else {
            perror("getcwd failed");
            exit(1);
        }
    } else {  // 부모 프로세스
        // 현재 디렉토리의 내용을 출력
        printf("Parent Process: Listing current directory contents:\n");
        if (system("ls -l") == -1) {
            perror("system failed");
            exit(1);
        }
    }

    return 0;
}

