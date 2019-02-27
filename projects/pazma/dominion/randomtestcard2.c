#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkSmithy(int currentPlayer, struct gameState *post, int handPos) {
	int r;
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	r = smithyCard(currentPlayer, post, handPos);
	
	for(int maxdraw = 0; maxdraw < 3; maxdraw++)
	{
		if (pre.deckCount[currentPlayer] > 0)
		{
			pre.handCount[currentPlayer]++;
			pre.hand[currentPlayer][pre.handCount[currentPlayer]-1] = pre.deck[currentPlayer][pre.deckCount[currentPlayer]-1];
			pre.deckCount[currentPlayer]--;
		}
		else if (pre.discardCount[currentPlayer] > 0)
		{
			memcpy(pre.deck[currentPlayer], post->deck[currentPlayer], sizeof(int) * pre.discardCount[currentPlayer]);
			memcpy(pre.discard[currentPlayer], post->discard[currentPlayer], sizeof(int) * pre.discardCount[currentPlayer]);
			pre.hand[currentPlayer][post->handCount[currentPlayer]-1] = post->hand[currentPlayer][post->handCount[currentPlayer]-1];
			pre.handCount[currentPlayer]++;
			pre.deckCount[currentPlayer] = pre.discardCount[currentPlayer]-1;
			pre.discardCount[currentPlayer] = 0;
		}
	}
	
	discardCard(handPos, currentPlayer, &pre, 0);
	
	assert (r == 0);
	assert (memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {
	
	int i, j, n, r, player, deckCount, discardCount, handCount, smithyPos;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	
	struct gameState G;
	
	printf ("Testing drawCard.\n");
	
	printf ("RANDOM TESTS.\n");
	
	SelectStream(2);
	PutSeed(3);
	
	// Create game random state
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		player = floor(Random() * 2);
		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);
		
		for (j = 0; j < G.handCount[player]; j++) {
			if (handCard(j, &G) == smithy)
			{
				smithyPos = i;
				checkSmithy(player, &G, smithyPos);
			}
		}
	}
	
	printf ("ALL TESTS OK\n");
	
	exit(0);
	
	printf ("SIMPLE FIXED TESTS.\n");
	for (player = 0; player < 2; player++) {
		for (deckCount = 0; deckCount < 5; deckCount++) {
			for (discardCount = 0; discardCount < 5; discardCount++) {
				for (handCount = 0; handCount < 5; handCount++) {
					memset(&G, 23, sizeof(struct gameState));
					r = initializeGame(2, k, 1, &G);
					G.deckCount[player] = deckCount;
					memset(G.deck[player], 0, sizeof(int) * deckCount);
					G.discardCount[player] = discardCount;
					memset(G.discard[player], 0, sizeof(int) * discardCount);
					G.handCount[player] = handCount;
					memset(G.hand[player], 0, sizeof(int) * handCount);
					for (j = 0; j < G.handCount[player]; j++) {
						if (handCard(j, &G) == smithy)
						{
							smithyPos = i;
							checkSmithy(player, &G, smithyPos);
						}
					}
				}
			}
		}
	}
	
	return 0;
}
