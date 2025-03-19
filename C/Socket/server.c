#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main() {

    struct sockaddr_in sin;
    int sin_len;
    char buffer[4096];

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock< 0) {
        perror("socket failed");
        abort();
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(8080);

    if(bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("bind failed");
        abort();
    }

    int read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&sin, &sin_len);

    if(read_bytes < 0) {
        perror("recvfrom failed");
        abort();
    }

    return 0;
   
}