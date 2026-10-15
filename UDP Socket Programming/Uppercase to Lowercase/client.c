#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int s;
    char str[100];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter uppercase string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    sendto(s, str, strlen(str)+1, 0,
           (struct sockaddr *)&server, sizeof(server));

    int n = recvfrom(s, str, sizeof(str)-1, 0,
                     (struct sockaddr *)&server, &len);
    str[n] = '\0';

    printf("Lowercase string: %s\n", str);

    close(s);
    return 0;
}
