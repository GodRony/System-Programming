#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *dir_name = "non_existent_directory"; // 존재하지 않는 디렉토리 이름

    // rmdir 호출
    if (rmdir(dir_name) == -1) {
        perror("rmdir error");
        exit(EXIT_FAILURE);
    }

    return 0;
}

