#include <stdio.h>
#include <dlfcn.h>

typedef void (*dLibFunc) (void);

int main() {

    dLibFunc dlFunc;
    void *dl = dlopen("libdltest.so", RTLD_LAZY);

    if(dl == NULL) {
        printf("dl open failed\n");
        return -1;
    }

    dlFunc = (dLibFunc)dlsym(dl, "PrintDL");

    if(dlFunc == NULL) {
        printf("dlsym failed\n");
        return -2;
    }
    dlFunc();
    dlclose(dl);
    return 0;
}