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
	server_t.sin_port = htons(PORT);
	server_t.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("sercer\n");
	if(bind(sockfd,(struct sockaddr*)&server_t,sizeof(server_t)) == -1){
		perror("bind error");
		exit(-1);
	}
	addrlen = sizeof(client_t);
	while(1){
		if((num=recvfrom(sockfd, memory, SIZE,0,(struct sockaddr*)&client_t,&addrlen)) < 0){
			perror("recvfrom error");
			exit(0);
		}
		memory[num] = '\0';
		printf("get a msg(%s) form client_t ",memory);
		char* msg = "welcome to server_t";
		sendto(sockfd,msg,strlen(msg),0,(struct sockaddr*)&client_t, addrlen);
		if(strcmp(memory,"bye")){
			break;
		}
	}
	close(sockfd);
	return NULL;
}
		

		
int main(){
	pthread_t server;
	int sockfd;
	char *IP = "192.168.122.1";
	struct hostent * he;
	int num = 0;
	struct sockaddr_in server_t,peer_t;	
	pthread_create(&server,NULL,service,NULL);
	if((he=gethostbyname(IP)) == NULL){
		perror("gethostbyname error");
		exit(-1);
	}
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) == -1){
		perror("socke");
		exit(-1);
	}
	bzero(&server_t,sizeof(server_t));
	server_t.sin_family = AF_INET;
	server_t.sin_port = htons(PORT);
	server_t.sin_addr = *((struct in_addr*)he->h_addr);
	socklen_t  addrlen;
	char  msg[] = "hi i am client";
	sendto(sockfd,msg,strlen(msg),0,(struct sockaddr *)&server_t,sizeof(server_t));
	addrlen = sizeof(server_t);
	while(1){
		if((num = recvfrom(sockfd,cache,SIZE,0,(struct sockaddr*)&peer_t,&addrlen) == -1)){
			perror("recvfrom error");
			exit(-1);
		}
		if(addrlen != sizeof(server) || memcmp((const void*)&server_t, (const void *)&peer_t,addrlen) != 0){
			printf("Receive message from ohterserver\n");
			continue;
		}
		cache[num] = '\0';
		printf("server msg %s\n",cache);
		scanf("%s",msg);
		if(!strcmp(msg,"bye")){
			break;
		}
	}
	close(sockfd);
	printf("I am client_t\n");
}
