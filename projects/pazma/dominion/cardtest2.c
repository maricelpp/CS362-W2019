/*
 *  cardtest2.c
 *
 */

/*
 *  Include the following lines in your makefile:
 *
 *  cardtest2: cardtest2.c dominion.o rngs.o
 *  gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Adventurer"

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
	int newCards = 0;
	int discardCards = 0;
	
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	newCards = 2; // Adventurer acquires 2 cards
	discardCards = 1; // Adventurer is discarded after it is played
	
	// TEST 1: Ensure current player's hand has increased by 3
	printf("TEST 1: Checking current player's hand\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discardCards);
	assertTest(testG.handCount[thisPlayer], (G.handCount[thisPlayer] + newCards - discardCards), "Hand Count\n\n");
	
	// TEST 2: Ensure player's deck has decreased by 3
	printf("TEST 2: Checking current player's deck\n");
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - G.discardCount[thisPlayer]);
	assertTest(testG.deckCount[thisPlayer], (G.deckCount[thisPlayer] - newCards - G.discardCount[thisPlayer]), "Deck Count\n\n");
	
	// TEST 3: Ensure player's action count has decreased by 1
	printf("TEST 3: Checking current player's action count\n");
	printf("action count = %d, expected = %d\n", testG.numActions, G.numActions);
	assertTest(testG.numActions, (G.numActions), "Action Count\n\n");
	
	// TEST 4: Ensure player's discard deck hasn't changed
	printf("TEST 4: Checking current player's discard deck\n");
	printf("discard deck count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	assertTest(testG.discardCount[thisPlayer], (G.discardCount[thisPlayer]), "Discard Deck Count\n\n");
	
	// TEST 5: Ensure player's buy count hasn't changed
	printf("TEST 5: Checking current player's buys count\n");
	printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys);
	assertTest(testG.numBuys, (G.numBuys), "Buy Count\n\n");
	
	// TEST 6: Ensure other player's hand has not changed
	printf("TEST 6: Checking other player's hand\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	assertTest(testG.handCount[otherPlayer], (G.handCount[otherPlayer]), "Hand Count\n\n");
	
	// TEST 7: Ensure player's deck has not changed
	printf("TEST 7: Checking other player's deck\n");
	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
	assertTest(testG.deckCount[otherPlayer], (G.deckCount[otherPlayer]), "Deck Count\n\n");
	
	// TEST 8: Ensure player's discard deck hasn't changed
	printf("TEST 8: Checking current player's discard deck\n");
	printf("discard deck count = %d, expected = %d\n", testG.discardCount[otherPlayer], G.discardCount[otherPlayer]);
	assertTest(testG.discardCount[otherPlayer], (G.discardCount[otherPlayer]), "Discard Deck Count\n\n");
	
	return 0;
}


