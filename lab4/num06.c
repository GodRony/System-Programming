#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // dir1 디렉토리 생성
    if (mkdir("dir1", 0755) == -1) {
        perror("mkdir dir1");
        exit(EXIT_FAILURE);
    }

    // dir2 디렉토리 생성
    if (mkdir("dir2", 0755) == -1) {
        perror("mkdir dir2");
        exit(EXIT_FAILURE);
    }

    printf("디렉토리 dir1과 dir2가 생성되었습니다.\n");

    // dir1 삭제
    if (rmdir("dir1") == -1) {
        perror("rmdir dir1");
        exit(EXIT_FAILURE);
    }

    printf("디렉토리 dir1이 삭제되었습니다.\n");

    // dir2 이름 변경
    if (rename("dir2", "hanbit") == -1) {
        perror("rename dir2 to hanbit");
        exit(EXIT_FAILURE);
    }

    printf("디렉토리 dir2가 hanbit으로 이름이 변경되었습니다.\n");

    return 0;
}

