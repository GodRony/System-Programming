#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *rfp;
    char buffer[26];  // 데이터 파일의 크기만큼 버퍼 설정
    int i;

    // 파일 열기
    if ((rfp = fopen("data.txt", "r")) == NULL) {  // "data.txt" 파일이 "abcdefghijklmnopqrstubwxyz"를 포함한다고 가정
        perror("fopen");
        exit(1);
    }

    // 파일 내용 전체를 버퍼에 읽기
    fread(buffer, sizeof(char), 26, rfp);
    fclose(rfp);

    // 짝수 인덱스 위치의 문자 출력
    printf("출력 형태 : ");
    for (i = 0; i < 26; i += 2) {
        fwrite(&buffer[i], sizeof(char), 1, stdout);
    }
    printf("\n");

    return 0;
}

