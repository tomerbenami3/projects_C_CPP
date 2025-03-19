#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main() {

    char message[] = "Hey Im here BRO!!";
    int len = strlen(message);
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock< 0) {
        perror("socket failed");
        abort();
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(8080);

    int sent_bytes = sendto(sock, message, len, 0, (struct sockaddr*)&sin, sizeof(sin));

    if(sent_bytes < 0) {
        perror("sendto failed");
        abort();
    }

    return 0;
   
}

bool send(const std::string& message)
    {
        // sendto() returns the number of bytes sent, or -1 on error
        ssize_t sentBytes = ::sendto(
            m_sock,                      // socket descriptor
            message.data(),             // message buffer
            message.size(),             // message length
            0,                          // flags
            reinterpret_cast<sockaddr*>(&m_serverAddr),
            sizeof(m_serverAddr)
        );

        // Return true if all bytes were successfully sent
        return (sentBytes == static_cast<ssize_t>(message.size()));
    }
