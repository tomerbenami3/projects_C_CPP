#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "round.h"
#include "deck.h"
#include "cards.h"
#include "ui.h"
#include "../Vectornew/vector.h"

#define NUM_PLAYERS _round->m_playersNum

struct Round{
    Player** m_players;
    int* m_tableScore;
    int m_playersNum;
    int m_currentRound;
    Context* m_context;
};

struct Context {
    Vector* m_legalCards;
    bool m_wasHeart;
    
    // table cards
    // Hand
    // context
    // 1 card to check if valid
};

struct Strategy {
    // table cards
    // Valid cards of Hand
    // context
};

static int CheckStartingPlayerFirstRound(Round* _round);
static int CompareCards(Card* _card1, Card* _card2);
static int Trick(Round* _round, int _startingPlayer, int* _trickTableScore);
static int CheckWhoTakesCards(Vector* _table, int _startingPlayer);
static int CalculateScore(int* _cardsRank, int* _cardsSuite, int _size);
static int IsGameOver(int* _scoreTable, int size);
static int CheckWinner(int* _scoreTable, int size);
static int HandleCardIndex(int _currentRound);
static int GetMaxRankFromHand(Vector* _hand);
static void SortHand(Vector* _hand);
static void SwapCards(Card* _card1, Card* _card2);
static void DealCards(Deck* _deck, Round* _round);
static void SortAllHands(Round* _players);
static void PrintAllHands(Round* _players);
static void UpdateHeartsFlag(Context* _context, Vector* _table);
static void UpdateScoreTable(int* _trickTableScore, int _loserIndex, int _score);
static void PrintScoreTable(int* _tableScore, int _size);
static void UpdateMainTableScore(int* _score, int* _roundTableScore, int _size);
static void UpdateRoundScoreTable(int* _roundTableScore, int* _trickTableScore, int _size);
static void PrintRoundScoreTable(int* _roundTableScore, int _size, int _roundNumber);
static void PassThreeCards(Round* _round);
static bool DoWeHaveOnlyHearts(Vector* _hand);
static bool AreAllCardsAreDifferentSuite(Vector* _hand, Suite _suite);
static Context* ContextCreate();

Round* RoundCreate(Player** _players, int _playersNum) {

    if(_players == NULL || *_players == NULL) {
        return NULL;
    }

    Round* rptr = (Round*)malloc(sizeof(Round));

    if(rptr == NULL) {
        return NULL;
    }

    rptr->m_tableScore = (int*)calloc(_playersNum, sizeof(int));

    if(rptr->m_tableScore == NULL) {
        free(rptr);
        return NULL;
    }

    rptr->m_context = ContextCreate();

    rptr->m_players = _players;
    rptr->m_playersNum = _playersNum;
    rptr->m_currentRound = 0;

    return rptr;
}

void RoundDestroy(Round** _round) {

    int index;

    if(_round == NULL || *_round == NULL) {
        return;
    }

    for(index = 0; index < (*_round)->m_playersNum; ++index) {
        PlayerDestroy(&(*_round)->m_players[index]);
    }

    free((*_round)->m_players);
    free((*_round)->m_tableScore);
    free((*_round)->m_context);

    *_round = NULL;
}

int RunRound(Round* _round, int* _score, size_t _deckAmount) {

    int cardIndex, playerIndex, startingPlayerIndex, roundIndex;
    int trickTableScore[4] = {0};

    if(_score == NULL || _deckAmount == 0) {
        return UNINITIALIZED;
    }

    Deck* deck = DeckCreate(_deckAmount);

    if(deck == NULL) {
        return UNINITIALIZED;
    }

    DeckShuffle(deck);
    DealCards(deck, _round);
    startingPlayerIndex = CheckStartingPlayerFirstRound(_round);
    SortAllHands(_round);
    PrintAllHands(_round);
    PassThreeCards(_round);

    printf("\nAfter Passing Cards:\n");
    SortAllHands(_round);
    PrintAllHands(_round);
    

    for(roundIndex = 0; roundIndex < TRICKS_TOTAL; ++roundIndex) {
        startingPlayerIndex = Trick(_round, startingPlayerIndex, trickTableScore);
        _round->m_context->m_wasHeart = 0;
    }
    UpdateRoundScoreTable(_round->m_tableScore, trickTableScore, NUM_PLAYERS);
    PrintRoundScoreTable(_round->m_tableScore, NUM_PLAYERS, _round->m_currentRound);
    UpdateMainTableScore(_score,_round->m_tableScore, NUM_PLAYERS);

    _round->m_currentRound += 1;

    if(IsGameOver(_round->m_tableScore, NUM_PLAYERS)) {
        return CheckWinner(_round->m_tableScore, NUM_PLAYERS);
    }

    return GAME_IS_NOT_OVER;

}

int StrategyForTricks(Vector* _legalCards, Vector* _table, Context* _context) {


    return 0;
}

bool RulesForPassingCard(Vector* _tableCards, Vector* _hand, Card* _realPlayerCard, void* _context) {

    if(_hand == NULL) {
        return false;
    }

    return true;
}

bool RulesForTricks(Vector* _tableCards, Vector* _hand, Card* _card, void* _context) {
    
    Context* context = (Context*)_context;
    Card* firstTableCard;

    if(_tableCards == NULL || _hand == NULL || _context == NULL) {
        return false;
    }


    if(_card == NULL) {
        return false;
    }

    if(VectorSize(_tableCards) == 0) {
        if(_card->m_suite == _HEART) {
            if(context->m_wasHeart) {
                return true;
            } else if (!context->m_wasHeart) {
                if(DoWeHaveOnlyHearts(_hand)) {
                    return true;
                } else {
                    return false;
                }
            } 
        }
    } else {
        VectorGet(_tableCards, 0, (void**)&firstTableCard);
        if(_card->m_suite == firstTableCard->m_suite) {
            return true;
        } else if(AreAllCardsAreDifferentSuite(_hand, firstTableCard->m_suite)) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

int StrategyForPassingCards(Vector* _tableCards, Vector* _legalCards, void* _context) {

    int maxRankIndex;
    void* card;

    if(_legalCards == NULL) {
        return HAND_IS_EMPTY;
    }

    maxRankIndex = GetMaxRankFromHand(_legalCards);
    return maxRankIndex;
}

static bool AreAllCardsAreDifferentSuite(Vector* _hand, Suite _suite) {

    int index;
    int size = VectorSize(_hand);
    Card* card;

    for(index = 0; index < size; ++index) {
        VectorGet(_hand, index, (void**)&card);

        if(card->m_suite == _suite) {
            return false;
        }
    }
    return true;
}

static bool DoWeHaveOnlyHearts(Vector* _hand) {

    int index;
    int size = VectorSize(_hand);
    Card* card;

    for(index = 0; index < size; ++index) {
        VectorGet(_hand, index, (void**)&card);

        if(card->m_suite != _HEART) {
            return false;
        }
    }

    return true;
}

static int GetMaxRankFromHand(Vector* _hand) {

    int index, maxRank = 0, maxIndex = 0;
    int size = VectorSize(_hand);
    void* card;

    for(index = 0; index < size; ++index) {

        VectorGet(_hand, index, &card);

        if(((Card*)card)->m_rank > maxRank) {
            maxRank = ((Card*)card)->m_rank;
            maxIndex = index;
        }
    }
    /*
0  1  2  3  4  5  6  7  8  9  10  11  12  
3♥ 4♥ 9♥ K♥ A♥ 4♠ 6♠ 3♦ 8♦ K♦ 3♣ 9♣ Q♣ 
*/

    return maxIndex;
}

static void PassThreeCards(Round* _round) {

    int playerIndex, cardIndex, loopIndex;
    Card* cardsPool[NUM_OF_CARDS_TO_PASS * NUM_PLAYERS];

    for(playerIndex = 0; playerIndex < NUM_PLAYERS; ++playerIndex) {
        for(cardIndex = 0; cardIndex < NUM_OF_CARDS_TO_PASS; ++cardIndex) {
          cardsPool[cardIndex + playerIndex * NUM_OF_CARDS_TO_PASS] = (Card*)PlayerRemoveCard(_round->m_players[playerIndex], NULL, RulesForPassingCard, StrategyForPassingCards, NULL);
        }
    }

    cardIndex = HandleCardIndex(_round->m_currentRound);

    for(playerIndex = 0; playerIndex < NUM_PLAYERS; ++playerIndex) {
        for(loopIndex = 0; loopIndex < NUM_OF_CARDS_TO_PASS; ++loopIndex) {

            PlayerReceiveCard(cardsPool[cardIndex], _round->m_players[playerIndex]);
            cardIndex = (cardIndex + 1) % 12;
        }
    }
    
}

static int HandleCardIndex(int _currentRound) {

    switch(_currentRound % 4) {
        case 0:
            return 9;
        case 1: 
            return 3;
        case 2: 
            return 6;
        default: 
            return 0;
    }
}

static void PrintRoundScoreTable(int* _roundTableScore, int _size, int _roundNumber) {

    printf("\n\nRound number: %d", _roundNumber);

    PrintScoreTable(_roundTableScore, _size);
}

static void UpdateRoundScoreTable(int* _roundTableScore, int* _trickTableScore, int _size) {

   int index;

   for(index = 0; index < _size; ++index) {
    _roundTableScore[index] += _trickTableScore[index];
   }
}

static void DealCards(Deck* _deck, Round* _round) {

    int cardIndex, playerIndex;

    for(cardIndex = 0; cardIndex < HAND_SIZE; ++cardIndex) {
        for(playerIndex = 0; playerIndex < _round->m_playersNum; ++playerIndex) {
            Card* card = DeckRemoveCard(_deck);
            PlayerReceiveCard(card, _round->m_players[playerIndex]);
        }
    }
}

static void PrintAllHands(Round* _players) {

    int index;

    for(index = 0; index < _players->m_playersNum; ++index) {
        PrintHand(GetPlayerHand(_players->m_players[index]));
    }
}

static void SortAllHands(Round* _players) {

    int index;

    for(index = 0; index < _players->m_playersNum; ++index) {
        SortHand(GetPlayerHand(_players->m_players[index]));
    }
}

static void SortHand(Vector* _hand) {

    int innerIndex, outerIndex;
    int size = VectorSize(_hand);
    Card *card1, *card2;

    for(outerIndex = 0; outerIndex < size - 1; ++outerIndex) {
        for(innerIndex = 0; innerIndex < size - outerIndex; ++innerIndex) {

            VectorGet(_hand, innerIndex, (void**)&card1);
            VectorGet(_hand, innerIndex + 1, (void**)&card2);

            if(CompareCards(card1, card2)) {
                SwapCards(card1, card2);
            }
        }
    }
}

static int CompareCards(Card* _card1, Card* _card2) {

    if(_card1->m_suite < _card2->m_suite) {
        return 0;
    } else if (_card1->m_suite > _card2->m_suite) {
        return 1;
    } else {
        if(_card1->m_rank <= _card2->m_rank) {
            return 0;
        } else if (_card1->m_rank > _card2->m_rank) {
            return 1;
        }
    }

    return 0;
}

static int CheckStartingPlayerFirstRound(Round* _round) {

    int index;

    if(_round == NULL) {
        return -1;
    }

        for(index = 0; index < NUM_PLAYERS; ++index) {
            if(SearchTwoClub(_round->m_players[index])) {
                return index;
            }
        }

    return -1;
}

static void SwapCards(Card* _card1, Card* _card2) {
    Card temp = *_card1;
    *_card1 = *_card2;
    *_card2 = temp;
}

static int Trick(Round* _round, int _startingPlayer, int* _trickTableScore) {

    int index, cardsRank[NUM_PLAYERS], loserIndex, score, playerTurn;
    int cardsSuite[NUM_PLAYERS];

    Vector* table = VectorCreate(NUM_PLAYERS, 1);


    if(table == NULL) {
        return UNINITIALIZED;
    }
    
    Card* card;

    for(index = 0; index < NUM_PLAYERS; ++index) {

        playerTurn = (_startingPlayer + index) % NUM_PLAYERS;

        card = (Card*)PlayerRemoveCard(_round->m_players[playerTurn], table, RulesForTricks, StrategyForPassingCards, _round->m_context);
        VectorAppend(table, card);
        cardsRank[playerTurn] = card->m_rank;
        cardsSuite[playerTurn] = card->m_suite;
    }
        printf("\nTable Cards:\n");
        PrintTable(table);

        if(_round->m_context->m_wasHeart == 0) {
            UpdateHeartsFlag(_round->m_context, table);
        }

        loserIndex = CheckWhoTakesCards(table, _startingPlayer);
        score = CalculateScore(cardsRank, cardsSuite, NUM_PLAYERS);
        UpdateScoreTable(_trickTableScore, (_startingPlayer + loserIndex) % NUM_PLAYERS, score);
        PrintScoreTable(_trickTableScore, NUM_PLAYERS);
        VectorDestroy(&table, free);

        return loserIndex;
}

static void UpdateHeartsFlag(Context* _context, Vector* _table) {

    int index, size = VectorSize(_table);
    Card* card;

    for(index = 0; index < size; ++index) {
        VectorGet(_table, index, (void**)&card);

        if(card->m_suite == _HEART) {
            _context->m_wasHeart = 1;
            break;
        }
    }
}

static void PrintScoreTable(int* _tableScore, int _size) {

    int index;

    printf("\n");
    printf("\n");
    
    for(index = 0; index < _size; ++index) {
        printf("Player ID: %d\t", index);
    }
    printf("\n");
    for(index = 0; index < _size; ++index) {
        printf("Score: %d\t", _tableScore[index]);
    }
    printf("\n");
}

static int CalculateScore(int* _cardsRank, int* _cardsSuite, int _size) {

    int index, score = 0;

    for(index = 0; index < _size; ++index) {

        if(_cardsSuite[index] == 0) { // HEART
            score += 1;
        } else if (_cardsSuite[index] == 1 && _cardsRank[index] == 10)  {   // SPADE AND QUEEN
            score += 13;
        }
    }
    return score;
}

static void UpdateScoreTable(int* _trickTableScore, int _loserIndex, int _score) {

    _trickTableScore[_loserIndex] += _score;
}

static int CheckWhoTakesCards(Vector* _table, int _startingPlayer) {


    int index = 0, max, maxIndex;
    int size = VectorSize(_table);
    Card* card;
    Suite firstSuite;

    VectorGet(_table, index, (void**)&card);

    firstSuite = card->m_suite;
    max = card->m_rank;
    maxIndex = _startingPlayer;

    for(index = 1; index < size; ++index) {
        VectorGet(_table, index, (void**)&card);

        if(firstSuite == card->m_suite && card->m_rank > max) {
            max = card->m_rank;
            maxIndex = index;
        }
    }

    return maxIndex;
}

static int IsGameOver(int* _scoreTable, int size) {

    int index;

    for(index = 0; index < size; ++index) {
        if(_scoreTable[index] >= LIMIT_SCORE) {
            return 1;
        }
    }
    return 0;
}

static int CheckWinner(int* _scoreTable, int size) {

    int index, min = _scoreTable[0], minIndex = 0;

    for(index = 1; index < size; ++index) {
        if(_scoreTable[index] < min) {
            min = _scoreTable[index];
            minIndex = index;
        }
    }
    return minIndex;
}

static void UpdateMainTableScore(int* _score, int* _roundTableScore, int _size) {


    int index;

   for(index = 0; index < _size; ++index) {
    _score[index] = _roundTableScore[index];
   }
}

static Context* ContextCreate() {

    Context* context = (Context*)malloc(sizeof(Context));

    if(context == NULL) {
        return NULL;
    }

    context->m_wasHeart = false;

    return context;
}