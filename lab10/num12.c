#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SIGQUIT 시그널을 처리할 핸들러 함수
void sig_handler(int signo, siginfo_t *si, void *ucontext) {
    if (signo == SIGQUIT) {
        printf("Received SIGQUIT\n");

        // si_code를 출력하여 시그널 발생 원인 확인
        printf("si_code : %d\n", si->si_code);

        // si_pid와 si_uid를 출력하여 시그널을 보낸 프로세스의 정보를 확인
        printf("Signal sent by PID: %d, UID: %d\n", si->si_pid, si->si_uid);
    }
}

int main() {
    struct sigaction act;

    // SIGQUIT에 대한 sigaction 설정
    act.sa_flags = SA_SIGINFO;  // SA_SIGINFO를 설정하여 siginfo_t를 전달받을 수 있게 함
    act.sa_sigaction = sig_handler;  // sa_sigaction에 핸들러 설정

    // SIGQUIT에 대한 핸들러 등록
    if (sigaction(SIGQUIT, &act, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    // 현재 프로세스에서 SIGQUIT 시그널 보내기
    printf("Sending SIGQUIT to myself...\n");
    kill(getpid(), SIGQUIT);  // 현재 프로세스에 SIGQUIT 시그널을 보냄

    // 대기
    printf("Waiting for signal...\n");
    sleep(2);  // 시그널이 처리될 시간을 확보

    return 0;
}

