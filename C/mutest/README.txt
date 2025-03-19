mu_test.h       is the header file, include it as first file in your source
utest.c         is the demo sample test that demonstarte various spects of the testing framework.
Compile with gcc like:
gcc-12 -std=c99 -pedantic -Wall utest.c -o utest

Run with:   ./utest

or for timing run it with the following command:    ./utest -v