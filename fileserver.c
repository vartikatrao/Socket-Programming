//server
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5576
int main(int argc,char **argv)
{
int i,j;
ssize_t n;
char s[80],str[80];
struct sockaddr_in servaddr,cliaddr;
int listenfd,connfd,clilen;
listenfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);
bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
listen(listenfd,1);
clilen=sizeof(cliaddr);
connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
printf("\nclient connected\n");
int counter = 0;
while (1) {
if (recv(connfd, str, 80, 0) <= 0) {
memset(str, 0, 80);
break;
}
str[strlen(str)] = '\0';
printf("\n%s\n", str);
counter += strlen(str);
char str1[20];
sprintf(str1, "%d", counter);
send(connfd, str1, strlen(str1), 0);
memset(str, 0, 80);
}
close(listenfd);
return 0;
}