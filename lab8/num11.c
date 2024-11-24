#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;
    
    // 시작 시간 측정
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < 100000; ++i) {
        int fd = open("/dev/null", O_RDONLY);  // /dev/null 파일을 연다
        if (fd == -1) {
            perror("open failed");
            return 1;
        }
        close(fd);  // 파일을 닫는다
    }
    
    // 종료 시간 측정
    gettimeofday(&end, NULL);

    // 실행 시간 계산
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    
    if (microseconds < 0) {
        microseconds += 1000000;
        seconds--;
    }
    
    printf("Elapsed time: %ld seconds and %ld microseconds\n", seconds, microseconds);

    return 0;
}


