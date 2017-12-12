#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

void client(int,char*,int);

int main()
{
    char ip[] = "127.0.0.1";
    client(6666,ip, sizeof(ip));
}

void client(int port,char* ip,int len) {
    int client_fd;
    struct sockaddr_in server_addr;
    int er;
    char buf[128];
    client_fd = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    er = connect(client_fd,(struct sockaddr *)&server_addr, sizeof(server_addr));
    if (er<0)
    {
        perror("connect:\n");
    }
    write(client_fd,"hello",4);
    read(client_fd,buf,128);
    write(1,buf,128);

    close(client_fd);
}