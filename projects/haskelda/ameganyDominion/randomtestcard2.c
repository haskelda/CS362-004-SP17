/* -----------------------------------------------------------------------
randomtestcard2.c
testing cardVillage() as refactored by amegany:

int cardVillage(struct gameState *state,  int currentPlayer, int handPos){
  //+1 Card
  drawCard(currentPlayer, state);   
  //+2 Actions
  state->numActions = state->numActions + 3;
  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}
  
 card text: "+1 Card   +2 Actions"

 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h> // not using assert
#include "rngs.h"


#define VERBOSE_TEST 1	// 1 = ON, 0 = OFF. printfs of expected results from output
#define TRACERS 1 // 1 = ON, 0 = OFF. For displaying actual cards in players' deck, hand, discard

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


int test_cardVillage(struct gameState *G, int handPos){
  // copy the game state to a test case
  struct gameState testG;
  memcpy(&testG, G, sizeof(struct gameState)); 

  //asserttrue(memcmp(&testG, G, sizeof(struct gameState)) == 0, "initial gamestates are equal");


  int i;
  #if (TRACERS == 1)
    printf("Player cards before call to cardVillage: (%d):\t", G->deckCount[G->whoseTurn]);
    for (i = 0; i < G->deckCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->deck[G->whoseTurn][i]);
    }
    printf("\nhand: (%d):\t", G->handCount[G->whoseTurn]);
    for (i = 0; i < G->handCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->hand[G->whoseTurn][i]);
    }
    printf("\nplayedCards: (%d):\t", G->playedCardCount);
    for (i = 0; i < G->playedCardCount; ++i)
    {
      printf("%d\t", G->playedCards[i]);
    }
    printf("\ndiscard: (%d):\t", G->discardCount[G->whoseTurn]);
    for (i = 0; i < G->discardCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->discard[G->whoseTurn][i]);
    }
    printf("\n");
  #endif 

  /* 
  tests for cardEffect_Village will be a direct memcmp of testG and G gamestates.
  this requires manually changing the following in the testG gamestate:
  1) the card that was on top of player's deck is on "top" of the player's hand
  2) player's deckcount decreases by exactly 1
  3) number of actions increases by exactly 2
  4) playedCardCount increases by 1
  5) village (14) is on top of playedCard pile
  ALL other gamestate vars remain unchanged (includeing the player's handcount)
  */

  testG.hand[testG.whoseTurn][testG.handCount[testG.whoseTurn]-1] = testG.deck[testG.whoseTurn][testG.deckCount[testG.whoseTurn]-1];
  testG.deckCount[testG.whoseTurn]--;
  testG.numActions = testG.numActions + 2;
  testG.playedCardCount++;
  testG.playedCards[testG.playedCardCount-1] = village;  // 14 is village.  See enum CARDS in dominion.h

  
  #if (TRACERS == 1)
    printf("test Player cards after changing manually:\ndeck: (%d):\t", testG.deckCount[testG.whoseTurn]);
    for (i = 0; i < testG.deckCount[testG.whoseTurn]; ++i)
    {
      printf("%d\t", testG.deck[testG.whoseTurn][i]);
    }
    printf("\nhand: (%d):\t", testG.handCount[testG.whoseTurn]);
    for (i = 0; i < testG.handCount[testG.whoseTurn]; ++i)
    {
      printf("%d\t", testG.hand[testG.whoseTurn][i]);
    }
    printf("\nplayedCards (%d):\t", testG.playedCardCount);
    for (i = 0; i < testG.playedCardCount; ++i)
    {
      printf("%d\t", testG.playedCards[i]);
    }
    printf("\ndiscard: (%d):\t", testG.discardCount[testG.whoseTurn]);
    for (i = 0; i < testG.discardCount[testG.whoseTurn]; ++i)
    {
      printf("%d\t", testG.discard[testG.whoseTurn][i]);
    }
    printf("\n");
  #endif    

  // Call cardVillage() with the original gameState.  
  // This *should* have the same effect as what was changed manually, above.
  cardVillage(G, G->whoseTurn, handPos); // handPos is G->handCount[G->whoseTurn] - 1 (from main)

  #if (TRACERS == 1)
    printf("Player cards after call to cardVillage():\ndeck: (%d):\t", G->deckCount[G->whoseTurn]);
    for (i = 0; i < G->deckCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->deck[G->whoseTurn][i]);
    }
    printf("\nhand: (%d):\t", G->handCount[G->whoseTurn]);
    for (i = 0; i < G->handCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->hand[G->whoseTurn][i]);
    }
    printf("\nplayedCards: (%d):\t", G->playedCardCount);
    for (i = 0; i < G->playedCardCount; ++i)
    {
      printf("%d\t", G->playedCards[i]);
    }
    printf("\ndiscard: (%d):\t", G->discardCount[G->whoseTurn]);
    for (i = 0; i < G->discardCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->discard[G->whoseTurn][i]);
    }
    printf("\n");
  #endif 


  // compare the manually changed testG gameState with the gameState G after the call to cardEffect_Adventurer
  asserttrue(memcmp(&testG, G, sizeof(struct gameState)) == 0, "gamestates are equal");

  // if gamestate cmp fails, display specific test results
  if (memcmp(&testG, G, sizeof(struct gameState)) != 0) {
    // 1) the card that was on top of player's deck is on "top" of the player's hand
    asserttrue(testG.hand[testG.whoseTurn][testG.handCount[testG.whoseTurn] - 1] == G->hand[G->whoseTurn][G->handCount[G->whoseTurn] - 1], "the card that was on top of player's deck is on \"top\" of the player's hand");

    // 2) player's deckCount decreases by exactly 1
    asserttrue(testG.deckCount[testG.whoseTurn] == G->deckCount[G->whoseTurn], "player's deckCount decreases by exactly 1");
    
    // 2) player's handCount remains the same (draw one and discard village)
    asserttrue(testG.handCount[testG.whoseTurn] == G->handCount[G->whoseTurn], "player's handCount remains the same (draw one and discard village)");

    // 3) number of actions increases by exactly 2
    asserttrue(testG.numActions == G->numActions, "number of actions increases by exactly 2");

    // 4) player's playedCardCount increases by 1
    asserttrue(testG.playedCardCount == G->playedCardCount, "player's playedCardCount increases by 1");

    // 5) village (14) is on top of player's playedCards pile
    asserttrue(testG.playedCards[testG.playedCardCount-1] == G->playedCards[G->playedCardCount-1], "village (14) is the top card of player's playedCards pile");
  }
  return 0;
} // end test_cardVillage





int main() {
	// initial vars
  struct gameState G;

  printf("This is randomtestcard2.c: testing cardVillage:\n"); 

  // set up random gameState and other relevant variables
  SelectStream(2);
  PutSeed(3);

  int n; // iterator for number of test runs
  int p; // iterator for player
  int i; // all-purpose iterator
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};
  initializeGame(4, k, 1000, &G); // this was necessary due to segfaults when calling discardCard() without it....

  for (n = 0; n < 20; n++) {
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
      G.playedCardCount = floor(Random() * 5);  // big enough for realistic game situations
      for (i = 0; i < G.playedCardCount; ++i)
      {
        G.playedCards[i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
      G.discardCount[p] = floor(Random() * 50);  // leave enough room for increase due to card action
      for (i = 0; i < G.discardCount[p]; ++i)
      {
        G.discard[p][i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
    } // p
    G.whoseTurn = floor(Random() * 4); // 0-3, four players is max
    // add smithy to G.whoseTurn's hand
    G.hand[G.whoseTurn][G.handCount[G.whoseTurn]] = village; //14 is village.  See enum CARDS in dominion.h
    G.handCount[G.whoseTurn]++;

    #if (VERBOSE_TEST == 1)
      printf("\n\nTest number %d\tplayer: %d\tdeckCount: %d\thandCount: %d\tplayedCardCount: %d\tdiscardCount: %d\n", n, G.whoseTurn, G.deckCount[G.whoseTurn], G.handCount[G.whoseTurn], G.playedCardCount, G.discardCount[G.whoseTurn]);
    #endif 
    #if (TRACERS == 1)
      printf("Player cards after random initialization:\ndeck: (%d):\t", G.deckCount[G.whoseTurn]);
      for (i = 0; i < G.deckCount[G.whoseTurn]; ++i)
      {
        printf("%d\t", G.deck[G.whoseTurn][i]);
      }
      printf("\nhand: (%d):\t", G.handCount[G.whoseTurn]);
      for (i = 0; i < G.handCount[G.whoseTurn]; ++i)
      {
        printf("%d\t", G.hand[G.whoseTurn][i]);
      }
      printf("\nplayedCards: (%d):\t", G.playedCardCount);
      for (i = 0; i < G.playedCardCount; ++i)
      {
        printf("%d\t", G.playedCards[i]);
      }
      printf("\ndiscard: (%d):\t", G.discardCount[G.whoseTurn]);
      for (i = 0; i < G.discardCount[G.whoseTurn]; ++i)
      {
        printf("%d\t", G.discard[G.whoseTurn][i]);
      }
      printf("\n");
    #endif    

    test_cardVillage(&G, G.handCount[G.whoseTurn] - 1);

  } // n


  if (testFlag == 1)
  {
    printf("ALL TESTS PASSED for randomtestcard2.c: cardVillage()\n\\n");
  }else {
    printf("\nOVERALL TEST FAILURE for randomtestcard2.c: cardVillage()\n\n");
  }
  return 0;
} // end main