#include "cards.h"
#include <stdbool.h>

#define HAND_SIZE 13
#define TRICKS_TOTAL 13
#define LIMIT_SCORE 100
#define SCORE_TABLE_SIZE 4
#define NUM_OF_CARDS_TO_PASS 3
#define GAME_IS_NOT_OVER -1
#define UNINITIALIZED -2
#define HAND_IS_EMPTY -3

typedef struct Round Round;
typedef struct Context Context;
typedef struct Vector Vector;

Round* RoundCreate(Player** _players, int _playersNum);

void RoundDestroy(Round** _round);

void PlayerReceiveCard(Card* _card, Player* _player);

int RunRound(Round* _round, int* _score, size_t _deckAmount);

bool RulesForPassingCard(Vector* _tableCards, Vector* _hand, Card* _realPlayerCard, void* _context);

int StrategyForPassingCards(Vector* _tableCards, Vector* _legalCards, void* _context);

bool RulesForTricks(Vector* _tableCards, Vector* _hand, Card* _card, void* _context);