#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 3500
  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
  
    char *host = argc>1 ? argv[1]:"127.0.0.1";
    
    printf("Send Messages to Server\n");

    while(1){
        char message_buffer[250]={0}; 
        printf("-> ");
        fgets(message_buffer,250,stdin);

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));
      
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
          
        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, host, &serv_addr.sin_addr)<=0) 
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }
        send(sock , message_buffer , strlen(message_buffer) , 0 );
        
        char buffer[1024] = {0};
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
    }
    
    return 0;
}