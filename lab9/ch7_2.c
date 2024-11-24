#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    pid_t pid;

    switch (pid = fork()) {
        // fork가 실패했을 때
        case -1:
            perror("fork");
            exit(1); // exit 이후 break는 필요 없음
        // 자식 프로세스
        case 0:
            printf("Child Process - My PID: %d, My Parent's PID: %d\n",
                   (int)getpid(), (int)getppid());
            break;
        // 부모 프로세스
        default:
            printf("Parent Process - My PID: %d, My Parent's PID: %d, My Child's PID: %d\n",
                   (int)getpid(), (int)getppid(), (int)pid);
            break;
    }
    printf("End of fork\n");
    return 0;
}
			


