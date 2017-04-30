/*
-----------------------------------------------------------------------
unittest1.c
testing isGameOver()

expected behavior:  isGameOver returns 1 when either:  province cards are empty 
					OR three other supply pile cards stacks are empty.
					otherwise isGameOver returns 0

int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
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
#include <time.h> // rand, srand


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
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; // these do not matter for this test

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// begin testing
	printf("\n\nunittest1.c - testing the function isGameOver():\n");

	/*
	The tests for isGameOver() are NOT regarding change of game state.  It is simply if the function returns 1 or 0.
	isGameOver returns 1 when either:  province cards are empty OR three other supply pile cards stacks are empty.
	The other supply cards are: curse, estate, duchy, copper, silver, and gold.

	To attempt to cover sufficient input domain partitioning, testing here will cover the following instances:

	Expected outcome: game is over (return 1)
	1) province count = 0 AND the all other upply piles are not = 0
	2) province count = 0 AND one, two, and three other supply piles are = 0
	3) all supply counts = 0
	4) province count != 0 AND three other supply piles are = 0.  

	Expected outcome: game is not over (return 0)
	1) province count = 1 AND none, one, or two other supply piles are empty

	*/

	/***************************  Expected outcome: game is over (return 1)  *******************************************/
	//1) province count = 0 AND the all other upply piles are not = 0
	G.supplyCount[province] = 0;  // province pile is empty
	asserttrue(1 == isGameOver(&G), "Game end: province pile is empty"); // Note: all other supplies are > 0 due to initializeGame()

	//2) province count = 0 AND one, two, and three other supply piles are = 0
	G.supplyCount[curse] = 0;
	asserttrue(1 == isGameOver(&G), "Game end: province pile and one other supply pile is empty"); 
	G.supplyCount[copper] = 0;
	asserttrue(1 == isGameOver(&G), "Game end: province pile and two other supply piles are empty"); 
	G.supplyCount[estate] = 0;
	asserttrue(1 == isGameOver(&G), "Game end: province pile and three other supply piles are empty"); 

	//3) province count != 0 AND three other supply piles are = 0. 	
	G.supplyCount[province] = 1;
	asserttrue(1 == isGameOver(&G), "Game end: province pile is NOT empty but three other supply piles are empty"); // Note: three supply piles are still empty

	//4) all supply counts = 0
	G.supplyCount[province] = 0;
	G.supplyCount[silver] = 0;
	G.supplyCount[gold] = 0;
	G.supplyCount[duchy] = 0;
	asserttrue(1 == isGameOver(&G), "Game end: all supply piles are empty"); // Note: other three supply piles are still empty


	/*************************   Expected outcome: game is not over (return 0) *****************************************/
	//1) province count = 1 AND none, one, or two other supply piles are empty
	G.supplyCount[province] = 1;
	G.supplyCount[curse] = 1;
	G.supplyCount[gold] = 1;
	G.supplyCount[duchy] = 1;	
	G.supplyCount[silver] = 1;
	G.supplyCount[copper] = 1;
	G.supplyCount[estate] = 1;
	asserttrue(0 == isGameOver(&G), "Game did NOT end: all supply piles are NOT empty");
	G.supplyCount[gold] = 0;
	asserttrue(0 == isGameOver(&G), "Game did NOT end: only one supply pile is empty");
	G.supplyCount[curse] = 0;
	asserttrue(0 == isGameOver(&G), "Game did NOT end: only two supply piles are empty");


	/***************************************  final results  **************************************************************/
	if (testFlag == 1)
	{
		printf("ALL TESTS PASSED for unittest1.c: isGameOver():\n\n");
	} else {
		printf("TEST FAILURE for unittest1.c: isGameOver():\n\n");
	}

    return 0;
}