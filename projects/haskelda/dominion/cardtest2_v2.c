/* -----------------------------------------------------------------------
 * cardtest2_v2.c
 * testing cardEffect_Adventurer()

int cardEffect_Adventurer(struct gameState *state)
{
  int currentPlayer = whoseTurn(state);
  int temphand[MAX_HAND];
  int drawntreasure=0;
  int cardDrawn;
  int z = 0; // this is the counter for the temp hand
  while(drawntreasure < 2){
    if (state->deckCount[currentPlayer] < 2){ //if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  return 0;
}
 
  
 card text:
 "Reveal cards from your deck until you reveal 2 Treasure cards. 
 Put those Treasure cards into your hand and discard the other revealed cards."

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
	printf("This is cardtest2_v2.c: testing cardEffect_Adventurer():\n");

	/* 
	tests for cardAdventurer() will be:
	1) player's deckCount decreases by at least 2
	2) player's handCount increases by exactly 1 (gain 2 treasures, play adventurer)
	3) playedCardCount increases by 1
	4) adventurer is the top card in the playedCards pile
	5) player's discard pile increases by 2 less than amount that the deck decreases
	*/

	int i; // iterator
/****************************************   all tests performed with one call to cardEffect_Smithy  **************************************/
	initializeGame(numPlayers, k, seed, &G);
	G.hand[thisPlayer][G.handCount[thisPlayer]] = adventurer; // adding adventurer to hand
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
	printf("\ndiscard:\t");
	for (i = 0; i < G.discardCount[thisPlayer]; ++i)
	{
		printf("%d\t", G.discard[thisPlayer][i]);
	}
	printf("\n");
	#endif


	cardEffect_Adventurer(&G, G.handCount[thisPlayer] - 1); //play adventurer

	#if (TRACERS == 1)
	printf("Player cards after playing adventurer:\ndeck:\t");
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
	
	// 1) player's deckCount decreases by at least 2 after playing adventurer
	asserttrue(testG.deckCount[thisPlayer] >= G.deckCount[thisPlayer] + 2, "player's deckCount decreases by at least 2");
	
	// 2) player's handCount increases by 1 after playing adventurer
	asserttrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1, "player's handCount increases by exactly 1");

	// 3) player's playedCardCount increases by 1
	asserttrue(testG.playedCardCount == G.playedCardCount - 1, "player's playedCardCount increases by exactly 1");

	// 4) adventurer is the top card in the playedCards pile
	asserttrue(G.playedCards[G.playedCardCount - 1] == adventurer, "adventurer is the top card in the playedCards pile");

	// 5) player's discard pile increases by 2 less than amount that the deck decreases
	int deckCountDecrease = testG.deckCount[thisPlayer] - G.deckCount[thisPlayer];
	asserttrue(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] - (deckCountDecrease - 2), "player's discard pile increases by 2 less than amount that the deck decreases");

	/*
	Other tests to consider:

	other players card counts do not change
	the same other cards remain in the player's hand
	adventurer is removed from the player's hand
	the same cards that were removed from the deck ended up in the discard (except for the treasures)
	*/


	if (testFlag == 1)
	{
		printf("\nALL TESTS PASSED for cardtest2_v2.c: cardEffect_Adventurer()\n\n");
	}else {
		printf("\nOVERALL TEST FAILURE for cardtest2_v2.c: cardEffect_Adventurer()\n\n");
	}

    return 0;
}