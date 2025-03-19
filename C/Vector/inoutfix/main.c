// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "../stack.h"

// #define OK 0
// #define ERROR -1

// int checkBracket(char* _name) {

//     int len = strlen(_name);
//     int i, counter = 0;

//     if(_name == NULL) {
//         return ERROR;
//     }

//     for(i = 0;i < len; ++i) {
//         if(_name[i] == '(') {
//             counter++;
//         } else if (_name[i] == ')'){
//             counter--;
//         }

//         if(counter < 0) {
//             return ERROR;
//         }

//         printf("%d\n", counter);
//     }

//     if(counter == 0) {
//         return 0;
//     }

//     return 9;
// }

// int checkBracketsTypes(char* _name) {
//     int len = strlen(_name);
//     int i, counter = 0;

//     Stack* sptr;

//     StackCreate(len, 4);

//     if(_name == NULL) {
//         return ERROR;
//     }

//     for(i = 0;i < len; ++i) {

//         if(_name[i] == '(' || _name[i] == '[' || _name[i] == '{') {
//             StackPush(sptr, &_name[i]);
//         }
//     }

//     return 9;
// }

// int main() {

//     char name[] = "(2 + 4)*5";

//     checkBracket(name);

//     return 0;
// }