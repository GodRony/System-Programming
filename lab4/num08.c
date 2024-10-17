#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char originalDir[256];  // 원래 디렉토리를 저장할 배열
    char *newDir = "/tmp";  // 이동할 새로운 디렉토리 경로

    // 현재 디렉토리 기억
    if (getcwd(originalDir, sizeof(originalDir)) == NULL) {
        perror("getcwd error");
        return 1;
    }
    
    printf("현재 디렉토리: %s\n", originalDir);

    // 새로운 디렉토리로 이동
    if (chdir(newDir) != 0) {
        perror("chdir error");
        return 1;
    }

    // 새로운 디렉토리 확인
    char currentDir[256];
    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        perror("getcwd error");
        return 1;
    }
    
    printf("새로운 디렉토리: %s\n", currentDir);

    // 원래 디렉토리로 돌아가기
    if (chdir(originalDir) != 0) {
        perror("chdir error");
        return 1;
    }

    // 원래 디렉토리 확인
    if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
        perror("getcwd error");
        return 1;
    }
    
    printf("원래 디렉토리로 돌아옴: %s\n", currentDir);

    return 0;
}
 
