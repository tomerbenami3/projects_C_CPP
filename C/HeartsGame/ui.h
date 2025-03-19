#include "../Vectornew/vector.h"
#include "cards.h"
/* bold/not bold */
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[21m"
/* colors */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define GRAY "\x1b[90m"
/* cards suites symbols */
#define HEART "\xE2\x99\xA5"
#define SPADE "\xE2\x99\xA0"
#define DIAMOND "\xE2\x99\xA6"
#define CLUB "\xE2\x99\xA3"


void PrintTable(Vector* _hand);

int PrintAndCovertRank(void* _card, size_t _index, void* _context);

int PrintHand(Vector* _hand);