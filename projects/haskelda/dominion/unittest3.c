/* 
-----------------------------------------------------------------------
unittest3.c
testing fullDeckCount() which returns the frequency(count) of a specific card that is present in 
the player's deck, hand, and discard.  It is used for scoring at the end of the game.


 int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
   These are how the specific cards are numbered:

   enum CARD
  {curse = 0,
   estate,
   duchy,
   province,

   copper, //4
   silver,
   gold,

   adventurer, //7

   council_room, //8
   feast, 
   gardens,
   mine, 
   remodel,
   smithy,
   village,

   baron,  //15
   great_hall,
   minion, 
   steward, 
   tribute,

   ambassador,  //20
   cutpurse,
   embargo, 
   outpost,
   salvager, 
   sea_hag,
   treasure_map
  };
 -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> // not using assert
#include "rngs.h"


#define VERBOSE_TEST 1	// set to 0 to remove printfs of individual TEST PASSED / TEST FAILED from asserttrue()
#define TRACERS 0 // for tracing/testing this code

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
			sea_hag, tribute, smithy, council_room}; // these are arbitrarily chosen for this test

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// begin testing
	printf("\n\nThis is unittest3.c: testing fullDeckCount():\n");


	#if (TRACERS == 1)
	printf("Initial player cards:\ndeck:\t");
	int i;
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

	/* 
	tests for fullDeckCount will be:
	1) adding one specific card to the player's deck.
	2) adding one specific card to the player's hand.
	3) adding one specific card to the player's dicard.
	*/


	/********************************************* 1) adding one specific card to the player's deck  *************************************/
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
	G.deck[thisPlayer][G.deckCount[thisPlayer]] = 1; // adding another estate to deck
	G.deckCount[thisPlayer]++;
	asserttrue(fullDeckCount(thisPlayer, 1, &G) == fullDeckCount(thisPlayer, 1, &testG) + 1 , "added one estate to deck");

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

	/******************************************  2) adding one specific card to the player's hand **********************************/
	G.hand[thisPlayer][G.handCount[thisPlayer]] = 7; // adding adventurer to hand
	G.handCount[thisPlayer]++;
	asserttrue(fullDeckCount(thisPlayer, 7, &G) == fullDeckCount(thisPlayer, 7, &testG) + 1 , "added one adventurer to hand");

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


	/******************************************  3) adding one specific card to the player's dicard **********************************/
	G.discard[thisPlayer][G.discardCount[thisPlayer]] = 0; // adding curse to discard
	G.discardCount[thisPlayer]++;
	asserttrue(fullDeckCount(thisPlayer, 0, &G) == fullDeckCount(thisPlayer, 0, &testG) + 1 , "added one curse to discard");

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




	if (testFlag == 1)
	{
		printf("ALL TESTS PASSED for unittest3.c: fullDeckCount()\n\n");
	}else {
		printf("TEST FAILURE for unittest3.c: fullDeckCount()\n\n");
	}

    return 0;
}