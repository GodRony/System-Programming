#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) < 0) {
        perror("stat");
        return 1;
    }

    // 파일명
    printf("파일명: %s\n", argv[1]);

    // inode 번호
    printf("inode 번호: %lu\n", (unsigned long)fileStat.st_ino);

    // 파일 종류
    printf("파일 종류: ");
    if (S_ISREG(fileStat.st_mode)) {
        printf("일반 파일\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("디렉토리\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("심볼릭 링크\n");
    } else {
        printf("기타\n");
    }

    // 접근 권한
    printf("접근 권한: %o\n", fileStat.st_mode & 0777);

    // UID
    printf("UID: %u\n", fileStat.st_uid);

    return 0;
}
