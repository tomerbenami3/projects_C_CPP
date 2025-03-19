#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include "../DoubleLinkedList/dlist.h"

int ServerSocketOpen();

void ServerSocketSet(int _sock);

struct sockaddr_in ServerInitSocket();

void ServerSocketBind(int _sock, struct sockaddr* _sin);

void ServerSocketListen(int _sock);

int ServerReceiveNewClient(int _sock);

int ServerReadData(int* _client_sock);

void ServerSendData(int _client_sock, char* buffer);

int ToList_ReceiveAndSend(void* _sock, void* _no_use);