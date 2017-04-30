/* 
-----------------------------------------------------------------------
 unittest4.c
 testing scoreFor()


int scoreFor (int player, struct gameState *state) {

  int i;
  int score = 0;
  //score from hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == curse) { score = score - 1; };
      if (state->hand[player][i] == estate) { score = score + 1; };
      if (state->hand[player][i] == duchy) { score = score + 3; };
      if (state->hand[player][i] == province) { score = score + 6; };
      if (state->hand[player][i] == great_hall) { score = score + 1; };
      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };  // BUG!!!!
    }

  //score from discard
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == curse) { score = score - 1; };
      if (state->discard[player][i] == estate) { score = score + 1; };
      if (state->discard[player][i] == duchy) { score = score + 3; };
      if (state->discard[player][i] == province) { score = score + 6; };
      if (state->discard[player][i] == great_hall) { score = score + 1; };
      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };  // BUG!!!!
    }

  //score from deck
  for (i = 0; i < state->discardCount[player]; i++)  // BUG!!!!
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };  // BUG!!!!
    }

  return score;
}
-----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> // not using assert
#include "rngs.h"


#define VERBOSE_TEST 1	// set to 0 to remove printfs TEST PASSED / TEST FAILED from asserttrue()
#define TRACERS 1

// global vars
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

	// initialize a game state and player cards
	

	// begin testing
	printf("\n\nThis is unittest4.c: testing scoreFor():\n");


	/* 
	tests for scoreFor() will be:
	1) adding one of each specific victory cards to the player's deck, except for gardens
	2) adding one of each specific victory cards to the player's hand, except for gardens
	3) adding one of each specific victory cards to the player's discard, except for gardens
	4) adding 9 arbitrary kingdom cards and one gardens card to the player's deck
	5) adding 9 arbitrary kingdom cards and one gardens card to the player's hand
	6) adding 9 arbitrary kingdom cards and one gardens card to the player's discard
	*/

	int i; // iterator
/****************************************   1) adding one of each specific victory cards to the player's deck, except for gardens  *********************/
	initializeGame(numPlayers, k, seed, &G);
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

	G.deck[thisPlayer][G.deckCount[thisPlayer]] = estate;
	G.deckCount[thisPlayer]++;
	G.deck[thisPlayer][G.deckCount[thisPlayer]] = duchy;
	G.deckCount[thisPlayer]++;
	G.deck[thisPlayer][G.deckCount[thisPlayer]] = province;
	G.deckCount[thisPlayer]++;
	G.deck[thisPlayer][G.deckCount[thisPlayer]] = curse;
	G.deckCount[thisPlayer]++;
	G.deck[thisPlayer][G.deckCount[thisPlayer]] = great_hall;
	G.deckCount[thisPlayer]++;

	#if (TRACERS == 1)
	printf("player cards after test:\ndeck:\t");
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

	asserttrue(scoreFor(thisPlayer, &G) == scoreFor(thisPlayer, &testG) + 10, "adding one of each specific victory cards to the player's deck, except for gardens");// 1+3+6-1+1 = 10

	#if (TRACERS == 1)
		printf("Score after test:%d  Score initial:%d \n", scoreFor(thisPlayer, &G), scoreFor(thisPlayer, &testG));
	#endif


/****************************************  2) adding one of each specific victory cards to the player's hand, except for gardens  *********************/
	initializeGame(numPlayers, k, seed, &G);
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

	G.hand[thisPlayer][G.handCount[thisPlayer]] = estate; 
	G.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = duchy;
	G.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = province;
	G.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = curse;
	G.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = great_hall;
	G.handCount[thisPlayer]++;

	#if (TRACERS == 1)
	printf("player cards after test:\ndeck:\t");
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

	asserttrue(scoreFor(thisPlayer, &G) == scoreFor(thisPlayer, &testG) + 10, "adding one of each specific victory cards to the player's hand, except for gardens");

	#if (TRACERS == 1)
		printf("Score after test:%d  Score initial:%d \n", scoreFor(thisPlayer, &G), scoreFor(thisPlayer, &testG));
	#endif


/****************************************  3) adding one of each specific victory cards to the player's discard, except for gardens  *********************/
	initializeGame(numPlayers, k, seed, &G);
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

	G.discard[thisPlayer][G.discardCount[thisPlayer]] = estate; 
	G.discardCount[thisPlayer]++;
	G.discard[thisPlayer][G.discardCount[thisPlayer]] = duchy;
	G.discardCount[thisPlayer]++;
	G.discard[thisPlayer][G.discardCount[thisPlayer]] = province;
	G.discardCount[thisPlayer]++;
	G.discard[thisPlayer][G.discardCount[thisPlayer]] = curse;
	G.discardCount[thisPlayer]++;
	G.discard[thisPlayer][G.discardCount[thisPlayer]] = great_hall;
	G.discardCount[thisPlayer]++;

	#if (TRACERS == 1)
	printf("player cards after test:\ndeck:\t");
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

	asserttrue(scoreFor(thisPlayer, &G) == scoreFor(thisPlayer, &testG) + 10, "adding one of each specific victory cards to the player's discard, except for gardens");

	#if (TRACERS == 1)
		printf("Score after test:%d  Score initial:%d \n", scoreFor(thisPlayer, &G), scoreFor(thisPlayer, &testG));
	#endif

/****************************************	4) adding 9 arbitrary kingdom cards and one gardens card to the player's deck   *********************/
	initializeGame(numPlayers, k, seed, &G);
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

	for (i = 0; i < 9; ++i)
	{
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = smithy; // smithy is arbitrary
		G.deckCount[thisPlayer]++;
	}
	G.deck[thisPlayer][G.deckCount[thisPlayer]] = gardens;
	G.deckCount[thisPlayer]++;

	asserttrue(scoreFor(thisPlayer, &G) == scoreFor(thisPlayer, &testG) + 10, "adding 9 arbitrary kingdom cards and one gardens card to the player's deck");

	#if (TRACERS == 1)
	printf("player cards after test:\ndeck:\t");
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

	#if (TRACERS == 1)
		printf("Score after test:%d  Score initial:%d \n", scoreFor(thisPlayer, &G), scoreFor(thisPlayer, &testG));
	#endif


/****************************************	5) adding 9 arbitrary kingdom cards and one gardens card to the player's hand    *********************/
	initializeGame(numPlayers, k, seed, &G);
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

	for (i = 0; i < 9; ++i)
	{
		G.hand[thisPlayer][G.handCount[thisPlayer]] = smithy; // smithy is arbitrary
		G.handCount[thisPlayer]++;
	}
	G.hand[thisPlayer][G.handCount[thisPlayer]] = gardens;
	G.handCount[thisPlayer]++;

	asserttrue(scoreFor(thisPlayer, &G) == scoreFor(thisPlayer, &testG) + 10, "adding 9 arbitrary kingdom cards and one gardens card to the player's hand");

	#if (TRACERS == 1)
	printf("player cards after test:\ndeck:\t");
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

	#if (TRACERS == 1)
		printf("Score after test:%d  Score initial:%d \n", scoreFor(thisPlayer, &G), scoreFor(thisPlayer, &testG));
	#endif


/****************************************	6) adding 9 arbitrary kingdom cards and one gardens card to the player's discard    *********************/
	initializeGame(numPlayers, k, seed, &G);
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

	for (i = 0; i < 9; ++i)
	{
		G.discard[thisPlayer][G.discardCount[thisPlayer]] = smithy; // smithy is arbitrary
		G.discardCount[thisPlayer]++;
	}
	G.discard[thisPlayer][G.discardCount[thisPlayer]] = gardens;
	G.discardCount[thisPlayer]++;

	#if (TRACERS == 1)
	printf("player cards after test:\ndeck:\t");
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
	
	asserttrue(scoreFor(thisPlayer, &G) == scoreFor(thisPlayer, &testG) + 10, "adding 9 arbitrary kingdom cards and one gardens card to the player's discard");

	#if (TRACERS == 1)
		printf("Score after test:%d  Score initial:%d \n", scoreFor(thisPlayer, &G), scoreFor(thisPlayer, &testG));
	#endif



	/* other tests to consider:
	all cards in the hand, deck, discard are accounted for
	thisPlayer scores aren't transferred to or affect other players' scores
	*/



	if (testFlag == 1)
	{
		printf("ALL TESTS PASSED\n");
	}else {
		printf("TEST FAILURE for unittest4.c: scoreFor():\n\n");
	}

    return 0;
}