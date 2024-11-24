#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char ch;

    // 파일 열기
    if ((fd = open("data.txt", O_RDONLY)) == -1) {  // "data.txt" 파일이 "abcdefghijklmnopqrstubwxyz"를 포함한다고 가정
        perror("open");
        exit(1);
    }

    printf("출력 형태 : ");
    // 파일의 처음부터 2씩 건너뛰며 읽기
    for (int i = 0; lseek(fd, i, SEEK_SET) >= 0; i += 2) {
        if (read(fd, &ch, 1) == 1) {
            printf("%c", ch);
        } else {
            break;  // 파일 끝에 도달하면 종료
        }
    }

    printf("\n");

    close(fd);
    return 0;
}

