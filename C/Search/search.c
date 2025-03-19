#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int Search(int* _arr, int _size, int _num) {

    int index;

    if(_arr == NULL) {
        return -1;
    }

    for(index = 0; index < _size; ++index) {
        if(_arr[index] == _num) {
            return index;
        }
    }

    return index;
}

int SearchBetter(int* _arr, int _size, int _num) {

    int index;

    if(_arr == NULL) {
        return -1;
    }

    if(_arr[_size - 1] == _num) {
        return _size - 1;
    }

    int temp = _arr[_size - 1];
    _arr[_size - 1] = _num;

    for(index = 0;;++index) {
        if(_arr[index] == _num) {
            if(index < _size - 1) {
                _arr[_size - 1] = temp;
                return index;
            } else {
                _arr[_size - 1] = temp;
                return index;
            }
        }
    }

    return -1;
}

int Search4Times(int* _arr, int _size, int _num) {

    int index, g;

    if(_arr == NULL) {
        return -1;
    }

    for(index = 0, g = 4; g < _size; g+=4) {
        if(_arr[index++] == _num) {
            return index;
        }
        if(_arr[index++] == _num) {
            return index;
        }
        if(_arr[index++] == _num) {
            return index;
        }
        if(_arr[index++] == _num) {
            return index;
        }
    }


    for(; index < _size; ++index) {
        if(_arr[index] == _num) {
            return index;
        }
    }

    return -1;
}