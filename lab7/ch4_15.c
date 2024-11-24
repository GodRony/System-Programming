#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *rfp;
    int id, s1, s2, s3, s4, n;

    if((rfp = fopen("linux.dat","r")) == NULL){
        perror("fopen: linux.dat");
        exit(1);
    }

    printf("학번	평균\n");
    while((n = fscanf(rfp, "%d %d %d %d %d", &id, &s1, &s2, &s3, &s4)) != EOF){
        printf("%d: %.2f\n", id, (s1 + s2 + s3 + s4) / 4.0);  // 평균을 소수점 2자리까지 출력
    }

    fclose(rfp);  // 올바르게 fclose로 수정
    return 0;
}

