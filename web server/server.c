#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "HTTP/1.1 200 OK\nContenttype: text/html\ncontent-length: 46\n\n<html><body><h1>MY FIRST SERVERSIDE APP IN C</h1></body></html>";

    //creating a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0 ){
        perror("Socket collapsed");
        exit(EXIT_FAILURE);

    }

    // configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    // binding socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE);

    }

    // listen for incoming request
    if (listen(server_fd, 3) < 0){
        perror("Listened failed");
        exit(EXIT_FAILURE)

    }

    printf("server is running on http://127.0.0.1:%d\n",PORT);

    while(1){
        //accept incoming request
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if(new_socket< 0){
            perror("Accept failed");
            exit(EXIT_FAILURE);

        }
        read(new_socket, buffer, BUFFER_SIZE);
        printf("Received request:\n%s\n", buffer);

        // send respose
        send (new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;


}