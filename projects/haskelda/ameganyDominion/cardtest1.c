/* -----------------------------------------------------------------------
 * cardtest1.c
 * testing cardSmithy(); as refactored by amegany:

int cardSmithy(struct gameState *state,  int currentPlayer, int handPos){
	int i;
	//+3 Cards
	for (i = 0; i <= 3; i++){
		drawCard(currentPlayer, state);
	}
	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}

 card text: "+3 Cards"

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
#define TRACERS 1 // for displaying the player's cards

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
	printf("This is cardtest1.c: testing amegany cardSmithy():\n");

	/* 
	tests for cardSmithy will be:
	1) player's deckCount decreases by 3
	2) player's handCount increases by 2 (draw 3 - playedCard smithy)
	3) player's playedCardCount increases by 1
	4) smithy is the top card in the playedCards pile
	*/

	int i; // iterator
/****************************************   all tests performed with one call to cardSmithy  **************************************/
	initializeGame(numPlayers, k, seed, &G);
	G.hand[thisPlayer][G.handCount[thisPlayer]] = smithy; // adding smithy to hand
	G.handCount[thisPlayer]++;
	G.playedCardCount = 0;
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
	printf("\nplayedCards:\t");
	for (i = 0; i < G.playedCardCount; ++i)
	{
		printf("%d\t", G.playedCards[i]);
	}
	printf("\n");
	#endif

	cardSmithy(&G, thisPlayer, G.handCount[thisPlayer] - 1); //play smithy

	#if (TRACERS == 1)
	printf("player cards after playing smithy:\ndeck:\t");
	for (i = 0; i < G.deckCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.deck[thisPlayer][i]);
	}
	printf("\nhand:\t");
	for (i = 0; i < G.handCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.hand[thisPlayer][i]);
	}
	printf("\nplayedCards:\t");
	for (i = 0; i < G.playedCardCount; ++i)
	{
		printf("%d\t", G.playedCards[i]);
	}
	printf("\n");
	#endif	
	
	// 1) player's deckCount decreases by 3
	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + 3, "player's deckCount decreases by 3 after playing smithy");
	
	// 2) player's handCount increases by 2 (draw 3 - play smithy)
	asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 2, "player's handCount increases by 2 after playing smithy");

	// 3) player's playedCards pile increases by 1 smithy
	asserttrue(testG.playedCardCount == G.playedCardCount - 1, "player's playedCardCount increases by 1 after playing smithy");

	// 4) smithy is the top card in the playedCards pile
	asserttrue(G.playedCards[G.playedCardCount - 1] == smithy, "smithy is the top card in the playedCards pile");


	/*
	Other tests to consider:

	other players card counts do not change
	the same other cards remain in the player's hand
	smithy is removed from the player's hand
	*/


	if (testFlag == 1)
	{
		printf("\nALL TESTS PASSED for cardtest1.c: cardSmithy()\n\n");
	}else {
		printf("\nOVERALL TEST FAILURE for cardtest1.c: cardSmithy()\n\n");
	}

    return 0;
}