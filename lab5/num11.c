#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    // 현재 디렉터리를 열기
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // 디렉터리 항목을 하나씩 읽기
    while ((entry = readdir(dir)) != NULL) {
        // '.' 과 '..' 제외
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // 디렉터리 여부 확인 (d_type이 DT_DIR인 경우)
        if (entry->d_type == DT_DIR) {
            printf("%s\n", entry->d_name);
        }
    }

    // 디렉터리 닫기
    closedir(dir);

    return 0;
}

