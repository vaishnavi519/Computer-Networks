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

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(9001);

    if (inet_pton(AF_INET, "127.0.0.1",
                  &server.sin_addr) != 1) {
        fprintf(stderr, "Invalid server IP address\n");
        close(clientSocket);
        return 1;
    }

    // Input string
    printf("Enter a string: ");

    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Input failed\n");
        close(clientSocket);
        return 1;
    }

    // Remove newline
    str[strcspn(str, "\n")] = '\0';

    // Send string to server
    if (sendto(clientSocket, str, strlen(str) + 1, 0,
               (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Send failed");
        close(clientSocket);
        return 1;
    }

    // Receive reversed string
    ssize_t n = recvfrom(clientSocket, str, sizeof(str) - 1, 0,
                         (struct sockaddr *)&server, &len);

    if (n < 0) {
        perror("Receive failed");
        close(clientSocket);
        return 1;
    }

    str[n] = '\0';

    printf("Reversed string: %s\n", str);

    close(clientSocket);
    return 0;
}
