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
	int numPlayer = 2;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	
	struct gameState G;
	int deckMax = 10;
	int handMax = 10;
	int discardMax = 10;
	int fullCount = -1;
	
	printf ("TESTING fullDeckCount():\n");
	for (int i = 0; i < deckMax; i++)
	{
		for (int j = 0; j < handMax; j++)
		{
			for (int l = 0; l < discardMax; l++)
			{
				for (int p = 0; p < numPlayer; p++)
				{
					printf("Test player %d with %d cards in deck, %d cards in hand, %d cards in discard\n", p, i, j, l);
					
					memset(&G, 23, sizeof(struct gameState));   // clear the game state
					r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
					G.deckCount[p] = i;
					G.handCount[p] = j;                 // set the number of cards on hand
					G.discardCount[p] = l;
					
					fullCount = fullDeckCount(p, 1, &G);
					
					assertTest(fullCount, i+j+l, "Full Deck Count\n\n"); // check if the number of cards is correct
				}
			}
		}
	}
	
	return 0;
}
