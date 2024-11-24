#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    pid_t pid;

    // fork()를 호출하여 자식 프로세스 생성
    if ((pid = fork()) < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // 자식 프로세스
        char cwd[1024];

        // 현재 디렉토리의 절대 경로를 얻기
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Child Process: Current directory (absolute path): %s\n", cwd);
        } else {
            perror("getcwd failed");
            exit(1);
        }
    } else {  // 부모 프로세스
        struct dirent *entry;
        struct stat fileStat;
        DIR *dp;

        // 현재 디렉토리 열기
        dp = opendir(".");
        if (dp == NULL) {
            perror("opendir failed");
            exit(1);
        }

        printf("Parent Process: Listing current directory contents with inode numbers:\n");

        // 디렉토리 내의 항목들 읽기
        while ((entry = readdir(dp)) != NULL) {
            // 각 파일의 inode 번호와 파일 이름 출력
            if (stat(entry->d_name, &fileStat) == -1) {
                perror("stat failed");
                continue;
            }
            printf("Inode: %lu, Filename: %s\n", (unsigned long)fileStat.st_ino, entry->d_name);
        }

        closedir(dp);  // 디렉토리 닫기
    }

    return 0;
}

