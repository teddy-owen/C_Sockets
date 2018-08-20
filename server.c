#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 3500



int main(int argc, char const *argv[])
{

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // // Forcefully attaching socket to the port 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    char *host = argc>1 ? argv[1]:"127.0.0.1";
    address.sin_addr.s_addr = inet_addr(host);
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1){	
	    
	    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
	                       (socklen_t*)&addrlen))<0)
	    {
	        perror("accept");
	        exit(EXIT_FAILURE);
	    }

    	char buffer[1024] = {0};
	    valread = read( new_socket , buffer, 1024);
	    printf("%s\n",buffer );

	    char resp[250] = {0};
	    printf("\n-> ");	    
	    fgets(resp,250,stdin);
	    send(new_socket , resp, strlen(resp) , 0);
    }

    return 0;
}
