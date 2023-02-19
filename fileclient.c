//client
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define SERV_PORT 5576
int main()
{
int i,j;
ssize_t n;
char filename[80],recvline[80];
struct sockaddr_in servaddr;
int sockfd;
sockfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
printf("enter the file name");
scanf("%s",filename);
char *line = NULL;
size_t len = 0;
ssize_t read;
FILE *fp = fopen(filename, "r");
if (fp == NULL) {
exit(EXIT_FAILURE);
}
char buffer[80];
while (fgets(buffer, 80, fp) != NULL) {
send(sockfd, buffer, strlen(buffer), 0);
recv(sockfd, recvline, 80, 0);
}
printf("\n Number of characters: \n");
printf("%s\n", recvline);
fclose(fp);
close(sockfd);
return 0;
}