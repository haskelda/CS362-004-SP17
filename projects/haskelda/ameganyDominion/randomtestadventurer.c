/* -----------------------------------------------------------------------
randomtestadventurer.c
testing cardAdventurer(); as refactored by amegany:

int cardAdventurer(struct gameState *state,  int currentPlayer,  int temphand[MAX_HAND]){
  int drawntreasure=0;
  int cardDrawn;
  int z = 0;
  while(drawntreasure<2){
    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-2];
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
      drawntreasure++;
    }
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
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


#define VERBOSE_TEST 1	// 1 = ON, 0 = OFF. printfs of expected results from output
#define TRACERS 1 // 1 = ON, 0 = OFF. For displaying actual cards in players' deck, hand, playedCards, discard

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


int test_cardAdventurer(int thisPlayer, struct gameState *G){
  // copy the game state to a test case
  struct gameState testG;
  memcpy(&testG, G, sizeof(struct gameState)); 

  int i;
  #if (TRACERS == 1)
    printf("Player cards before call to cardAdventurer():\ndeck: (%d):\t", G->deckCount[thisPlayer]);
    for (i = 0; i < G->deckCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->deck[thisPlayer][i]);
    }
    printf("\nhand: (%d):\t", G->handCount[thisPlayer]);
    for (i = 0; i < G->handCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->hand[thisPlayer][i]);
    }
    printf("\nplayedCards: (%d):\t", G->playedCardCount);
    for (i = 0; i < G->playedCardCount; ++i)
    {
      printf("%d\t", G->playedCards[i]);
    }
    printf("\ndiscard: (%d):\t", G->discardCount[thisPlayer]);
    for (i = 0; i < G->discardCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->discard[thisPlayer][i]);
    }
    printf("\n");
  #endif 


  // Call cardEffect_Adventurer with the original gameState.  
  // This *should* have the same effect as what was changed manually, above.


  /* The function cardAdventurer takes an array of MAX_HAND ints as its third argument.  
  This is used in the function as a temporary array, only within the scope of the function itself.  
  It is unnecessary to pass the array into the function as an argument. 
  It should be declared and used within the function only 
  */

  int unnecessaryArray[MAX_HAND];
  cardAdventurer(G, thisPlayer, unnecessaryArray);


  // manually change the test case vars according to the chosen tests:
  /* 
  tests for cardEffect_Adventurer will be:
  1) player's deckCount decreases by at least 2
  2) player's handCount increases by exactly 1 (gain 2 treasures, play adventurer)
  3) playedCardCount increases by 1
  4) adventurer is the top card in the playedCards pile
  5) player's discard pile increases by 2 less than amount that the deck decreases
  */

  int deckCountDecrease = testG.deckCount[thisPlayer] - G->deckCount[thisPlayer]; // for use in test 5
  
  // 1) player's deckCount decreases by at least 2
  testG.deckCount[thisPlayer] = testG.deckCount[thisPlayer] - 2;
  // 2) player's handCount increases by exactly 1 (gain 2 treasures, play adventurer)
  testG.handCount[thisPlayer]++;
  // 3) playedCardCount increases by 1
  testG.playedCardCount++;
  // 4) adventurer is the top card in the playedCards pile
  testG.playedCards[testG.playedCardCount-1] = adventurer;
  // 5) player's discard pile increases by 2 less than amount that the deck decreases
  testG.discardCount[thisPlayer] = testG.discardCount[thisPlayer] + (deckCountDecrease - 2);


  #if (TRACERS == 1)
    printf("test Player cards after changing manually:\ndeck: (%d):\t", testG.deckCount[thisPlayer]);
    for (i = 0; i < testG.deckCount[thisPlayer]; ++i)
    {
      printf("%d\t", testG.deck[thisPlayer][i]);
    }
    printf("\nhand: (%d):\t", testG.handCount[thisPlayer]);
    for (i = 0; i < testG.handCount[thisPlayer]; ++i)
    {
      printf("%d\t", testG.hand[thisPlayer][i]);
    }
    printf("\nplayedCards (%d):\t", testG.playedCardCount);
    for (i = 0; i < testG.playedCardCount; ++i)
    {
      printf("%d\t", testG.playedCards[i]);
    }
    printf("\ndiscard: (%d):\t", testG.discardCount[thisPlayer]);
    for (i = 0; i < testG.discardCount[thisPlayer]; ++i)
    {
      printf("%d\t", testG.discard[thisPlayer][i]);
    }
    printf("\n");
  #endif 


  #if (TRACERS == 1)
    printf("Player cards after call to cardAdventurer():\ndeck: (%d):\t", G->deckCount[thisPlayer]);
    for (i = 0; i < G->deckCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->deck[thisPlayer][i]);
    }
    printf("\nhand: (%d):\t", G->handCount[thisPlayer]);
    for (i = 0; i < G->handCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->hand[thisPlayer][i]);
    }
    printf("\nplayedCards: (%d):\t", G->playedCardCount);
    for (i = 0; i < G->playedCardCount; ++i)
    {
      printf("%d\t", G->playedCards[i]);
    }
    printf("\ndiscard: (%d):\t", G->discardCount[thisPlayer]);
    for (i = 0; i < G->discardCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->discard[thisPlayer][i]);
    }
    printf("\n");
  #endif 


  // compare the manually changed testG gameState with the gameState G after the call to cardEffect_Adventurer

  // 1) player's deckCount decreases by at least 2 after playing adventurer
  asserttrue(testG.deckCount[thisPlayer] >= G->deckCount[thisPlayer], "player's deckCount decreases by at least 2 after playing adventurer");
  
  // 2) player's handCount increases by exactly 1 after playing adventurer
  asserttrue(testG.handCount[thisPlayer] == G->handCount[thisPlayer], "player's handCount increases by 1 after playing adventurer");

  // 3) player's playedCardCount increases by 1
  asserttrue(testG.playedCardCount == G->playedCardCount, "player's playedCardCount increases by exactly 1");

  // 4) adventurer is the top card in the playedCards pile
  asserttrue(G->playedCards[G->playedCardCount - 1] == adventurer, "adventurer is the top card in the playedCards pile");

  // 5) player's discard pile increases by 2 less than amount that the deck decreases
  asserttrue(testG.discardCount[thisPlayer] == G->discardCount[thisPlayer], "player's discard pile increases by 2 less than amount that the deck decreases");

  /*
  Other tests to consider:
    other players card counts do not change
    the same other cards remain in the player's hand
    adventurer is removed from the player's hand

  Other tests can also involve location of specific cards.
  But testing these specific changes would require a similar amount of code that we are testing, which would be just as prone to error as the code itself
  These tests can be acheived by turning on TRACERS and manually observing the output:

    the player's hand contains two additional treasure cards
    the same cards that were removed from the deck ended up in the discard (except for the treasures)
  */
  return 0;
} // end test_cardAdventurer





int main() {
	// initial vars
  struct gameState G;
  int thisPlayer;

  printf("This is randomtestadventurer.c: testing amegany cardAdventurer():\n"); 

  // set up random gameState and other relevant variables
  SelectStream(2);
  PutSeed(3);

  int n; // iterator for number of test runs
  int p; // iterator for player
  int i; // all-purpose iterator
  for (n = 0; n < 10; n++) {
    // fill four different players' deck, hand, and discard with a random amount of random cards. 
    for (p = 0; p < 4; ++p){
      G.deckCount[p] = floor(Random() * 30);
      for (i = 0; i < G.deckCount[p]; ++i)
      {
        G.deck[p][i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
      G.handCount[p] = floor(Random() * 10);  // big enough for realistic game situations
      for (i = 0; i < G.handCount[p]; ++i)
      {
        G.hand[p][i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
      G.playedCardCount = floor(Random() * 5); // big enough for realistic game situations
      for (i = 0; i < G.playedCardCount; ++i)
      {
        G.playedCards[i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
      G.discardCount[p] = floor(Random() * (50));  // leave enough room for increase due to card action
      for (i = 0; i < G.discardCount[p]; ++i)
      {
        G.discard[p][i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
    } // p
    thisPlayer = floor(Random() * 4); // 0-3, four players is max
    G.hand[thisPlayer][G.handCount[thisPlayer]] = adventurer; // adding adventurer (7) to hand
    G.handCount[thisPlayer]++;
    #if (VERBOSE_TEST == 1)
      printf("\n\nTest number %d\tplayer: %d\tdeckCount: %d\thandCount: %d\tplayedCardCount: %d\tdiscardCount: %d\n", n, thisPlayer, G.deckCount[thisPlayer], G.handCount[thisPlayer], G.playedCardCount, G.discardCount[thisPlayer]);
    #endif
    test_cardAdventurer(thisPlayer, &G);
  } // n


  if (testFlag == 1)
  {
    printf("\nALL TESTS PASSED for randomtestadventurer.c: amegany cardAdventurer()\n\n");
  }else {
    printf("\nOVERALL TEST FAILURE for randomtestadventurer.c: amegany cardAdventurer()\n\n");
  }
  return 0;
} // end main