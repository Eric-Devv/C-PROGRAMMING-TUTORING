#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main (){
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "HTTP/1.1 200 OK \nContent-type:application/json\nContent-length: 27\n\n{\"message\":\"Hallo, API!\"}";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("API server running on http://127.0.0.1:%d\n", PORT);

    while(1){
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        read(client_fd, buffer, BUFFER_SIZE);
        printf("Request received: \n%s\n", buffer);

        send(client_fd, response, strlen(response), 0);
        close(client_fd);

    }

    return 0;
}