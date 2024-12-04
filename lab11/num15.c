#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t sigusr1_received = 0; // 시그널 플래그

// 시그널 핸들러 함수
void handle_sigusr1(int sig) {
    sigusr1_received = 1; // 시그널 수신 플래그 설정
}

int main(int argc, char *argv[]) {
    int fd;
    pid_t pid;
    caddr_t addr;
    struct stat statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if (stat(argv[1], &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    addr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd);

    // 부모 프로세스가 SIGUSR1을 처리하도록 핸들러 등록
    struct sigaction sa;
    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    switch (pid = fork()) {
        case -1:
            // fork 실패
            perror("fork");
            exit(1);

        case 0:
            // 자식 프로세스
            printf("1. Child Process: addr=%s\n", addr);
            sleep(1);

            // 메시지 작성 후 부모에게 시그널 전송
            strcpy(addr, "Message from child");
            printf("2. Child Process: addr=%s\n", addr);
            kill(getppid(), SIGUSR1); // 부모 프로세스에 SIGUSR1 시그널 전송

            sleep(2);
            break;

        default:
            // 부모 프로세스
            printf("1. Parent Process: addr=%s\n", addr);
            printf("Waiting for SIGUSR1 from child...\n");

            // 시그널을 기다림
            while (!sigusr1_received) {
                pause(); // 시그널 대기
            }

            printf("2. Parent Process received SIGUSR1: addr=%s\n", addr);

            // 부모가 데이터 수정
            addr[0] = 'P';
            printf("3. Parent Process modified addr: addr=%s\n", addr);
            break;
    }

    return 0;
}

