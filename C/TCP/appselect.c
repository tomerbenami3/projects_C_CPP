#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "serverselect.h"
#include "../DoubleLinkedList/dlist.h"
#include <sys/select.h>
#include <errno.h>


#define CLIENTS_AMOUNT 100

static int FindEmptySlot(int* client_sockets, int client_index, int client_sock);

int main()
{   
    fd_set masterfds, slavefds;


    char buffer[4096];
    int bufferSize = sizeof(buffer);
    int client_sockets[CLIENTS_AMOUNT] = {0}, client_index = 0;
    int client_sock, counter = 0, activity;

    List* client_list = ListCreate();

    if(client_list == NULL) {
        perror("Client List ERROR");
        return 0;
    }

    int sock = ServerSocketOpen();
    ServerSocketSet(sock);

    struct sockaddr_in sin = ServerInitSocket(sock, &masterfds);
    ServerSocketBind(sock, (struct sockaddr *)&sin);
    ServerSocketListen(sock);
    void* nodetoRemove;

    while(1) {
        slavefds = masterfds;
        activity = select(1024, &slavefds, NULL, NULL, NULL);

        if ((activity < 0) && (errno!=EINTR)) {
            printf("select error");
        }
        if((FD_ISSET(sock, &slavefds))) {
            client_sock = ServerReceiveNewClient(sock, &slavefds);

            if (client_sock > 0) {
                if (counter < CLIENTS_AMOUNT) {
                client_index = FindEmptySlot(client_sockets, client_index, client_sock);
                ListPushHead(client_list, &client_sockets[client_index]);
                ++counter;
                FD_SET(sock, &masterfds);
                } else {
                    close(client_sock);
                }
            }
        }

        if(activity > 0) {
        nodetoRemove = ListItrForEach(ListItrBegin(client_list), ListItrEnd(client_list), ToList_ReceiveAndSend, NULL);
        }

        if(nodetoRemove != ListItrEnd(client_list)) {
            ListItrRemove(nodetoRemove);
            FD_CLR(sock, &masterfds); // ???
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