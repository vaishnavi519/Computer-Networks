#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress;
    char message[1024], reply[1024];

    // Create TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        return 1;
    }

    // Listen for client
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        close(serverSocket);
        return 1;
    }

    printf("TCP Chat Server waiting for client...\n");

    // Accept client connection
    clientSocket = accept(serverSocket, NULL, NULL);

    if (clientSocket < 0) {
        perror("Accept failed");
        close(serverSocket);
        return 1;
    }

    printf("Client connected!\n");

    // Chat communication
    while (1) {
        memset(message, 0, sizeof(message));

        int n = recv(clientSocket, message,
                     sizeof(message) - 1, 0);

        if (n <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        message[n] = '\0';
        printf("Client: %s\n", message);

        if (strcmp(message, "exit") == 0)
            break;

        printf("Server: ");
        if (fgets(reply, sizeof(reply), stdin) == NULL)
            break;

        reply[strcspn(reply, "\n")] = '\0';

        if (send(clientSocket, reply, strlen(reply), 0) < 0) {
            perror("Send failed");
            break;
        }

        if (strcmp(reply, "exit") == 0)
            break;
    }

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    printf("Server closed.\n");
    return 0;
}
