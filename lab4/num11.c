#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // 명령행 인자가 하나 더 필요함
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <디렉토리 이름>\n", argv[0]);
        return 1;
    }

    // 입력받은 디렉토리 이름
    char *dirName = argv[1];

    // 디렉토리 생성
    if (mkdir(dirName, 0755) != 0) {
        perror("디렉토리 생성 실패");
        return 1;
    }

    printf("디렉토리 '%s'가 생성되었습니다.\n", dirName);

    // 생성한 디렉토리로 이동
    if (chdir(dirName) != 0) {
        perror("디렉토리 이동 실패");
        return 1;
    }

    // 현재 작업 디렉토리 확인
    char currentDir[256];
    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        perror("현재 작업 디렉토리 확인 실패");
        return 1;
    }

    printf("현재 작업 디렉토리: %s\n", currentDir);

    return 0;
}

