//  randomtestcard1.c
// 	Village Card
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
	
	int numPlayers = 0, currentPlayer = 0, villagePos = -1;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int randomSeed = 0, deckSize = 0, handSize = 0, discardSize = 0, actionSize = 0;
	int n = 0, r = 0;
	
	
	int kindomCards[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	
	struct gameState preTest, state;
	
	//printf ("Testing Smithy.\n");
	//printf ("RANDOM TESTS.\n");
	
	//SelectStream(2);
	//PutSeed(3);
	
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
		
		// Set hand size (must be less than or equal to deck size
		handSize = (rand() % (MAX_DECK - deckSize - 1)) + 1;
		//printf("HAND SIZE: %d\n", handSize);
		
		// Set hand size (must be less than or equal to deck size
		discardSize = rand() % (MAX_DECK - (deckSize + handSize)) + 1;
		//printf("DISCARD SIZE: %d\n", discardSize);
		
		// Set number of actions for current player
		actionSize = (rand() % 100) + 1;
		
		// Set current player's deck and hand count.
		state.deckCount[currentPlayer] = deckSize;
		state.handCount[currentPlayer] = handSize;
		state.discardCount[currentPlayer] = discardSize;
		state.numActions = actionSize;
		
		if(state.handCount[currentPlayer] < 1)
		{
			return 0;
		}
		
		// Set Village position to last card in hand
		villagePos = state.handCount[currentPlayer] - 1;
		
		// Create copy of pre-play state
		memcpy(&preTest, &state, sizeof(struct gameState));
		
		
		// Play card
		r = cardEffect(village, choice1, choice2, choice3, &state, villagePos, &bonus);
		
		
		// Ensure play executed successfully
		assert (r == 0);
		
		
		// TEST ORACLE
		
		// Update hand, deck, and discard counts.
		if((preTest.deckCount[currentPlayer] + preTest.discardCount[currentPlayer]) < 1)
		{
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] + preTest.deckCount[currentPlayer] + preTest.discardCount[currentPlayer];
			
			// Set discard and deck to 0 after discard is shuffled and added to deck and all are added to hand
			preTest.discardCount[currentPlayer] = 0;
			preTest.deckCount[currentPlayer] = 0;
			
			// Discard a card (Village played card)
			preTest.playedCardCount = preTest.playedCardCount + 1;
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] - 1;
			
			preTest.numActions = preTest.numActions + 2;
			
		}
		
		else if (preTest.deckCount[currentPlayer] < 1)
		{
			preTest.deckCount[currentPlayer] = preTest.deckCount[currentPlayer] + preTest.discardCount[currentPlayer];
			preTest.discardCount[currentPlayer] = 0;
			
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] + 1;
			preTest.deckCount[currentPlayer] = preTest.deckCount[currentPlayer] - 1;
			
			// Discard a card (Village played card)
			preTest.playedCardCount = preTest.playedCardCount + 1;
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] - 1;
			
			preTest.numActions = preTest.numActions + 2;
		}
		
		else
		{
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] + 1;
			preTest.deckCount[currentPlayer] = preTest.deckCount[currentPlayer] - 1;
			
			// Discard a card (Village played card)
			preTest.playedCardCount = preTest.playedCardCount + 1;
			preTest.handCount[currentPlayer] = preTest.handCount[currentPlayer] - 1;
			
			preTest.numActions = preTest.numActions + 2;
		}
		
		
		assert(preTest.playedCardCount == state.playedCardCount);
		assert(preTest.handCount[currentPlayer] == state.handCount[currentPlayer]);
		assert(preTest.deckCount[currentPlayer] == state.deckCount[currentPlayer]);
		assert(preTest.numActions == state.numActions);
		
	}
	
	
	
	//printf ("ALL TESTS OK\n");
	
	return 0;
}

