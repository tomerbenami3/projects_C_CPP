#include <iostream>
#include "../../inc/challenger/challenger_1.hpp"

static void swapBalls(Ball& _ball1, Ball& _ball2);
/// @brief 
/// @return 
long Fibo() {

    static long prev = 0, current = 1, counter = 1;

    if(counter == 1) {
        ++counter;
        return prev;
    } else if (counter == 2) {
        ++counter;
        return current;
    } else {
        current = current + prev;
        prev = current - prev;
        return current;
    }
}

int Factorial(int const number)
{
    if(number < 0) {
        return -1;
    }

    if (number == 0) {
        return 1;
    }

    return number * Factorial(number - 1);
}

void sortBalls(Ball* _balls, int _size) {

    if(_balls == NULL) {
        return;
    }

    int white_index = 0, array_index = 0, black_index = _size - 1;

    while(array_index <= black_index) {
        if(_balls[array_index].color == White) {
            swapBalls(_balls[white_index], _balls[array_index]);
            ++white_index;
        }
        ++array_index;
    }

    array_index = 0;

    while(array_index <= black_index) {
        if(_balls[array_index].color == Black) {
            swapBalls(_balls[black_index], _balls[array_index]);
            --black_index;
        }
        ++array_index;
    }
}

static void swapBalls(Ball& _ball1, Ball& _ball2) {
    Ball temp;
    temp = _ball1;
    _ball1 = _ball2;
    _ball2 = temp;
}