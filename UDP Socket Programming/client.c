#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int clientSocket;
    char str[100];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    sendto(clientSocket, str, strlen(str) + 1, 0,
           (struct sockaddr*)&server, sizeof(server));

    recvfrom(clientSocket, str, sizeof(str), 0,
             (struct sockaddr*)&server, &len);

    printf("Reversed string: %s\n", str);

    close(clientSocket);

    return 0;
}
