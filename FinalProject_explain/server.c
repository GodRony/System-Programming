#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10

#define BUFFSIZE 200
int g_clnt_socks[CLNT_MAX];
int g_clnt_count =0;

pthread_mutex_t g_mutex;



void send_all_clnt(char * msg,int my_sock){
// 특정 클라이언트를 제외한 모든 클라이언트에게 메세지를 보내는 역할

        pthread_mutex_lock(&g_mutex);
        // 다른 스레드가 동시에 g_clnt_socks 배열을 수정하지 못하도록
        // 뮤텍스 잠금을 걸어둠.

        for(int i = 0 ; i <g_clnt_count ; i++){

                if(g_clnt_socks[i] != my_sock){
                // 메세지를 보낸 클라이언트를 제외한 나머지 클라이언트에게만 메세지 전송
                        printf("send msg : %s",msg);

                        write(g_clnt_socks[i],msg,strlen(msg)+1);
                //각 클라이언트 소켓에 메세지를 씀 strlen(msg) + 1: 문자열 끝에 \0까지 포함)
                }

        }
        pthread_mutex_unlock(&g_mutex);
}

void * clnt_connection(void * arg){
// 각 클라이언트와 통신을 처리, 스레드에서 실행할 것.
// 클라이언트가 보낸 메세지를 다른 클라이언트에게 전달하고
// 연결이 끊기면 클라이언트를 목록에서 제거

        int clnt_sock = (int)arg; //arg는 pthread_create로 전달 받은 클라이언트 소켓
        int str_len=0;
        char msg[BUFFSIZE];
        int i;


        while(1){
        //메세지 수신 루프 str_len이 -1이면 클라이언트 연결이 끊어진것으로 간주
                str_len = read(clnt_sock,msg,sizeof(msg));

                if(str_len == -1){
                        printf("clnt[%d] close\n",clnt_sock);
                        break;
                }

                send_all_clnt(msg,clnt_sock);
                printf("%s\n",msg);

        }



        pthread_mutex_lock(&g_mutex);


        for(i=0; i<g_clnt_count; i++){

                if(clnt_sock == g_clnt_socks[i]){

                        for(;i<g_clnt_count-1;i++)
                                g_clnt_socks[i]=g_clnt_socks[i+1];
                        break;

                }// 클라이언트와 연결이 끊어지면.. 리스트가 아닌 배열로 만들었으므로
                 // 해당 클라이언트를 지우고 g_clnt_socks를 앞당김
        }

        pthread_mutex_lock(&g_mutex);
        // 뮤텍스로 보호하면서 안전하게 제거.
        close(clnt_sock);

        pthread_exit(0);
        return NULL;
}

int main(int argc, char **argv){

        int serv_sock; // 서버 소켓
        int clnt_sock; // 클라이언트 소켓
        pthread_t t_thread; // 클라이언트 처리를 위한 스레드
        struct sockaddr_in clnt_addr; // 클라이언트 주소 정보를 저장하는 구조체
        int clnt_addr_size; // 클라이언트 주소 구조체의 크기
        struct sockaddr_in serv_addr; // 서버 주소 정보를 저장하는 구조체



        pthread_mutex_init(&g_mutex,NULL); // 뮤텍스 초기화



        serv_sock = socket(PF_INET,SOCK_STREAM,0);
        // socket 함수로 소켓 생성 , PF_INENT : IPv4 주소 사용 , SOCK_STREAM : TCP 소켓 생성

        serv_addr.sin_family = AF_INET; // IPv4 주소 사용
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);// 모든 네트워크 인터페이스에서 접근 가능
        serv_addr.sin_port=htons(7989); // 포트 번호
        // 서버 주소 설정하는 부분


        if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1){
                printf("bind error\n");
        }
        // bind 함수는 생성한 소켓에 IP 주소와 포트 번호를 할당

        if(listen(serv_sock,5) == -1){
                printf("listen error");
        }
        // 클라이언트 연결 대기 : 5명까지 동시 대기 가능

        char buff[200];
        int recv_len =0;

        while(1){ // 클라이언트 연결 수락
                clnt_addr_size=sizeof(clnt_addr);
                clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
                // accept : 클라이언트와 통신할 수 있는 새 소켓 반환 clnt_sock에 클라이언트 소켓 저장
                pthread_mutex_lock(&g_mutex); // 뮤텍스 잠금 동기화
                g_clnt_socks[g_clnt_count++] = clnt_sock; // 클라이언트 소켓을 리스트에 추가
                pthread_mutex_unlock(&g_mutex); // 뮤텍스 잠금 해제
                pthread_create(&t_thread,NULL,clnt_connection,(void *)clnt_sock);
                // pthread_create : 새로운 스레드 생성
                // clnt_connectioln 함수가 실행디고 해당 클라이언트와 통신을 담당함.
        }
}
