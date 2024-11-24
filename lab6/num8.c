#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory name> <file name>\n", argv[0]);
        exit(1);
    }

    const char *dir_name = argv[1];
    const char *file_name = argv[2];

    // 디렉터리 생성 (권한: 0755)
    if (mkdir(dir_name, 0755) == -1) {
        perror("Failed to create directory");
        exit(1);
    }

    // 새 경로 생성: "directory_name/file_name"
    char new_path[1024];
    snprintf(new_path, sizeof(new_path), "%s/%s", dir_name, file_name);

    // 파일 이동
    if (rename(file_name, new_path) == -1) {
        perror("Failed to move file to new directory");
        exit(1);
    }

    printf("File moved successfully to %s\n", new_path);
    return 0;
}

