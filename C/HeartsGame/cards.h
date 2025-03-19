#ifndef __CARDS_H__
#define __CARDS_H__

#define RANK_AMOUNT 13

typedef enum Suite {
	_HEART = 0,
    _SPADE,
    _DIAMOND,
    _CLUB,
    NUM_OF_SUITE
}Suite;

typedef struct {
    int m_rank;
    Suite m_suite;
}Card;


#endif // __CARDS_H__