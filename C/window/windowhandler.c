#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "windowhandler.h"

void OpenTerminal(char* _ip, char* _port, char* _username) {
    
    char senderWin[256];
    char recieverWin[256];

    sprintf(senderWin, "gnome-terminal -- bash -c '%s %s %s %s; exec bash'", SENDER, _ip, _port, _username);
    sprintf(recieverWin, "gnome-terminal -- bash -c '%s %s %s %s; exec bash'", RECEIVER, _ip, _port, _username);

    system(senderWin);
    system(recieverWin);

}

int main() {

    OpenTerminal("230.0.0.1", "8080", "tomer");
}

// git config --global user.name "tomer"
// git config --global user.email "tomerbenami3@gmail.com"

// git clone http://46.101.37.227/h76.matan/ChatProjectNew.git
// git clone http://46.101.37.227/h76.tomer/chatproject.git
// cd chatproject
// touch README.md
// git add README.md
// git commit -m "add README"
// git push -u origin master