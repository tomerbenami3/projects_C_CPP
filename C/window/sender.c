#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define MESSAGE_LENGTH 1024
#define BUFFER_LENGTH 2048

static int ClientSocketOpen();
static struct sockaddr_in ClientInitSocket();
static void GetMessage(char* message);
static void SendMessage(int _sock, char* _message, struct sockaddr_in* _sin, int _sin_len);
static void packMessage(const char *username, const char *message, char *buffer, size_t *len);

int main(int argc, char* argv[]) {

    char* username = argv[3];
    char buffer[BUFFER_LENGTH];
    size_t packed_len;

    int sock = ClientSocketOpen();
    struct sockaddr_in sin = ClientInitSocket();
    int sin_len = sizeof(sin);

    char message[MESSAGE_LENGTH];

    while(1) {
        printf("Enter message:\n");

        GetMessage(message);
        packMessage(username, message, buffer, &packed_len);
        SendMessage(sock, buffer, (struct sockaddr_in*)&sin, sin_len);

    }

    close(sock);
    return 0;
}

static struct sockaddr_in ClientInitSocket() {

    struct sockaddr_in sin;

    memset(&sin, 0 ,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("230.0.0.1");
    sin.sin_port = htons(PORT);

    return sin;
}

static int ClientSocketOpen() {

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket failed");
        return -1;
    }

    return sock;
}

static void GetMessage(char* message) {
    if(fgets(message, MESSAGE_LENGTH, stdin) == NULL) {
        perror("Error reading message:");
    }
}

static void SendMessage(int _sock, char* _message, struct sockaddr_in* _sin, int _sin_len) {

    if(sendto(_sock,_message, strlen(_message), 0, (struct sockaddr_in*)_sin, _sin_len) < 0) {
        perror("Sendto Failed");
    }
}

static void packMessage(const char *username, const char *message, char *buffer, size_t *len) {

    unsigned char username_len = strlen(username);
    unsigned char message_len = strlen(message);

    buffer[0] = username_len;
    memcpy(buffer + sizeof(unsigned char), username, username_len);

    buffer[username_len + 1] = message_len;
    memcpy(buffer + 2*sizeof(unsigned char) + username_len, message, message_len);

    *len = 2 * sizeof(unsigned char) + username_len + message_len;
}