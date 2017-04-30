/* -----------------------------------------------------------------------
 * cardtest1.c
 * testing smithy

 int cardEffect_Smithy(struct gameState *state, int handPos)
{
  int i;
  int currentPlayer = whoseTurn(state);
  //+3 Cards
  for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer + i, state);
  }
      
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
  return 0;
}

 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> // not using assert
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
	printf("This is cardtest1.c: testing cardEffect_Smithy:\n");

	/* 
	tests for cardEffect_Smithy will be:
	1) player's deckCount decreases by 3
	2) player's handCount increases by 2 (draw 3 - discard smithy)
	3) player's discard pile increases by 1 smithy
	*/

	int i; // iterator
/****************************************   all tests performed with one call to cardEffect_Smithy  **************************************/
	initializeGame(numPlayers, k, seed, &G);
	G.hand[thisPlayer][G.handCount[thisPlayer]] = smithy; // adding smithy to hand
	G.handCount[thisPlayer]++;
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
	
	#if (TRACERS == 1)
	//printf("whoseTurn: %d\n", G.whoseTurn);
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

	cardEffect_Smithy(&G, G.handCount[thisPlayer] - 1); //play smithy

	#if (TRACERS == 1)
	printf("player cards after plating smithy:\ndeck:\t");
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
	
	// 1) player's deckCount decreases by 3
	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + 3, "player's deckCount decreases by 3 after playing smithy");
	
	// 2) player's handCount increases by 2 (draw 3 - discard smithy)
	asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 2, "player's handCount increases by 2 after playing smithy");

	// 3) player's discard pile increases by 1 smithy
	asserttrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] - 1, "player's discardCount increases by 1 after playing smithy");


	/*
	Other tests to consider:

	other players card counts do not change
	the same other cards remain in the player's hand
	smithy is removed from the player's hand
	smithy is added to the player's discard
	*/


	if (testFlag == 1)
	{
		printf("ALL TESTS PASSED\n");
	}else {
		printf("TEST FAILURE for cardtest1.c: cardEffect_Smithy\n\n");
	}

    return 0;
}