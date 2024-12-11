#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>



#define BUFFSIZE 100
#define NAMESIZE 20

int StoHEX(char fi, char sc);
void error_handling(char *msg);
void * send_message(void * arg);
void * recv_message(void * arg);


char message[BUFFSIZE];

void * rcv(void * arg){
// 메세지를 수신하는 스레드 함수, 클라에서 메세지를 받는 부분 담당.
        printf("rcv thread created\n");
        int sock = (int)arg; // arg는 클라 소켓
        char buff[500]; // 수신할 임시 버퍼 서버로부터 읽어온 메세지를 저장
        int len;

        while(1){

                len = read(sock,buff,sizeof(buff)); // 서버로부터 메세지 읽어온다.
                if(len == -1){
                        printf("sock close\n");
                        break;
                }
                printf("%s",buff);
        }
        pthread_exit(0);
        return 0;
}

int main(int argc,char **argv){

        int sock;
        struct sockaddr_in serv_addr;
        pthread_t rcv_thread;
        void* thread_result;


        char id[100];

        printf("argc : %d\n",argc);

        if(argc < 2){
                printf("you have to enter ID\n");
                return 0;
        }

        strcpy(id,argv[1]);
        // 입력한 id를 가져와 id 배열에 복사 ID는 사용자가 채팅에 보낼때 사용할 사용자 이름

        printf("id : %s\n",id);
        sock=socket(PF_INET, SOCK_STREAM, 0);
        // PF_INET : IPv4 프로토콜 이용, SOCK_STREAM : TCP 소켓 사용, 0 : 기본 프로토콜 사용
        // 성공시 소켓 파일 디스크립터 반환 실패하면 -1
        if(sock==-1){
                printf("socket error");
        }else{
                printf("socket ok\n");
        }

        memset(&serv_addr, 0,sizeof(serv_addr)); // serv_addr 구조체를 0으로 초기화함
                                                 // 서버의 주소를 설정하는데 사용할거임!!

        serv_addr.sin_family=AF_INET; // AF_INET : IPv4 주소를 사용
        serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        //서버의 IP주소 설정 121.0.0.1은 로컬호스트 주소로 서버와 클라가 같은 머신에서 실행될때 사용
        serv_addr.sin_port=htons(7989); // 서버가 대기할 포트번호임. 서버꺼랑 똑같이 맞춰줘야함



        if(connect(sock, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1){
                // connect : 클라가 서버에 연결을 시도하는 함수
                // 서버주소를 serv_addr로 설정하고 이 주소로 연결 시도.
                printf("connect error\n");
        }else{
                printf("connection success\n");
        }


        pthread_create(&rcv_thread,NULL,rcv,(void *)sock);
        // 새로운 스레드를 생성하는 함수
        // rcv_thread : 생성된 스레드의 ID를 저장할 변수, rcv는 스레드가 실행할 함수
        // rcv는 서버로부터 수신한 메세지를 처리하는 함수임!
        // (void *) sock는 새로운 스레드 함수로 전달함. 이 값을 통해 소켓을 사용해 데이터 송수신 >가능
        char chat[100];
        char msg[1000];
        printf("while before\n");

        while(1){
        // 사용자 입력받기 및 서버로 메세지 보내기.
                printf("채팅 입력 : ");
                gets(chat); // 입력한 내용을 chat 배열에 저장
                sprintf(msg,"[%s] : %s\n",id,chat); // 메세지를 포맷팅해서 msg 배열에 저장
                printf("send : %s",msg);
                write(sock,msg,strlen(msg)+1); // write : 서버로 메세리를 전송함
                sleep(1);

        }
        printf("while end\n");
        close(sock);
        return 0;



}//end main


