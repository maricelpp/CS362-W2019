//  randomtestcard2.c
// 	Adventurer Card
//	CS-362 W2019
// 	Assignment 4


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0
#define NOISY_TEST 1


int main () {
	
	int numPlayers = 0, currentPlayer = 0, adventurerPos = -1, treasureLocation = -1;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int randomSeed = 0, deckSize = 0, handSize = 0, discardSize = 0;
	int n = 0, r = 0;
	
	
	int kindomCards[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	
	struct gameState preTest, state;
	
	srand(time(0));
	
	randomSeed = rand();
	
	// Create game random state
	for (n = 0; n < 100; n++) {
		
		//printf("In loop %d\n", n);
		
		// Set number of players according to max. Must be 2-4 players
		numPlayers = (rand() % 3) + 2;
		
		// Initialize a game with random values
		initializeGame(numPlayers, kindomCards, randomSeed, &state);
		
		// Select current player randomly
		currentPlayer = rand() % state.numPlayers; // Does this need +1?
		
		// Set current player to random player
		state.whoseTurn = currentPlayer;
		
		
		
		// Set deck size
		deckSize = 10 + (rand() % MAX_DECK - 9);
		//printf("DECK SIZE: %d\n", deckSize);
		
		// Set hand size
		handSize = (rand() % (MAX_DECK - deckSize - 1)) + 1;
		//printf("HAND SIZE: %d\n", handSize);
		
		// Set discard size
		discardSize = rand() % (MAX_DECK - (deckSize + handSize) - 2) + 3;
		//printf("DISCARD SIZE: %d\n", discardSize);
		
		// Set current player's deck and hand count.
		state.deckCount[currentPlayer] = deckSize;
		state.handCount[currentPlayer] = handSize;
		state.discardCount[currentPlayer] = discardSize;
		
		// Set Adventurer position to last card in hand
		adventurerPos = state.handCount[currentPlayer] - 1;
		
		// Randomly decide where treasure will be planted
		treasureLocation = rand() % 3;
		
		// Money cards in the deck
		if (treasureLocation == 0)
		{
			state.deck[currentPlayer][state.deckCount[currentPlayer] - 1] = copper;
			state.deck[currentPlayer][state.deckCount[currentPlayer] - 2] = copper;
			
			// Create copy of pre-play state
			memcpy(&preTest, &state, sizeof(struct gameState));
			
			// Play card
			r = cardEffect(adventurer, choice1, choice2, choice3, &state, adventurerPos, &bonus);
			
			// Ensure play executed successfully
			assert (r == 0);
			
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] + 2;
			preTest.deckCount[currentPlayer] = preTest.deckCount[currentPlayer] - 2;
			
			// Discard a card (Adventurer played card)
			//preTest.playedCardCount = preTest.playedCardCount + 1;
			//preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] - 1;
			//assert(preTest.playedCardCount == state.playedCardCount);
			
			assert(preTest.handCount[currentPlayer] == state.handCount[currentPlayer]);
			assert(preTest.deckCount[currentPlayer] == state.deckCount[currentPlayer]);
			assert(preTest.discardCount[currentPlayer] == state.discardCount[currentPlayer]);
			
		}
		
		
		// Money cards in the discard pile
		else if (treasureLocation == 1)
		{
			
			for(int i = 0; i < state.deckCount[currentPlayer]; i++)
			{
				state.deck[currentPlayer][i] = -1;
			}
			
			state.discard[currentPlayer][0] = copper;
			state.discard[currentPlayer][1] = copper;
			
			// Create copy of pre-play state
			memcpy(&preTest, &state, sizeof(struct gameState));
			
			// Play card
			r = cardEffect(adventurer, choice1, choice2, choice3, &state, adventurerPos, &bonus);
			
			// Ensure play executed successfully
			assert (r == 0);
			
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] + 2;
			preTest.deckCount[currentPlayer] = preTest.deckCount[currentPlayer] - 2;
			
			// Discard a card (Adventurer played card)
			//preTest.playedCardCount = preTest.playedCardCount + 1;
			//preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] - 1;
			//assert(preTest.playedCardCount == state.playedCardCount);
			
			assert(preTest.handCount[currentPlayer] == state.handCount[currentPlayer]);
			assert((preTest.deckCount[currentPlayer] + preTest.discardCount[currentPlayer]) == (state.deckCount[currentPlayer] + state.discardCount[currentPlayer]));
		}
		
		
		// No discard pile
		else
		{
			for(int j = 0; j < state.deckCount[currentPlayer]; j++)
			{
				state.deck[currentPlayer][j] = -1;
			}
			
			for(int k = 0; k < state.discardCount[currentPlayer]; k++)
			{
				state.discard[currentPlayer][k] = -1;
			}
			
			// Create copy of pre-play state
			memcpy(&preTest, &state, sizeof(struct gameState));
			
			// Play card
			r = cardEffect(adventurer, choice1, choice2, choice3, &state, adventurerPos, &bonus);
			
			// Ensure play executed successfully
			assert (r == 0);
			
			preTest.discardCount[currentPlayer] = preTest.discardCount[currentPlayer] + preTest.deckCount[currentPlayer];
			preTest.deckCount[currentPlayer] = 0;
			
			// Discard a card (Adventurer played card)
			//preTest.playedCardCount = preTest.playedCardCount + 1;
			//preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] - 1;
			//assert(preTest.playedCardCount == state.playedCardCount);
			
			assert(preTest.handCount[currentPlayer] == state.handCount[currentPlayer]);
			
			assert(preTest.discardCount[currentPlayer] ==  state.discardCount[currentPlayer]);
			
		}
		
	}
	
	//printf ("ALL TESTS OK\n");
	
	return 0;
}

