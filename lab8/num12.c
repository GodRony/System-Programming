#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;
    long sum = 0;
    
    // 시작 시간 측정
    gettimeofday(&start, NULL);

    // 1부터 100000까지 더하면서 결과값을 출력
    for (int i = 1; i <= 100000; i++) {
        sum += i;
        printf("현재 합계: %ld\n", sum);  // 현재 합계 출력
    }

    // 종료 시간 측정
    gettimeofday(&end, NULL);

    // 시간 계산
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;

    if (microseconds < 0) {
        microseconds += 1000000;
        seconds--;
    }

    printf("Elapsed time: %ld seconds and %ld microseconds\n", seconds, microseconds);

    // 시간 측정 결과 출력
    printf("실행 시간 (real time): %ld.%06ld초\n", seconds, microseconds);

    return 0;
}

