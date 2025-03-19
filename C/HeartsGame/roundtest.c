#include "deck.h"
#include "cards.h"
#include "player.h"
#include "game.h"
#include "round.h"
#include "../mutest/mu_test.h"


BEGIN_TEST(RoundCreateTest1)

	Game* gptr;
	gptr = GameCreate(1,3);

    Round* round = GetRound(gptr);

    ASSERT_THAT(round != NULL);
    
END_TEST

BEGIN_TEST(RoundRunTest1)

	Game* gptr;
	gptr = GameCreate(1,3);
	PlayGame(gptr);
	

    ASSERT_THAT(gptr != NULL);
    
END_TEST

TEST_SUITE(DeckTests [inga ōhō: bad causes bring bad results])
	TEST(RoundCreateTest1)
	TEST(RoundRunTest1)


END_SUITE