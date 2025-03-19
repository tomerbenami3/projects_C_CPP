#include <stdio.h>
#include "ui.h"
#include "deck.h"
#include "cards.h"
#include "player.h"
#include "../Vectornew/vector.h"


void PrintTable(Vector* _hand) {

    if(_hand == NULL) {
        return;
    }

    VectorForEach(_hand, PrintAndCovertRank, NULL);
    printf("\n");
}

int PrintHand(Vector* _hand) {

    int index;
    int size = VectorSize(_hand);

    for(index = 0; index < size; ++index) {
        printf("%d  ", index);
    }
    printf("\n");
    PrintTable(_hand);

    return 1;
}

int PrintAndCovertRank(void* _card, size_t _index, void* _context) {

    char rank;
    Card* card = (Card*)_card;
    Suite suite = card->m_suite;
    switch (card->m_rank)
    {
    case 8:
        rank = 'T';
        break;
    case 9:
        rank = 'J';
        break;
    case 10:
        rank = 'Q';
        break;
    case 11:
        rank = 'K';
        break;
    case 12:
        rank = 'A';
        break;
    default:
        rank = card->m_rank + '2';
        break;
    }

    switch (suite)
    {
    case 0:
        printf("%s%c%s ",RED, rank, HEART);
        break;
    case 1:
        printf("%s%c%s ",BLACK, rank, SPADE);
        break;
    case 2:
        printf("%s%c%s ",RED, rank, DIAMOND);
        break;
    case 3:
        printf("%s%c%s ",BLACK, rank, CLUB);
        break;
    default:
        break;
    }
    return 1;
}