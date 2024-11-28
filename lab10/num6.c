#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SIGUSR1 시그널을 처리할 핸들러 함수
void sig_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("Received SIGUSR1\n");
    }
}

int main() {
    // SIGUSR1에 대한 핸들러 설정
    if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // 자신에게 SIGUSR1 시그널 보내기
    printf("Sending SIGUSR1 to myself...\n");
    kill(getpid(), SIGUSR1);  // 자신의 프로세스에 SIGUSR1 시그널 전송

    // 시그널이 처리될 때까지 대기
    printf("Waiting for signal...\n");
    sleep(1);  // 잠시 대기하여 시그널을 처리할 시간 확보

    printf("After signal handling\n");

    return 0;
}

