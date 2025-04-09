#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

struct myin_add
{
	uint32_t s_addr;
};

struct mysockaddr_in
{
	unsigned short sin_family;
	struct myin_add sin_addr;
	uint16_t sin_port;   
};

int main(int argc, char** argv)
{
	struct mysockaddr_in myaddr;
	const char* serv_ip = "127.0.0.1";
	const char* serv_port = "8090";

	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = inet_addr(serv_ip);
	myaddr.sin_port = htons(atoi(serv_port));
	
	printf("sin_family : %d\n",myaddr.sin_family);
	printf("sin_addr : %#x\n",myaddr.sin_addr);	//16진수
	printf("sin_port : %#x\n", myaddr.sin_port);
	return 0;
}
