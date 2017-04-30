/* -----------------------------------------------------------------------
 * cardtest3.c
 * testing cardEffect_SeaHag

int cardEffect_SeaHag(struct gameState *state)
{
  int i;
  int currentPlayer = whoseTurn(state);

  for (i = 0; i < state->numPlayers; i++){
    if (i != currentPlayer){
      state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];
      state->deckCount[i]--;
      state->discardCount[i]++;
      state->deck[i][state->deckCount[i]--] = sea_hag;//Top card now a sea_hag
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
    int numPlayers = 3;
   // int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; // these do not matter for this test
	printf("This is cardtest3.c: testing cardEffect_SeaHag:\n");

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

	cardEffect_SeaHag(&G);

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

	player's card counts do not change
	the same other cards remain in the player's hand
	adventurer is removed from the player's hand
	the same cards that were removed from the deck ended up in the discard (except for the treasures)
	*/


	if (testFlag == 1)
	{
		printf("ALL TESTS PASSED\n");
	}else {
		printf("TEST FAILURE for cardtest3.c: cardEffect_SeaHag\n\n");
	}

    return 0;
}