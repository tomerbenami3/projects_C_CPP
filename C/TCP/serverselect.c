#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "serverselect.h"
#include "../DoubleLinkedList/dlist.h"


#define PORT 9090
#define BACK_LOG 1000
#define FAIL -1

static int ChangeToNoBlockingMode(int _sock);

int ServerSocketOpen() {

    int flags;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("ServerSocketOpen failed");
        abort();
    }

    return sock;
}

void ServerSocketSet(int _sock) {

    int optval = 1;
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("ServerSocketSet - reuse failed");
        abort();
    }
}

struct sockaddr_in ServerInitSocket(int _sock, fd_set* _master) {

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);

    FD_ZERO(_master);
    FD_SET(_sock, _master);

    return sin;
}

void ServerSocketBind(int _sock, struct sockaddr* _sin) {

    if (bind(_sock, (struct sockaddr *) _sin, sizeof(*_sin)) < 0) {
        perror("ServerSocketBind failed");
        abort();
    }

}

void ServerSocketListen(int _sock) {

    if (listen(_sock, BACK_LOG) < 0) {
                perror("ServerSocketListen failed");
                abort();
        }
}

int ServerReceiveNewClient(int _sock, fd_set* _slave) {

    struct sockaddr_in client_sin;
    int addr_len = sizeof(client_sin);
    int flags, client_sock;

    client_sock = accept(_sock,(struct sockaddr *) &client_sin, &addr_len);


    if (client_sock < 0) {
        perror("Error in ServerReceiveNewClient");
        close(client_sock);
    }

    if(client_sock > 0) {

        flags = ChangeToNoBlockingMode(client_sock);

        if (flags < 0) {
            perror("Client flags:");
            close(client_sock);
            return -1;
        }
    }

    return client_sock;
}

int ServerReadData(int* _client_sock) {
    
    char buffer[4096] = {0};
    int _bufferSize = sizeof(buffer);
    int read_bytes = recv(*_client_sock, buffer, _bufferSize, 0);
    
    if (read_bytes < 0) {
        if(errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Error in ServerReadData");
            close(*_client_sock);
            *_client_sock = 0;
            return 0;
        }
    }

    if (read_bytes == 0) { 
        close(*_client_sock);
        *_client_sock = 0;
        return 0;
    }
    if(read_bytes > 0) {
        printf("message received from socket: %d. MESSAGE: %s\n", *_client_sock, buffer);
        ServerSendData(*_client_sock, buffer);
        memset(buffer, '\0', strlen(buffer));
    }
    return 1;
}

int ToList_ReceiveAndSend(void* _sock, void* _no_use) {
    
    return ServerReadData((int*)_sock);
}

void ServerSendData(int _client_sock, char* buffer) {

    int sent_bytes = send(_client_sock, buffer, strlen(buffer), 0);

    if (sent_bytes < 0) {
    
        if(errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Error in ServerSendData");
            close(_client_sock);
            abort();
        }
    }

    if (sent_bytes < 0) {
        perror("Server send data failed:");
    }
}

static int ChangeToNoBlockingMode(int _sock) {

    int flags;

        if (FAIL == (flags = fcntl(_sock, F_GETFL))) {
        perror("error at fcntl. F_GETFL.");
        return -1;
    }

    if(FAIL == fcntl(_sock, F_SETFL, flags | O_NONBLOCK)) {
        perror("error at fcntl. F_SETFL.");
        return -1;
    }

    return flags;
}
