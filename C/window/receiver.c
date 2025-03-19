#define _DEFAULT_SOURCE
#ifdef _WIN32
    #include <Winsock2.h> 
    #include <ws2ipdef.h> 
    #include <Windows.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <time.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define PORT 8080
#define BUFFER_LENGTH 1024
#define MESSAGE_LENGTH 1024
#define MAX_USER_LEN 20

static int SocketOpen();
static struct sockaddr_in ClientInitSocket();
static void SetSocket(int _sock);
static void SocketBind(int _sock, struct sockaddr* _sin);
static void unpackMessage(const char *buffer, char *username, char *message);

int main(int argc, char* argv[]) {

    char buffer[BUFFER_LENGTH];
    char username[MAX_USER_LEN];

    if (argc != 4) {
       printf("Command line args should be multicast group and port\n");
       return 1;
    }

    char* group = argv[1];
    int port = atoi(argv[2]);


    int sock = SocketOpen();
    struct sockaddr_in sin = ClientInitSocket();
    int sin_len = sizeof(sin);
    SetSocket(sock);
    SocketBind(sock, &sin);

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(group);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)) < 0) {
        perror("setsockopt");
        return 1;
    }

    while (1) {
        char message[MESSAGE_LENGTH];
        int addrlen = sizeof(sin);
        int nbytes = recvfrom(sock,buffer,BUFFER_LENGTH,0,(struct sockaddr *) &sin, &addrlen);
        if (nbytes < 0) {
            perror("recvfrom");
            return 1;
        }
        unpackMessage(buffer, username, message);
        message[nbytes] = '\0';
        printf("%s:%s", username, message);
     }

    // close(sock);
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

static int SocketOpen() {

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket failed");
        return -1;
    }

    return sock;
}

static void SetSocket(int _sock) {

    int yes = 1;

    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
       perror("Reusing ADDR failed");
       return;
    }
}

static void SocketBind(int _sock, struct sockaddr* _sin) {

    if (bind(_sock, (struct sockaddr*)_sin, sizeof(*_sin)) < 0) {
        perror("bind");
        return;
    }
}

static void unpackMessage(const char *buffer, char *username, char *message) {

    unsigned char username_len, message_len;

    username_len = buffer[0];
    memcpy(username, buffer + sizeof(unsigned char), username_len);
    username[username_len] = '\0'; 

    message_len = buffer[username_len + sizeof(unsigned char)];
    memcpy(message, buffer + 2 * sizeof(unsigned char) + username_len, message_len);
    message[message_len] = '\0';
}