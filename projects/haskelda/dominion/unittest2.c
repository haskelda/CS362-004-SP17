/* 
-----------------------------------------------------------------------
unittest2.c
testing shuffle()


int shuffle(int player, struct gameState *state) {
 

  int newDeck[MAX_DECK];
  int newDeckPos = 0;
  int card;
  int i;

  if (state->deckCount[player] < 1)
    return -1;
  qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare); 
  // SORT CARDS IN DECK TO ENSURE DETERMINISM! 

  while (state->deckCount[player] > 0) {
    card = floor(Random() * state->deckCount[player]);
    newDeck[newDeckPos] = state->deck[player][card];
    newDeckPos++;
    for (i = card; i < state->deckCount[player]-1; i++) {
      state->deck[player][i] = state->deck[player][i+1];
    }
    state->deckCount[player]--;
  }
  for (i = 0; i < newDeckPos; i++) {
    state->deck[player][i] = newDeck[i];
    state->deckCount[player]++;
  }

  return 0;
}
-----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> // not using assert
#include "rngs.h"


#define VERBOSE_TEST 1	// set to 0 to remove printfs of individual TEST PASSED / TEST FAILED from asserttrue()

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
	initializeGame(numPlayers, k, seed, &G);

	// begin testing
	printf("\n\nThis is unittest2.c: testing the function shuffle():\n");

	/*
	Tests for shuffle() will be:
	1) the player's deck is not empty when shuffle() is called
	2) the amount of cards in the deck remain the same after shuffling.  Test for deck size = 1, MAX_DECK
	3) nothing else in the game state changes after shuffling
	4) player's other card counts do not change after shuffling
	*/

	/********************************************* 1) - deck is empty / not empty *************************************/
	G.deckCount[thisPlayer] = 0; 
	asserttrue(-1 == shuffle(thisPlayer, &G), "shuffle() returns -1 when player's deck is empty");
	G.deckCount[thisPlayer] = 1; 
	asserttrue(0 == shuffle(thisPlayer, &G), "shuffle() returns 0 when player's deck has one card");
	G.deckCount[thisPlayer] = MAX_DECK; 
	asserttrue(0 == shuffle(thisPlayer, &G), "shuffle() returns 0 when player's deck is MAX_DECK");



	/***************************** 2) the amount of cards in the deck remains the same after shuffling *************************/
	G.deckCount[thisPlayer] = 1; 
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
	shuffle(thisPlayer, &G);
	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "deck size = 1 doesn't change after shuffle()");

	G.deckCount[thisPlayer] = MAX_DECK; 
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
	shuffle(thisPlayer, &G);
	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], "deck size = MAX_DECK doesn't change after shuffle()");



	/************************* 3) nothing else in the general game state changes after shuffling  ******************************/
	G.deckCount[thisPlayer] = 17; // arbitrary number 
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
	shuffle(thisPlayer, &G);
	asserttrue(testG.numPlayers == G.numPlayers 
  				&& testG.outpostPlayed == G.outpostPlayed
  				&& testG.outpostTurn == G.outpostTurn
  				&& testG.whoseTurn == G.whoseTurn
  				&& testG.phase == G.phase
  				&& testG.numActions == G.numActions 
 				&& testG.coins == G.coins 
				&& testG.numBuys == G.numBuys, "general game state does not change after shuffle()");


/********************************** 4) player's other card counts do not change after shuffling  ******************************/
	asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer]
				&& testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]
				&& testG.playedCardCount == G.playedCardCount, "player's other card counts do not change after shuffle()");
/*
Other tests to consider:

other players card counts does not change
the order of the other players' decks do not change
the order of the player's deck does change (actual shuffle happens)
the same cards remain in the player's hand
the same cards remain in the player's deck

*/

	if (testFlag == 1)
	{
		printf("ALL TESTS PASSED for unittest2.c: shuffle()\n\n");
	}else {
		printf("TEST FAILURE for unittest2.c: shuffle():\n\n");
	}

    return 0;
}