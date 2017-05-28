/* -----------------------------------------------------------------------
randomtestcard1.c
testing cardEffect_Smithy

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


int test_cardSmithy(struct gameState *G, int thisPlayer, int handPos){
  // copy the game state to a test case
  struct gameState testG;
  memcpy(&testG, G, sizeof(struct gameState)); 

  int i;
  #if (TRACERS == 1)
    printf("Player cards before call to cardSmithy():\ndeck: (%d):\t", G->deckCount[thisPlayer]);
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


  /* 
  tests for cardEffect_Smithy will be:
  1) player's deckCount decreases by 3
  2) player's handCount increases by 2 (draw 3 - play smithy)
  3) player's playedCard pile increases by 1
  4) smithy is the top card of player's playedCard pile

  */

  testG.deckCount[testG.whoseTurn] = testG.deckCount[testG.whoseTurn] - 3;
  testG.handCount[testG.whoseTurn] = testG.handCount[testG.whoseTurn] + 2;
  testG.playedCardCount++;
  testG.playedCards[testG.playedCardCount - 1] = smithy;  //13 is smithy.  See enum CARDS in dominion.h
  


 
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

  // Call cardEffect_Smithy with the original gameState.  
  // This *should* have the same effect as what was changed manually, above.
  cardSmithy(G, thisPlayer, handPos); 

  #if (TRACERS == 1)
    printf("Player cards after call to cardSmithy():\ndeck: (%d):\t", G->deckCount[thisPlayer]);
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

  //   1) player's deckCount decreases by 3
  asserttrue(testG.deckCount[testG.whoseTurn] == G->deckCount[G->whoseTurn], "player's deckCount decreases by 3");
  
  // 2) player's handCount increases by 2 (draw 3 - discard smithy)
  asserttrue(testG.handCount[testG.whoseTurn] == G->handCount[G->whoseTurn], "player's handCount increases by 2 (draw 3 - discard smithy)");

  // 3) player's playedCardCount pile increases by 1
  asserttrue(testG.playedCardCount == G->playedCardCount, "player's playedCards pile increases by 1");

  // 4) smithy is the top card of player's discard
  asserttrue(testG.discard[testG.whoseTurn][testG.discardCount[testG.whoseTurn]] == G->discard[G->whoseTurn][G->discardCount[G->whoseTurn]], "smithy (13) is the top card of player's playedCards pile");


  /*
  Other tests to consider:
  memcmp gamestates is possible if able to manually move three top cards from deck to hand in proper order...
  */

  return 0;
} // end test_cardEffect_Smithy





int main() {
	// initial vars
  struct gameState G;

  printf("This is randomtestcard2.c: testing cardSmithy:\n"); 

  // set up random gameState and other relevant variables
  SelectStream(2);
  PutSeed(3);

  int n; // iterator for number of test runs
  int p; // iterator for player
  int i; // all-purpose iterator
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};
  initializeGame(4, k, 1000, &G); // this was necessary due to segfaults when calling discardCard() without it....

  for (n = 0; n < 10; n++) { // segfault if n > 80 ...?!?!?!
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
      G.discardCount[p] = floor(Random() * (50));  // leave enough room for increase due to card action
      for (i = 0; i < G.discardCount[p]; ++i)
      {
        G.discard[p][i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
    } // p
    G.whoseTurn = floor(Random() * 4); // 0-3, four players is max
    // add smithy to G.whoseTurn's hand
    G.hand[G.whoseTurn][G.handCount[G.whoseTurn]] = smithy; //13 is smithy.  See enum CARDS in dominion.h
    G.handCount[G.whoseTurn]++;

    #if (VERBOSE_TEST == 1)
      printf("\n\nTest number %d\tplayer: %d\tdeckCount: %d\thandCount: %d\tplayedCardCount: %d\tdiscardCount: %d\n", n, G.whoseTurn, G.deckCount[G.whoseTurn], G.handCount[G.whoseTurn], G.playedCardCount, G.discardCount[G.whoseTurn]);
    #endif 
    /*
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
    */

    test_cardSmithy(&G, G.whoseTurn, G.handCount[G.whoseTurn] - 1);

  } // n


  if (testFlag == 1)
  {
    printf("ALL TESTS PASSED\n");
  }else {
    printf("\nOVERALL TEST FAILURE for randomtestcard2.c: cardEffect_Smithy\n\n");
  }
  return 0;
} // end main