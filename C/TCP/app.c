#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "../DoubleLinkedList/dlist.h"

#define CLIENTS_AMOUNT 100

static int FindEmptySlot(int* client_sockets, int client_index, int client_sock);

int main()
{   
    char buffer[4096];
    int bufferSize = sizeof(buffer);
    int client_sockets[CLIENTS_AMOUNT] = {0}, client_index = 0;
    int client_sock, counter = 0;

    List* client_list = ListCreate();

    if(client_list == NULL) {
        perror("Client List ERROR");
        return 0;
    }

    int sock = ServerSocketOpen();
    ServerSocketSet(sock);

    struct sockaddr_in sin = ServerInitSocket();
    ServerSocketBind(sock, (struct sockaddr *)&sin);
    ServerSocketListen(sock);
    void* toRemove;

    while(1) {

        client_sock = ServerReceiveNewClient(sock);

        if (client_sock > 0) {
            if (counter < CLIENTS_AMOUNT) {
            client_index = FindEmptySlot(client_sockets, client_index, client_sock);
            ListPushHead(client_list, &client_sockets[client_index]);
            ++counter;
            } else {
                close(client_sock);
            }
        }

        toRemove = ListItrForEach(ListItrBegin(client_list), ListItrEnd(client_list), ToList_ReceiveAndSend, NULL);
        if(toRemove != ListItrEnd(client_list)) {
            ListItrRemove(toRemove);
            --counter;
        }
    }

    close(sock);

    return 0;
}

static int FindEmptySlot(int* client_sockets, int client_index, int client_sock) {

    for (client_index = 0; client_index < CLIENTS_AMOUNT; ++client_index) {
        if (client_sockets[client_index] == 0) {
            client_sockets[client_index] = client_sock;
            break;
        }
    }
    return client_index;
}