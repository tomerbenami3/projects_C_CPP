#include <stdio.h>
#include <stdlib.h>
#include "../Vectornew/vector.h"
#include "deck.h"
#include <time.h>
// #include "cards.h"


struct Deck{
    Vector* m_cards;
};

static void PopulateDeck(Deck* _deck, size_t _deckAmount);
static size_t PrintCard(void* _card);
static Card* CardCreate(int _rankIndex, int _suiteIndex);
static void SwapCards(Deck* _deck, int index, int randIndex);
void PrintDeck(Deck* _deck);

Deck* DeckCreate(size_t _deckAmount) {

    Deck* deck;

    if(_deckAmount == 0) {
        return NULL;
    }

    deck = (Deck*)malloc(sizeof(Deck));

    if(deck == NULL) {
        return NULL;
    }

    PopulateDeck(deck, _deckAmount);

    return deck;
}

void DeckDestroy(Deck** _deck) {

    if(_deck == NULL || *_deck == NULL) {
        return;
    }

    Deck* dptr = *_deck;
    Vector* vptr = dptr->m_cards;

    VectorDestroy(&vptr, free);
    free(dptr);

    *_deck = NULL;
}

void DeckShuffle(Deck* _deck) {
    
    int index, randIndex;

    if(_deck == NULL) {
        return;
    }

    srand(time(NULL));

    for(index = DECK_SIZE - 1; index > 0; --index) {
        randIndex = rand() % index;
        // PrintDeck(_deck);
        SwapCards(_deck, index, randIndex);
    }
    
    // PrintDeck(_deck);
}

static void PopulateDeck(Deck* _deck, size_t _deckAmount) {

    int suiteIndex, rankIndex, freeIndex, vectorStatus;

    _deck->m_cards = VectorCreate(DECK_SIZE * _deckAmount, BLOCK_SIZE);

        for(suiteIndex = 0; suiteIndex < NUM_OF_SUITE; ++suiteIndex) {
            for(rankIndex = 0; rankIndex < RANK_AMOUNT; ++rankIndex) {

                vectorStatus = VectorAppend(_deck->m_cards, CardCreate(rankIndex, suiteIndex));

                if(vectorStatus != VECTOR_SUCCESS) {
                    VectorDestroy(&_deck->m_cards, NULL);
                    free(_deck);
                    _deck = NULL;
                    return;
                }
        }
    }

    // PrintCard(_deck);
}

static Card* CardCreate(int _rankIndex, int _suiteIndex) {

    Card* cptr = (Card*)malloc(sizeof(Card));

    if(cptr == NULL) {
        return NULL;
    }

    cptr->m_rank = _rankIndex;
    cptr->m_suite = _suiteIndex;

    return cptr;
}

Card* DeckRemoveCard(Deck* _deck) {

    Card* card;
    int status;

    if(_deck == NULL) {
        return NULL;
    }

    status = VectorRemove(_deck->m_cards, (void**)&card);

    if(status != VECTOR_SUCCESS) {
        return NULL;
    }

    return card;
}

static void SwapCards(Deck* _deck, int index, int randIndex) {

    Card* lastCard, *randomCard, temp;

    VectorGet(_deck->m_cards, index, (void**)&lastCard);
    VectorGet(_deck->m_cards, randIndex, (void**)&randomCard);

    VectorSet(_deck->m_cards, randIndex, (void*)lastCard);
    VectorSet(_deck->m_cards, index, (void*)randomCard);
}