/* -----------------------------------------------------------------------
 * cardtest4.c
 * testing cardVillage(); as refactored by amegany:

int cardVillage(struct gameState *state,  int currentPlayer, int handPos){
	//+1 Card
	drawCard(currentPlayer, state);		
	//+2 Actions
	state->numActions = state->numActions + 3;
	//discard played card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
}

card text: 		 +1 Card 	
				+2 Actions

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
	printf("This is cardtest4.c: testing amegany cardVillage():\n");

	/* 
	tests for cardVillage() will be:
	1) player's deckcount decreases by exactly 1
	2) player's handCount remains the same (draw one and play village)
	3) number of actions increases by exactly 2
	4) player's playCardCount increases by exactly 1
	5) village is the top card in the playedCards pile

	*/

	int i; // iterator
/****************************************   all tests performed with one call to cardVillage() **************************************/
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
	printf("\nplayedCards:\t");
	for (i = 0; i < G.playedCardCount; ++i)
	{
		printf("%d\t", G.playedCards[i]);
	}
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.discard[thisPlayer][i]);
	}
	printf("\n");
	#endif

	cardVillage(&G, thisPlayer, G.handCount[thisPlayer] - 1); //play village

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
	printf("\nplayedCards:\t");
	for (i = 0; i < G.playedCardCount; ++i)
	{
		printf("%d\t", G.playedCards[i]);
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
	asserttrue(testG.playedCardCount == G.playedCardCount - 1, "player's playedCardCount increases by exactly 1");

	/************************************************   5) village is the top card in the playedCards pile  *****************************************/
	asserttrue(G.playedCards[G.playedCardCount - 1] == village, "village is the top card in the playedCards pile");

	/*
	Other tests to consider:

	other players' card counts remain the same
	I could really use a ham and cheese sandwich about now
	*/


	if (testFlag == 1)
	{
		printf("\nALL TESTS PASSED for cardtest4.c: amegany cardVillage()\n\n");
	}else {
		printf("\nOVERALL TEST FAILURE for cardtest4.c: amegany cardVillage()\n\n");
	}

    return 0;
}