#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "outfix.h"

#define OK 0
#define ERROR -1
#define ERROR_NOT_VALID -2


static int Print(void* _element, size_t _index, void* _context) {
        printf("%c\n", *((char*)(_element)));
    return 1;
}

static void _elementDestroy(void* item) {

    if(item == NULL) {
        return;
    }

    // free(item);
}

int checkBracket(char* _name) {

    int len = strlen(_name);
    int i, counter = 0;

    if(_name == NULL) {
        return ERROR;
    }

    for(i = 0;i < len; ++i) {
        if(_name[i] == '(') {
            counter++;
        } else if (_name[i] == ')'){
            counter--;
        }
        if(counter < 0) {
            return ERROR;
        }

        printf("%d\n", counter);
    }

    if(counter == 0) {
        return 0;
    }

    return 9;
}

int checkBracketsTypes(char* _name) {
    int len = strlen(_name);
    int i;
    void* z;

    Stack* sptr;

    sptr = StackCreate(len, 4);

    if(_name == NULL) {
        return ERROR;
    }

    for(i = 0;i < len; ++i) {

        if(_name[i] == '(' || _name[i] == '[' || _name[i] == '{') {
            StackPush(sptr, &_name[i]);
        }

        if(_name[i] == ')' || _name[i] == ']' || _name[i] == '}') {

            if(StackIsEmpty(sptr)) {
                return ERROR_NOT_VALID;
            }
            // StackTop(sptr, &z);
            StackPop(sptr, &z);

            if(*(char*)z == '(' && _name[i] == ')') {
                continue;
            }
            if(*(char*)z == '[' && _name[i] == ']') {
                continue;
            }
            if(*(char*)z == '{' && _name[i] == '}') {
                continue;
            } else {
                return ERROR_NOT_VALID;
            }
        }
    }

    if(!StackIsEmpty(sptr)) {
        return ERROR_NOT_VALID;
    }

    StackDestroy(&sptr,_elementDestroy);

    return OK;
}

int ConvertInToOutfix(char* infix, char* postfix) {
    
    int len = strlen(infix);
    int i, j;
    char* ch;
    char* temp;

    Stack* sptr;

    sptr = StackCreate(len, 1);

    if(infix == NULL) {
        return ERROR;
    }

    for(i = 0, j =0; i < len; ++i) {

        if(infix[i] == ' ') {
            continue;
        }

        if(infix[i] >= '1' && infix[i] <= '9') {
            postfix[j++] = infix[i];
            continue;
        }

        if(infix[i] == '(') {
            StackPush(sptr, &infix[i]);
            continue;
        }

        if(infix[i] == ')') {
            while(*ch != '(') {
                StackPop(sptr, &postfix[j++]);
                StackTop(sptr, &ch);
            }
        }

        if(infix[i] == '+' || infix[i] == '-') {
            StackTop(sptr, &ch);

            if(*ch == ')') {
                StackPop(sptr, &ch);

                while(ch != '(') {
                    StackPop(sptr, &postfix[j++]);
                    StackTop(sptr, &ch);
                }
            }

            if(*ch == '*' || *ch == '/' || *ch == '+' || *ch == '-') {

                while(StackIsEmpty(sptr) && *ch != '(') {
                    StackPop(sptr, &postfix[j++]);
                    StackTop(sptr, &ch);
                }
      
            }

            StackPush(sptr, &infix[i]); 
        }

        if(infix[i] == '*' || infix[i] == '/') {
            StackTop(sptr, &ch);

            if(*ch == '*' || *ch == '/') {
                StackPop(sptr, &postfix[j++]);

                while(*ch != '+' || *ch != '-' || *ch != '(') {
                    StackPop(sptr, &postfix[j++]);
                    StackTop(sptr, &ch);
                }
                
            } else if (*ch == '-' || *ch == '+') {
                StackPush(sptr, &infix[i]);
            }
        }

    }

    for(i = 0; i < strlen(postfix); i++) {
        printf("%c", postfix[i]);
    }

    return 0;

}