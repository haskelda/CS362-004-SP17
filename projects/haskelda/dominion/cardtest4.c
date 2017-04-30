/* -----------------------------------------------------------------------
 * cardtest4.c
 * testing cardEffect_Village

int cardEffect_Village(struct gameState *state, int handPos)
{
  int currentPlayer = whoseTurn(state);

        //+1 Card
      drawCard(currentPlayer, state);
      
      //+2 Actions
      state->numActions = state->numActions + 2;
      
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 1);
      return 0;
}

 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h> // not using assert
#include "rngs.h"


#define VERBOSE_TEST 1	// set to 0 to remove printfs of expected results from output
#define TRACERS 1 // for tracing/testing this code

int testFlag = 1; // 1 = all tests passed thus far, 0 = at least one test failed.  For final printf statement

void asserttrue(int r, char* testDescription){
	if (r == 1)
	{
		#if (VERBOSE_TEST == 1)
			printf("TEST PASSED: %s\n", testDescription); 
		#endif  
	}
	if (r != 1)
	{
		#if (VERBOSE_TEST == 1)
			printf("TEST FAILED: %s\n", testDescription);
		#endif
		testFlag = 0;  // for final printf statement
	}
}



int main() {
	// initial vars
	int seed = 1000; 
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; // these do not matter for this test
	printf("This is cardtest4.c: testing cardEffect_Village:\n");

	/* 
	tests for cardEffect_Village will be:
	1) player's deckcount decreases by exactly 1
	2) player's handCount remains the same (draw one and discard village)
	3) number of actions increases by exactly 2
	4) player's discardCount increases by 1

	*/

	int i; // iterator
/****************************************   all tests performed with one call to cardEffect_Village **************************************/
	initializeGame(numPlayers, k, seed, &G);
	G.hand[thisPlayer][G.handCount[thisPlayer]] = village; // adding village to hand
	G.handCount[thisPlayer]++;
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case

	#if (TRACERS == 1)
	printf("Initial player cards:\ndeck:\t");
	for (i = 0; i < G.deckCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.deck[thisPlayer][i]);
	}
	printf("\nhand:\t");
	for (i = 0; i < G.handCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.hand[thisPlayer][i]);
	}
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.discard[thisPlayer][i]);
	}
	printf("\n");
	#endif

	cardEffect_Village(&G, G.handCount[thisPlayer] - 1); //play village

	#if (TRACERS == 1)
	printf("player cards after playing village:\ndeck:\t");
	for (i = 0; i < G.deckCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.deck[thisPlayer][i]);
	}
	printf("\nhand:\t");
	for (i = 0; i < G.handCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.hand[thisPlayer][i]);
	}
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.discard[thisPlayer][i]);
	}
	printf("\n");
	#endif	

	/************************************************	1) player's deckcount decreases by exactly 1 ********************************************/
	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + 1, "player's deckCount decreases by exactly 1");

	/************************************************	2) player's handCount remains the same (draw one and discard village) *******************/
	asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer], "player's handCount remains the same");

	/************************************************	3) number of actions increases by exactly 2 ********************************************/
	asserttrue(testG.numActions == G.numActions -2, "number of actions increases by exactly 2");

	/************************************************	4) player's discardCount increases by exactly 1 ************************************************/
	asserttrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] - 1, "player's discardCount increases by exactly 1");

	/*
	Other tests to consider:

	other players' card counts remain the same
	village is in the player's discard
	I could really use a ham and cheese sandwich about now
	*/


	if (testFlag == 1)
	{
		printf("ALL TESTS PASSED\n");
	}else {
		printf("TEST FAILURE for cardtest4.c: cardEffect_Village\n\n");
	}

    return 0;
}