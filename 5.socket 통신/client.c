#define BUFF_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

int client_socket; 
struct sockaddr_in server_addr;
char buff_rcv[BUFF_SIZE+5];
char buff_send[BUFF_SIZE+5];

void *writ()
{
	while(1)
	{
		if(getchar() == '\n')
		{
			printf("client : ");
			fgets(buff_send, sizeof(buff_send), stdin);
			write(client_socket, buff_send, strlen(buff_send)+1);
		}
	}
}

int main(int argc, char **argv)
{
	pthread_t p_thread[1];      // 쓰레드 식별자
    int thread_id;
    int status;
	
	thread_id = pthread_create(&p_thread[0], NULL, writ, NULL);
    if(thread_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	client_socket = socket(PF_INET, SOCK_STREAM, 0); //socket()을 이용하여 소켓 생성
	if(-1 == client_socket)
	{
		printf("socket 생성 실패\n");
		exit( 1);
	}
	
	//connet()를 이용하여 서버 연결 또는 접속 시도
	memset(&server_addr, 0, sizeof(server_addr)); //메모리의 크기를 변경할 포인터, 초기화 값, 초기화 길이
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);
	server_addr.sin_addr.s_addr= inet_addr("220.69.240.238"); //자신의 서버주소
	
	if(-1 == connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr) ) )
	{
		printf("접속 실패\n");
		exit(1);
	}
		
	while(1)
	{
		//접속에 성공하면 데이터 전송
		read(client_socket,buff_rcv,BUFF_SIZE);
		printf("server : %s",buff_rcv);
	}
	
	return 0;
}
