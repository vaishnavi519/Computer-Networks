#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char message[1024], reply[1024];

    // Create TCP socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);

    // Use the server machine's IP address
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) < 0) {
        perror("Connection failed");
        close(clientSocket);
        return 1;
    }

    printf("Connected to TCP Chat Server!\n");
    printf("Type 'exit' to close the chat.\n");

    // Chat communication
    while (1) {
        printf("Client: ");

        if (fgets(message, sizeof(message), stdin) == NULL)
            break;

        message[strcspn(message, "\n")] = '\0';

        if (send(clientSocket, message, strlen(message), 0) < 0) {
            perror("Send failed");
            break;
        }

        if (strcmp(message, "exit") == 0) {
            printf("Chat ended.\n");
            break;
        }

        memset(reply, 0, sizeof(reply));

        int n = recv(clientSocket, reply, sizeof(reply) - 1, 0);

        if (n <= 0) {
            printf("Server disconnected.\n");
            break;
        }

        reply[n] = '\0';
        printf("Server: %s\n", reply);

        if (strcmp(reply, "exit") == 0) {
            printf("Server ended the chat.\n");
            break;
        }
    }

    // Close client socket
    close(clientSocket);

    printf("Client socket closed.\n");
    return 0;
}
