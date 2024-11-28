#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SIGALRM 시그널을 처리할 핸들러 함수
void sig_handler(int signo) {
    if (signo == SIGALRM) {
        printf("Wake up\n");
        
        // 1초 후에 다시 알람을 설정
        alarm(1);
    }
}

int main() {
    // SIGALRM에 대한 핸들러 설정
    if (signal(SIGALRM, sig_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // SIGALRM 시그널을 1초마다 발생하도록 설정
    alarm(1);

    // SIGINT를 제외한 모든 시그널을 블로킹
    sigset_t new_set, old_set;
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);  // SIGINT는 제외
    sigprocmask(SIG_BLOCK, &new_set, &old_set);  // 새로운 시그널 집합을 블로킹

    // 무한 루프를 돌며 SIGALRM 핸들러가 실행되도록 기다림
    while (1) {
        // 이곳에서 다른 시그널을 처리하거나 필요한 작업을 추가할 수 있음
        // 예를 들어, SIGINT 시그널을 처리하려면 unblocking 후 작업할 수 있음.
        pause();  // 현재 프로세스를 대기 상태로 두고, 시그널을 기다림
    }

    return 0;
}

