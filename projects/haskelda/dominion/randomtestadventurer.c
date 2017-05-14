/* -----------------------------------------------------------------------
randomtestcard2.c
testing cardEffect_Adventurer

int cardEffect_Adventurer(struct gameState *state)
{
  //printf("cardEffect_Adventurer has been called\n"); // tracer
  int currentPlayer = whoseTurn(state);
  int temphand[MAX_HAND];
  int drawntreasure=0;
  int cardDrawn;
  int z = 0;// this is the counter for the temp hand
  while(drawntreasure<2){
  if (state->deckCount[currentPlayer] <2){//if the deck is empty we need to shuffle discard and add to deck
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


int test_cardEffect_Adventurer(int thisPlayer, struct gameState *G){
  // copy the game state to a test case
  struct gameState testG;
  memcpy(&testG, G, sizeof(struct gameState)); 

  int i;
  #if (TRACERS == 1)
    printf("Player cards before call to cardEffect_Adventurer:\ndeck:\t");
    for (i = 0; i < G->deckCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->deck[thisPlayer][i]);
    }
    printf("\nhand:\t");
    for (i = 0; i < G->handCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->hand[thisPlayer][i]);
    }
    printf("\ndiscard:\t");
    for (i = 0; i < G->discardCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->discard[thisPlayer][i]);
    }
    printf("\n");
  #endif 


  // manually change the test case according to the chosen tests:
  /* 
  tests for cardEffect_Adventurer will be:
  1) player's deckCount decreases by at least 2
  2) player's handCount increases by exactly 1 (gain 2 treasures, discard adventurer)
  3) player's discard pile increases by at least 2
  */

  testG.deckCount[thisPlayer] = testG.deckCount[thisPlayer] - 2;
  // add two treasures to hand
  testG.handCount[thisPlayer]++;
  // add two to discard pile
  testG.discardCount[thisPlayer] = testG.discardCount[thisPlayer] + 2;

 
  #if (TRACERS == 1)
    printf("test Player cards after changing manually:\ndeck:\t");
    for (i = 0; i < testG.deckCount[thisPlayer]; ++i)
    {
      printf("%d\t", testG.deck[thisPlayer][i]);
    }
    printf("\nhand:\t");
    for (i = 0; i < testG.handCount[thisPlayer]; ++i)
    {
      printf("%d\t", testG.hand[thisPlayer][i]);
    }
    printf("\ndiscard:\t");
    for (i = 0; i < testG.discardCount[thisPlayer]; ++i)
    {
      printf("%d\t", testG.discard[thisPlayer][i]);
    }
    printf("\n");
  #endif  

  // Call cardEffect_Adventurer with the original gameState.  
  // This *should* have the same effect as what was changed manually, above.
  cardEffect_Adventurer(G);

  #if (TRACERS == 1)
    printf("Player cards after call to cardEffect_Adventurer:\ndeck:\t");
    for (i = 0; i < G->deckCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->deck[thisPlayer][i]);
    }
    printf("\nhand:\t");
    for (i = 0; i < G->handCount[thisPlayer]; ++i)
    {
      printf("%d\t", G->hand[thisPlayer][i]);
    }
    printf("\ndiscard:\t");
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

  // 3) player's discard pile increases by at least 2
  asserttrue(testG.discardCount[thisPlayer] <= G->discardCount[thisPlayer], "player's discard pile increases by at least 2 after playing adventurer");

  /*
  Other tests to consider:
    other players card counts do not change
    the same other cards remain in the player's hand

  Other tests can also involve location of specific cards.
  But testing specific these changes would require the same amount of code that we are testing, which would be just as prone to error as the code itself

    adventurer is removed from the player's hand
    adventurer is added to discard
    the player's hand contains two additional treasure cards
    the same cards that were removed from the deck ended up in the discard (except for the treasures)
  */
  return 0;
} // end test_cardEffect_Adventurer





int main() {
	// initial vars
  struct gameState G;
  int thisPlayer;

  printf("This is randomtestcard2.c: testing cardEffect_Adventurer:\n"); 

  // set up random gameState and other relevant variables
  SelectStream(2);
  PutSeed(3);

  int n; // iterator for number of test runs
  int p; // iterator for player
  int i; // all-purpose iterator
  for (n = 0; n < 2000; n++) {
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
    thisPlayer = floor(Random() * 4); // 0-3, four players is max
    #if (VERBOSE_TEST == 1)
      printf("\n\nTest number %d\tplayer: %d\tdeckCount: %d\thandCount: %d\tdiscardCount: %d\n", n, thisPlayer, G.deckCount[thisPlayer], G.handCount[thisPlayer], G.discardCount[thisPlayer]);
    #endif
    test_cardEffect_Adventurer(thisPlayer, &G);
  } // n


  if (testFlag == 1)
  {
    printf("ALL TESTS PASSED\n");
  }else {
    printf("\nOVERALL TEST FAILURE for randomtestcard2.c: cardEffect_Adventurer\n\n");
  }
  return 0;
} // end main