#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int s, i, n;
    char str[100];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&server, sizeof(server));

    printf("Server waiting...\n");

    n = recvfrom(s, str, sizeof(str)-1, 0,
                 (struct sockaddr *)&client, &len);
    str[n] = '\0';

    printf("Received: %s\n", str);

    for (i = 0; str[i] != '\0'; i++)
        str[i] = tolower((unsigned char)str[i]);

    sendto(s, str, strlen(str)+1, 0,
           (struct sockaddr *)&client, len);

    close(s);
    return 0;
}
