#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#define PORT 6666
#define ARRAY 10

int main()
{
    int server_fd;//服务器文件描述符
    int client_fd;//客户端文件描述符
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int err;
    int on = 1;
    /*建立流式套接字*/
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if (server_fd<0)
    {
        perror("socket：\n");
        return -1;
    }
    /*设置服务器地址*/
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*设定端口利用，避免端口冷却*/
    setsockopt(server_fd,SOL_SOCKET,SO_RANDOMPORT,&on, sizeof(on));
    /*绑定地址结构到套接字描述符*/
    err = bind(server_fd,(struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err<0)
    {
        perror("bind：\n");
        return -1;
    }
    /*设置侦听*/
    err = listen(server_fd,ARRAY);
    if (err<0)
    {
        perror("listen：\n");
        return -1;
    }
    /*接受一个网络请求*/
    socklen_t len = sizeof(client_addr);
    client_fd = accept(server_fd,(struct sockaddr *)&client_addr, &len);
    if (client_fd<0)
    {
        perror("accept:\n");
        return -1;
    }
    printf("有一个客户端进行了连接\n");
    /*接收和发送数据*/
    char buffer[128]={0};
    char buf[]="I am client:\n";
    while(1)
    {
        /*数组初始化函数*/
        write(client_fd,buf, sizeof(buf));
        read(client_fd,buffer,128);
        printf("server:");
        printf("%s\n",buffer);
        if (buffer[0] == '0')
        {
            break;
        }
    }
    /*int x = strcmp("quit",buffer);
    printf("x:%d\n",x);
    if (!strcmp("quit",buffer))
    {
        break;
    }
     */
    close(server_fd);
    close(client_fd);
    return 0;
}