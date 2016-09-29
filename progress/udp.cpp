#include<stdio.h>
#include<pthread.h>
#include<sys/socket.h>
//#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>

#define PORT 1234
#define SIZE 100
char memory[SIZE];
char cache[SIZE];
void *service(void *p){
	int sockfd;
	struct sockaddr_in server_t;
	struct sockaddr_in client_t;
	socklen_t addrlen;
	int num = 0;
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1){
		perror("create socket error");
		exit(1);
	}
	bzero(&server_t,sizeof(server_t));
	server_t.sin_family = AF_INET;
	int port = 0;
	printf("cin port local\n");
	scanf("%d",&port);
	server_t.sin_port = htonl(port);
	server_t.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr*)&server_t,sizeof(server_t)) == -1){
		perror("bind error");
//		exit(-1);
	}
	addrlen = sizeof(client_t);
	while(1){
	printf("sercer\n");
		if((num=recvfrom(sockfd, memory, SIZE,0,(struct sockaddr*)&client_t,&addrlen)) < 0){
			perror("recvfrom error");
//			exit(-1);
		}
		memory[num] = '\0';
		printf("get a msg(%s) form client_t ",memory);
	}
	printf("return\n");
	close(sockfd);
	return NULL;
}
		

		
int main(){
	pthread_t server;
	int sockfd;
	char *IP = "127.0.0.1";
	struct sockaddr_in server_t;	
	pthread_create(&server,NULL,service,NULL);
	//if((he=gethostbyname(IP)) == NULL){
	//	perror("gethostbyname error");
	//	exit(-1);
//	}
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) == -1){
		perror("socke");
		exit(-1);
	}
	bzero(&server_t,sizeof(server_t));
	server_t.sin_family = AF_INET;
	int port ;
	server_t.sin_port = htonl(6666);
	//server_t.sin_addr = *((struct in_addr*)he->h_addr);
	//server_t.sin_addr.s_addr = inet_addr(IP);
	server_t.sin_addr.s_addr = htonl(2130706433);
	socklen_t  addrlen;
	char  msg[] = "hi i am client";
	printf("send ok?\n");
	ssize_t num = sendto(sockfd,msg,strlen(msg),0,(struct sockaddr *)&server_t,sizeof(server_t));
	printf("%ld\n",num);
	pthread_join(server,NULL);
	printf("clsoe\n");
	close(sockfd);
}
