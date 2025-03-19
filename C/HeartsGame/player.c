#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "player.h"
#include "ui.h"
#include "../Vectornew/vector.h"

#define INITIAL_CARDS_CAPACITY 30
#define BLOCK_SIZE 4
#define HAND_SIZE 13
#define NUM_OF_CARDS_TO_PASS 3

struct Player{
    int m_id;
    Vector* m_cards;
    int m_isReal;  //real or machine player
};

static void SwapCards(Card* _card1, Card* _card2);
static void SortAfterRemoveCard(Vector* _hand, int removeIndex);
static Vector* GetLegalCards(Vector* _tableCards, Vector* _hand, Rules _rulesFunction, void* _context);
static int ConvertIndexFromLegalToHand(Vector* _hand, Vector* _legalCards, int _removeIndex);

Player* PlayerCreate(int _isReal, int _id) {


    Player* player = (Player*)malloc(sizeof(Player));

    if(player == NULL) {
        return NULL;
    }

    player->m_cards = VectorCreate(INITIAL_CARDS_CAPACITY, BLOCK_SIZE);

    if(player->m_cards == NULL) {
        return NULL;
    }

    player->m_id = _id;
    player->m_isReal = _isReal;

    return player;
}

void PlayerDestroy(Player** _player) {

    if(_player == NULL || *_player == NULL) {
        return;
    }

    Player* pptr = *_player;

    VectorDestroy(&pptr->m_cards, free);
    free(pptr);

    *_player = NULL;
}

void PlayerReceiveCard(Card* _card, Player* _player) {

    int status;

    if(_card == NULL || _player == NULL) {
        return;
    }

    status = VectorAppend(_player->m_cards, _card);

    if(status != VECTOR_SUCCESS) {
        return;
    }
}

void* PlayerRemoveCard(Player* _player, Vector* _tableCards, Rules _rulesFunction, Strategy _strategy, void* _context) {

    int removeIndex, cardsInHand;
    void* card;
    Card* cardToRemove, *lastCard;

    if(_player == NULL) {
        return NULL;
    }

    cardsInHand = VectorSize(_player->m_cards) - 1;

    if(_player->m_isReal) {
        
        printf("\nChoose Card:\n");
        PrintHand(_player->m_cards);
        PrintTable(_tableCards);
        scanf("%d", &removeIndex);
        VectorGet(_player->m_cards, removeIndex, (void**)&cardToRemove);
        //CHECK VALID INDEX


        while(_rulesFunction(_tableCards, _player->m_cards, cardToRemove, _context) == 0 || removeIndex > cardsInHand) {

            printf("Invalid Card\nChoose Card To Remove:\n");
            scanf("%d", &removeIndex);
            VectorGet(_player->m_cards, removeIndex, (void**)&cardToRemove);
        }

        VectorGet(_player->m_cards, removeIndex, (void**)&cardToRemove);
        VectorGet(_player->m_cards, cardsInHand, (void**)&lastCard);
        SwapCards(cardToRemove, lastCard);
        VectorRemove(_player->m_cards, &card);
        SortAfterRemoveCard(_player->m_cards, removeIndex);


    } else {

        Vector* legalCards = GetLegalCards(_tableCards, _player->m_cards, _rulesFunction, _context);

        removeIndex = _strategy(_tableCards, legalCards, _context);
        removeIndex = ConvertIndexFromLegalToHand(_player->m_cards, legalCards, removeIndex);

        VectorGet(_player->m_cards, removeIndex, (void**)&cardToRemove);
        VectorGet(_player->m_cards, cardsInHand, (void**)&lastCard);
        SwapCards(cardToRemove, lastCard);
        VectorRemove(_player->m_cards, &card);
        SortAfterRemoveCard(_player->m_cards, removeIndex);

    }

    return card;
}

static int ConvertIndexFromLegalToHand(Vector* _hand, Vector* _legalCards, int _removeIndex) {

    int index;
    int size = VectorSize(_hand);
    Card *cardToRemove, *cardToCompare;

    VectorGet(_legalCards, _removeIndex, (void**)&cardToRemove);

    for(index = 0; index < size; ++index) {
        VectorGet(_hand, index, (void**)&cardToCompare);

        if(cardToRemove->m_rank == cardToCompare->m_rank && cardToRemove->m_suite == cardToCompare->m_suite) {
            return index;
        }
    }

    return -1;
}

static Vector* GetLegalCards(Vector* _tableCards, Vector* _hand, Rules _rulesFunction, void* _context) {

    Vector* legalCards = VectorCreate(HAND_SIZE, 2);
    int index;
    int handSize = VectorSize(_hand);
    Card* card;

    if(legalCards == NULL) {
        return NULL;
    }

    for(index = 0; index < handSize; ++index) {
        VectorGet(_hand, index, (void**)&card);

        if(_rulesFunction(_tableCards, _hand, card, _context)) {
            VectorAppend(legalCards, (void*)card);
        }
    }

    return legalCards;
}

int SearchTwoClub(Player* _player) {

    int index;
    Card* card;
    void* item;

    if(_player == NULL) {
        return -1;
    }

    for(index = 0; index < HAND_SIZE; ++index) {
        VectorGet(_player->m_cards, index, &item);

        card = (Card*)item;

        if(card->m_rank == 0 && card->m_suite == _CLUB) {
            return 1;
        }
    }

    return 0;
}

static void SwapCards(Card* _card1, Card* _card2) {
    Card temp = *_card1;
    *_card1 = *_card2;
    *_card2 = temp;
}

Vector* GetPlayerHand(Player* _player) {


    if(_player == NULL) {
        return NULL;
    }

    return _player->m_cards;
}

static void SortAfterRemoveCard(Vector* _hand, int removeIndex) {

    int index, size = VectorSize(_hand) - 1;
    Card *firstCard, *secondCard;

    for(index = removeIndex; index < size; ++index) { 
        
        VectorGet(_hand, index, (void*)&firstCard);
        VectorGet(_hand, index + 1, (void*)&secondCard);
        SwapCards(firstCard, secondCard);

    }
}