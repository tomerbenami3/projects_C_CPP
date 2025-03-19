#ifndef __DECK_H__
#define __DECK_H__
#include <stddef.h>
#include "cards.h"

#define DECK_SIZE 52
#define BLOCK_SIZE 4


typedef struct Deck Deck;


Deck* DeckCreate(size_t _deckAmount);

void DeckDestroy(Deck** _deck);

Card* DeckRemoveCard(Deck* _deck);

void DeckShuffle(Deck* _deck);


#endif // _DECK_H__