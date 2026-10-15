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

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket, (struct sockaddr *)&server,
             sizeof(server)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        return 1;
    }

    printf("UDP Server waiting...\n");

    // Receive string from client
    ssize_t n = recvfrom(serverSocket, str, sizeof(str) - 1, 0,
                         (struct sockaddr *)&client, &len);

    if (n < 0) {
        perror("Receive failed");
        close(serverSocket);
        return 1;
    }
    str[n] = '\0';

    printf("Received: %s\n", str);

    // Reverse the string
    int i = 0;
    int j = (int)strlen(str) - 1;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }

    // Send reversed string back to client
    if (sendto(serverSocket, str, strlen(str) + 1, 0,
               (struct sockaddr *)&client, len) < 0) {
        perror("Send failed");
        close(serverSocket);
        return 1;
    }

    close(serverSocket);
    return 0;
}
