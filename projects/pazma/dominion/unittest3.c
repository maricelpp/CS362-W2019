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
	int r;
	int seed = 1000;
	int numPlayer = 4;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	
	struct gameState G;
	
	int currPlayer = -1;
	
	printf ("TESTING whoseTurn():\n");
	for (int p = 0; p < numPlayer; p++)
	{
			printf("Test player %d\n", p);
			
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
			G.whoseTurn = p;                 // set the number of cards on hand
		
			currPlayer = whoseTurn(&G);
		
			assertTest(currPlayer, p, "Current Player\n\n"); // check if the number of cards is correct
		
	}
	
	return 0;
}
