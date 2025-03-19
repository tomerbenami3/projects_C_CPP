#include <stdio.h>
#define BUF_SIZE 250


int main(int argc, char* argv[]) {

    FILE *fp1, *fp2 , *fp3;
    char buf[BUF_SIZE];

    fp1 = popen(argv[1],"r");
    // fp2 = popen(argv[2],"r");
    fp2 = popen(argv[2], "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("ERROR in open pipe\n");
        return -1;
    }

    while (fgets(buf,BUF_SIZE-1,fp1) != NULL) {
        fputs(buf,fp2);
    }

    fclose(fp1);
    fclose(fp2);
}
// The shell command: ls –l | wc