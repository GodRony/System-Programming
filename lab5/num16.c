#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target-file> <link-name>\n", argv[0]);
        return 1;
    }

    const char *target_file = argv[1];
    const char *link_name = argv[2];

    // 심볼릭 링크 생성
    if (symlink(target_file, link_name) == -1) {
        perror("symlink");
        return 1;
    }

    // 생성된 심볼릭 링크가 가리키는 경로 출력
    char link_target[BUFFER_SIZE];
    ssize_t len = readlink(link_name, link_target, sizeof(link_target) - 1);
    if (len == -1) {
        perror("readlink");
        return 1;
    }
    link_target[len] = '\0';  // Null terminate the string
    printf("Symbolic link '%s' points to '%s'\n", link_name, link_target);

    // 심볼릭 링크 파일의 내용 출력
    FILE *file = fopen(link_name, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    printf("Contents of '%s':\n", link_name);
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}

