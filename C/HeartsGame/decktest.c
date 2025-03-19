#include "deck.h"
#include "cards.h"
#include "player.h"
#include "game.h"
#include "../mutest/mu_test.h"

BEGIN_TEST(CreationDeckTest1)
	int numberOfDecks = 1;

    Deck* dptr;

    dptr = DeckCreate(numberOfDecks);

    ASSERT_THAT(dptr != NULL);
    
END_TEST

BEGIN_TEST(DestroyDeckTest1)

	int numberOfDecks = 1;

    Deck* dptr;

    dptr = DeckCreate(numberOfDecks);
    DeckDestroy(&dptr);

    ASSERT_THAT(dptr == NULL);

END_TEST

BEGIN_TEST(DeckShuffleTest1)

	int numberOfDecks = 1;

    Deck* dptr;

    dptr = DeckCreate(numberOfDecks);
	DeckShuffle(dptr);
    DeckDestroy(&dptr);

    ASSERT_THAT(dptr == NULL);

END_TEST

BEGIN_TEST(PlayerCreateTest1)

    Player* pptr;
	pptr = PlayerCreate(1, 1);

    ASSERT_THAT(pptr != NULL);
END_TEST

BEGIN_TEST(PlayerDestroyTest1)

    Player* pptr;
	pptr = PlayerCreate(1, 1);
	PlayerDestroy(&pptr);

    ASSERT_THAT(pptr == NULL);
END_TEST

BEGIN_TEST(GameCreateTest1)

    Game* gptr;
	gptr = GameCreate(1,3);

    ASSERT_THAT(gptr != NULL);
END_TEST

BEGIN_TEST(GameDestroyTest1)

    Game* gptr;
	gptr = GameCreate(1,3);
	GameDestroy(&gptr);

    ASSERT_THAT(gptr == NULL);
END_TEST


TEST_SUITE(DeckTests [inga ōhō: bad causes bring bad results])
	TEST(CreationDeckTest1)
	TEST(DestroyDeckTest1)
	TEST(DeckShuffleTest1)

	TEST(PlayerCreateTest1)
	TEST(PlayerDestroyTest1)

	TEST(GameCreateTest1)
	TEST(GameDestroyTest1)

	// TEST(add_operations)
	// TEST(abs_function)

	// TEST(empty_struct_is_not_empty)
	// TEST(work_with_strings)
	// TEST(access_null_ptr_will_seg)

	// TEST(test_should_fail)
	// TEST(test_should_pass)


	// TEST(test_with_no_assert_should_fail)

	// IGNORE_TEST(test_should_fail)
	// IGNORE_TEST(test_should_pass)

	// TEST(test_with_no_assert_should_fail)
END_SUITE