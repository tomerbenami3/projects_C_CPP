#include <stdbool.h>
#include "cards.h"
#include "../Vector/vector.h"

typedef struct Player Player;

typedef bool (*Rules)(Vector* _tableCards, Vector* _hand, Card* _card, void* _context);
typedef int (*Strategy)(Vector* _tableCards, Vector* _legalCards, void* _context);

Player* PlayerCreate(int _isReal, int _id);

void PlayerDestroy(Player** _player);

void PlayerReceiveCard(Card* _card, Player* _player);

int SearchTwoClub(Player* _player);

Vector* GetPlayerHand(Player* _player);

void* PlayerRemoveCard(Player* _player, Vector* _tableCards, Rules _rulesFunction, Strategy _strategy, void* _context);