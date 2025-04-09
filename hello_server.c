#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


void error_handling(char *message);

int main(int argc, char *argv[]){
	
	int serv_sock;
	int clnt_sock;
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[] = "Hello World!";

	if (argc !=2)
	{
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);		//ipv4, tcp 통신
	if(serv_sock == -1)		//파일디스크립터가 -1이면 정상적으로 생성 안된것
		error_handling("socket() error");

	memset( &serv_addr, 0, sizeof(serv_addr));		//구조체 맴버 전부 0으로 초기화
	serv_addr.sin_family = AF_INET;		//ipv4 의미
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);		//ip할당 INADDR_ANT 는 00000000임
	serv_addr.sin_port = htons(atoi(argv[1]));	//host -> network

	//bind, listen 호출
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");
	if(listen(serv_sock, 5) == -1)		//5개 통신
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);		
	//클라이언트 소캣 저장
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept() error");

	//클라이언트 소캣을 통해 전달
	write(clnt_sock, message, sizeof(message));
	close(clnt_sock);
	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
