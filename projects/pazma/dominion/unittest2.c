#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void assertTest(int a, int b, char* message){
	if (a==b)
	{
		printf("PASS: %s", message);
	}
	else
	{
		printf("FAIL: %s", message);
	}
};

int main() {
	int i, r;
	int seed = 1000;
	int numPlayer = 2;

	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	
	struct gameState G;
	int maxHandCount = 10;
	int currHandCount = -1;
	
	printf ("TESTING numHandCards():\n");
	for (int p = 0; p < numPlayer; p++)
	{
		for (int handCount = 1; handCount <= maxHandCount; handCount++)
		{
				printf("Test player %d with %d cards in hand\n", p, handCount);

				memset(&G, 23, sizeof(struct gameState));   // clear the game state
				r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.handCount[p] = handCount;                 // set the number of cards on hand
	
				currHandCount = numHandCards(&G);
			
				assertTest(currHandCount, handCount, "Hand Count\n\n"); // check if the number of cards is correct
		}
	}
	
	return 0;
}
