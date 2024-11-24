#include <sys/sysinfo.h>
#include <stdio.h>
#include <unistd.h> // for getpid() and getppid()

int main() {
    // 현재 프로세스의 PID와 PPID 출력
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("PID: %d\n", (int)pid);
    printf("PPID: %d\n", (int)ppid);

    // sysinfo 구조체를 사용해 시스템 정보 가져오기
    struct sysinfo info;

    if (sysinfo(&info) == -1) {
        perror("sysinfo");
        return 1;
    }

    // 메모리 정보 출력 (단위 변환 포함)
    printf("Total RAM: %ld MB\n", info.totalram / (1024 * 1024)); // Byte -> MB 변환
    printf("Free RAM: %ld MB\n", info.freeram / (1024 * 1024));   // Byte -> MB 변환

    // 부팅 후 경과 시간 계산 (초 -> 시간과 분으로 변환)
    long uptime_seconds = info.uptime;
    long hours = uptime_seconds / 3600;
    long minutes = (uptime_seconds % 3600) / 60;
    printf("Uptime: %ld hours, %ld minutes\n", hours, minutes);

    // 프로세스 개수 출력
    printf("Number of processes: %d\n", info.procs);

    // PPID가 bash의 PID와 동일한지 확인
    FILE *bash_pid_file = fopen("/proc/self/stat", "r");
    if (bash_pid_file) {
        int stat_ppid;
        fscanf(bash_pid_file, "%*d %*s %*c %d", &stat_ppid);
        fclose(bash_pid_file);

        if (stat_ppid == ppid) {
            printf("PPID matches current bash PID.\n");
        } else {
            printf("PPID does not match current bash PID.\n");
        }
    } else {
        perror("Failed to open /proc/self/stat");
    }

    return 0;
}

