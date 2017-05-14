/* -----------------------------------------------------------------------
randomtestcard1.c
testing cardEffect_Smithy

 int cardEffect_Smithy(struct gameState *state, int handPos)
{
  int i;
  int currentPlayer = whoseTurn(state);
  //+3 Cards
  for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer + i, state);
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
#define TRACERS 0 // 1 = ON, 0 = OFF. For displaying actual cards in players' deck, hand, discard

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


int test_cardEffect_Smithy(struct gameState *G, int handPos){
  // copy the game state to a test case
  struct gameState testG;
  memcpy(&testG, G, sizeof(struct gameState)); 

  int i;
  #if (TRACERS == 1)
    printf("Player cards before call to cardEffect_Smithy:\ndeck:\t");
    for (i = 0; i < G->deckCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->deck[G->whoseTurn][i]);
    }
    printf("\nhand:\t");
    for (i = 0; i < G->handCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->hand[G->whoseTurn][i]);
    }
    printf("\ndiscard:\t");
    for (i = 0; i < G->discardCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->discard[G->whoseTurn][i]);
    }
    printf("\n");
  #endif 


  /* 
  tests for cardEffect_Smithy will be:
  1) player's deckCount decreases by 3
  2) player's handCount increases by 2 (draw 3 - discard smithy)
  3) player's discard pile increases by 1
  4) smithy is the top card of player's discard
  */

  testG.deckCount[testG.whoseTurn] = testG.deckCount[testG.whoseTurn] - 2;

  testG.handCount[testG.whoseTurn] = testG.handCount[testG.whoseTurn] + 2;

  testG.discard[testG.whoseTurn][testG.discardCount[testG.whoseTurn]] = smithy;  //13 is smithy.  See enum CARDS in dominion.h
  testG.discardCount[testG.whoseTurn] = testG.discardCount[testG.whoseTurn] + 1;


 
  #if (TRACERS == 1)
    printf("test Player cards after changing manually:\ndeck:\t");
    for (i = 0; i < testG.deckCount[testG.whoseTurn]; ++i)
    {
      printf("%d\t", testG.deck[testG.whoseTurn][i]);
    }
    printf("\nhand:\t");
    for (i = 0; i < testG.handCount[testG.whoseTurn]; ++i)
    {
      printf("%d\t", testG.hand[testG.whoseTurn][i]);
    }
    printf("\ndiscard:\t");
    for (i = 0; i < testG.discardCount[testG.whoseTurn]; ++i)
    {
      printf("%d\t", testG.discard[testG.whoseTurn][i]);
    }
    printf("\n");
  #endif  

  // Call cardEffect_Smithy with the original gameState.  
  // This *should* have the same effect as what was changed manually, above.
  cardEffect_Smithy(G, handPos); // handPos is G->handCount[G->whoseTurn] - 1

  #if (TRACERS == 1)
    printf("Player cards after call to cardEffect_Smithy:\ndeck:\t");
    for (i = 0; i < G->deckCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->deck[G->whoseTurn][i]);
    }
    printf("\nhand:\t");
    for (i = 0; i < G->handCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->hand[G->whoseTurn][i]);
    }
    printf("\ndiscard:\t");
    for (i = 0; i < G->discardCount[G->whoseTurn]; ++i)
    {
      printf("%d\t", G->discard[G->whoseTurn][i]);
    }
    printf("\n");
  #endif 


  // compare the manually changed testG gameState with the gameState G after the call to cardEffect_Adventurer

  //   1) player's deckCount decreases by 3
  asserttrue(testG.deckCount[testG.whoseTurn] == G->deckCount[G->whoseTurn], "player's deckCount decreases by 3");
  
  // 2) player's handCount increases by 2 (draw 3 - discard smithy)
  asserttrue(testG.handCount[testG.whoseTurn] == G->handCount[G->whoseTurn], "player's handCount increases by 2 (draw 3 - discard smithy)");

  // 3) player's discard pile increases by 1
  asserttrue(testG.discardCount[testG.whoseTurn] == G->discardCount[G->whoseTurn], "player's discard pile increases by 1");

  // 4) smithy is the top card of player's discard
  asserttrue(testG.discard[testG.whoseTurn][testG.discardCount[testG.whoseTurn]] == G->discard[G->whoseTurn][G->discardCount[G->whoseTurn]], "smithy is the top card of player's discard");


  /*
  Other tests to consider:

  other players card counts do not change
  the same other cards remain in the player's hand
  smithy is removed from the player's hand
  */
  return 0;
} // end test_cardEffect_Smithy





int main() {
	// initial vars
  struct gameState G;

  printf("This is randomtestcard2.c: testing cardEffect_Smithy:\n"); 

  // set up random gameState and other relevant variables
  SelectStream(2);
  PutSeed(3);

  int n; // iterator for number of test runs
  int p; // iterator for player
  int i; // all-purpose iterator
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};
  initializeGame(4, k, 1000, &G); // this was necessary due to segfaults when calling discardCard() without it....

  for (n = 0; n < 80; n++) {
    // fill four different players' deck, hand, and discard with a random amount of random cards. 
    for (p = 0; p < 4; ++p){
      G.deckCount[p] = floor(Random() * MAX_DECK);
      for (i = 0; i < G.deckCount[p]; ++i)
      {
        G.deck[p][i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
      G.handCount[p] = floor(Random() * 50);  // big enough for realistic game situations
      for (i = 0; i < G.handCount[p]; ++i)
      {
        G.hand[p][i] = floor(Random() * 28); // 27 is number of cards.   See enum CARDS in dominion.h
      }
      G.discardCount[p] = floor(Random() * (MAX_DECK - 50));  // leave enough room for increase due to card action
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
      printf("\n\nTest number %d\tplayer: %d\tdeckCount: %d\thandCount: %d\tdiscardCount: %d\n", n, G.whoseTurn, G.deckCount[G.whoseTurn], G.handCount[G.whoseTurn], G.discardCount[G.whoseTurn]);
    #endif 
    #if (TRACERS == 1)
      printf("Player cards after random initialization:\ndeck:\t");
      for (i = 0; i < G.deckCount[G.whoseTurn]; ++i)
      {
        printf("%d\t", G.deck[G.whoseTurn][i]);
      }
      printf("\nhand:\t");
      for (i = 0; i < G.handCount[G.whoseTurn]; ++i)
      {
        printf("%d\t", G.hand[G.whoseTurn][i]);
      }
      printf("\ndiscard:\t");
      for (i = 0; i < G.discardCount[G.whoseTurn]; ++i)
      {
        printf("%d\t", G.discard[G.whoseTurn][i]);
      }
      printf("\n");
    #endif    

    test_cardEffect_Smithy(&G, G.handCount[G.whoseTurn] - 1);

  } // n


  if (testFlag == 1)
  {
    printf("ALL TESTS PASSED\n");
  }else {
    printf("\nOVERALL TEST FAILURE for randomtestcard2.c: cardEffect_Smithy\n\n");
  }
  return 0;
} // end main