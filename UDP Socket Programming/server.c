#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int serverSocket;
    char str[100], temp;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&server, sizeof(server));

    printf("UDP Server waiting...\n");

    recvfrom(serverSocket, str, sizeof(str), 0,
             (struct sockaddr*)&client, &len);

    printf("Received: %s\n", str);

    // Reverse string
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
   sendto(serverSocket, str, strlen(str) + 1, 0,
           (struct sockaddr*)&client, len);

    close(serverSocket);
     return 0;
}
