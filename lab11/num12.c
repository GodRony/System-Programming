#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define FILE_SIZE 22  // "Linux System Programming" + 1 for '\0'

int main() {
    const char *filename = "a.txt";
    const char *text = "Linux System Programming";

    // 1. 파일 생성 및 열기
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 2. 파일 크기를 확장
    if (ftruncate(fd, FILE_SIZE) == -1) {
        perror("ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 3. 메모리 매핑
    void *mapped = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 4. 데이터 쓰기
    memcpy(mapped, text, FILE_SIZE);

    // 5. 메모리 동기화 (선택 사항)
    if (msync(mapped, FILE_SIZE, MS_SYNC) == -1) {
        perror("msync");
        munmap(mapped, FILE_SIZE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 6. 메모리 매핑 해제 및 파일 닫기
    if (munmap(mapped, FILE_SIZE) == -1) {
        perror("munmap");
    }
    close(fd);

    printf("Data written to the file: %s\n", text);
    return 0;
}

