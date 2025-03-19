

enum Color { Red, Black, White };

struct Ball {
      Color color;
      int radius;
      bool is_solid;
  };

/// @brief - find fibonachi number
/// @return - returns the fibonachi number as the number of calls
long Fibo();

/// @brief Factorial
/// @param number a number to multipy until zero
/// @return factorial of number
int Factorial(int const number);

/// @brief sort balls - white first, reds and blacks.
/// @param _balls an array of balls
/// @param _size size of the array
void sortBalls(Ball* _balls, int _size);