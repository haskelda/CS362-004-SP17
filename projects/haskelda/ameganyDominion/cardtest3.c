/* -----------------------------------------------------------------------
 * cardtest3.c
 * testing cardSeaHag(); as refactored by amegany;

int cardSeaHag(struct gameState *state,  int currentPlayer){
	int i;
	for (i = 0; i < state->numPlayers; i++){
		if (i != currentPlayer){
			state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];			    
			state->deckCount[i]--;
			state->discardCount[i]++;
			state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
		}
	}
	return 0;
}

card text:

"Each other player discards the top card of his deck, then gains a Curse card, putting it on top of his deck."

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
#define TRACERS 1 // for displaying the players' cards

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
    int numPlayers = 3;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; // these do not matter for this test
	printf("This is cardtest3.c: testing amegany cardSeaHag():\n");

	/* 
	tests for cardEffect_SeaHag will be:
	1) each other player's top deck card will be moved to top of discard
	2) each other players' top deck card will be a curse
	*/

	int i; // iterator
	/****************************************   all tests performed with one call to cardEffect_SeaHag  **************************************/
	initializeGame(numPlayers, k, seed, &G);
	// set the top of the other players' decks
	G.deck[1][G.deckCount[1]] = mine; // mine is arbitrary. enum = 11
	G.deckCount[1]++;
	G.deck[2][G.deckCount[2]] = village; // village is arbitrary. enum = 14
	G.deckCount[2]++;

	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case

	#if (TRACERS == 1)
	printf("whoseTurn: %d\n", G.whoseTurn);
	printf("Initial player 1 cards:\ndeck:\t");
	for (i = 0; i < G.deckCount[1]; ++i)
	{
		printf("%d\t", G.deck[1][i]);
	}
	printf("\nhand:\t");
	for (i = 0; i < G.handCount[1]; ++i)
	{
		printf("%d\t", G.hand[1][i]);
	}
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[1]; ++i)
	{
		printf("%d\t", G.discard[1][i]);
	}
	printf("\n");
	#endif


	#if (TRACERS == 1)
	//printf("whoseTurn: %d\n", G.whoseTurn);
	printf("Initial player 2 cards:\ndeck:\t");
	for (i = 0; i < G.deckCount[2]; ++i)
	{
		printf("%d\t", G.deck[2][i]);
	}
	printf("\nhand:\t");
	for (i = 0; i < G.handCount[2]; ++i)
	{
		printf("%d\t", G.hand[2][i]);
	}
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[2]; ++i)
	{
		printf("%d\t", G.discard[2][i]);
	}
	printf("\n");
	#endif	

	cardSeaHag(&G, thisPlayer);

	#if (TRACERS == 1)
	//printf("whoseTurn: %d\n", G.whoseTurn);
	printf("Player 1 cards after sea_hag:\ndeck:\t");
	for (i = 0; i < G.deckCount[1]; ++i)
	{
		printf("%d\t", G.deck[1][i]);
	}
	printf("\nhand:\t");
	for (i = 0; i < G.handCount[1]; ++i)
	{
		printf("%d\t", G.hand[1][i]);
	}
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[1]; ++i)
	{
		printf("%d\t", G.discard[1][i]);
	}
	printf("\n");
	#endif


	#if (TRACERS == 1)
	//printf("whoseTurn: %d\n", G.whoseTurn);
	printf("Player 2 cards after sea_hag:\ndeck:\t");
	for (i = 0; i < G.deckCount[2]; ++i)
	{
		printf("%d\t", G.deck[2][i]);
	}
	printf("\nhand:\t");
	for (i = 0; i < G.handCount[2]; ++i)
	{
		printf("%d\t", G.hand[2][i]);
	}
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[2]; ++i)
	{
		printf("%d\t", G.discard[2][i]);
	}
	printf("\n");
	#endif	

	/************************************************	1) each other player's top deck card will be moved to top of discard *******************/
	asserttrue(G.discard[1][G.discardCount[1] + 1] == mine, "player 1 top deck card was moved to top of discard");
	asserttrue(G.discard[2][G.discardCount[2] + 1] == village, "player 2 top deck card was moved to top of discard");


	/************************************************* 	2) each other players' top deck card will be a curse  **********************************/
	asserttrue(G.deck[1][G.deckCount[1]] == curse, "player 1 top deck card is a curse");
	asserttrue(G.deck[2][G.deckCount[2]] == curse, "player 2 top deck card is a curse");

	/*
	Other tests to consider:

	other player(s)' discardCount increase by 1
	other player(s)' deckCount does not change
	player's deck and discard piles are unchanged
	sea_hag is the top card in the playedCards pile

	*/


	if (testFlag == 1)
	{
		printf("\nALL TESTS PASSED for cardtest3.c: amegany cardSeaHag()\n\n");
	}else {
		printf("\nTEST FAILURE for cardtest3.c: amegany cardSeaHag()\n\n");
	}

    return 0;
}