#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SENDER "./sender.out"
#define RECEIVER "./receiver.out"

void OpenTerminal(char* _ip, char* _port, char* _username);