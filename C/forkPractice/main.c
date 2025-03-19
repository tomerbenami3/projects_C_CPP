#include <stdio.h>
#include <unistd.h>

int g_var=0;

int main() {

    int i = 5;
    sleep(10);

    int pid = fork();

    if (pid == 0){
        sleep(10);
    } else {
        sleep(20);
    }

    return 0;
}
