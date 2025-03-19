#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define PORT 9090
#define CLIENTS_AMOUNT 100

int ClientSocketOpen() {

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("socket failed");
        return -1;
    }

    return sock;
}

struct sockaddr_in ClientInitSocket() {

    struct sockaddr_in sin;

    memset(&sin, 0 ,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(PORT);

    return sin;
}

void ClientConnectSock(int _sock, struct sockaddr_in* _sin) {

    if (connect(_sock, (struct sockaddr *) _sin, sizeof(*_sin)) < 0) {
        printf("sock number: %d\n",_sock);
        perror("Client Connection failed");
        abort();
    }
}

void ClientSendData(int _sock, char* _data_addr, int _data_len) {
    int sent_bytes = send(_sock, _data_addr, _data_len, 0);
    if (sent_bytes < 0) {
        perror("send failed");
    }

}

int ClientReadData(int _sock, char* _buffer, int _expected_data_len) {

    int read_bytes = recv(_sock, _buffer, _expected_data_len, 0);

    if (read_bytes == 0) { 
        close(_sock);
    } else if (read_bytes < 0) { // error
        perror("recv failed");
    }
    return read_bytes;
}

void ClientSendAndReadData(int _sock, char* _buffer, int _expected_data_len) {
    char data[] = "Hello Server!";
    int data_len = strlen(data);
    ClientSendData(_sock, data, data_len);

    int read_bytes = ClientReadData(_sock, _buffer, _expected_data_len);

    printf("%s\n", _buffer);
}

int CreateClient() {

    int sock = ClientSocketOpen();
    struct sockaddr_in sin = ClientInitSocket();
    ClientConnectSock(sock, (struct sockaddr *)&sin);

    return sock;
}

void InitMultiClients(int* _clients) {

    int index;

    for(index = 0; index < CLIENTS_AMOUNT; ++index) {
        _clients[index] = -1;
    }
}

void ClientDisconnect(int _sock) {
    close(_sock);
}

int main() {

    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int clients[CLIENTS_AMOUNT];
    int client_index = 0;
    int chance;

    InitMultiClients(clients);

    while(true) {

        chance = rand() % 100;
        if(clients[client_index] == -1) {
            if(chance < 30) {
                clients[client_index] = CreateClient();
            }
        } else if (clients[client_index] > 0) {
            if(chance >= 30 && chance < 60) {
                ClientSendAndReadData(clients[client_index], buffer, expected_data_len);
            }
            if(chance >= 60 && chance < 65) {
                ClientDisconnect(clients[client_index]);
                clients[client_index] = -1;
            }
        }

        client_index = (client_index + 1) % CLIENTS_AMOUNT;
    }
} 