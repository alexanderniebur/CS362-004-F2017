//MACROS
#define MAX_NUM 50

//Include necessary libraries.
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//Include additional files.
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
  //Initialize the random seed.
  srand(time(NULL));
  //Initialize cards that can appear.
  int kingdom[10] = {adventurer, smithy, embargo, village, mine, gardens, tribute, minion, cutpurse, sea_hag};
  int counterS = 0;//Successful test counter
  int counterstatusF = 0;//Failed test counter
	int countercardcountF = 0;
	int countertokencountF = 0;
	int countercoincountF = 0;
  int players;//Number of players
  int p = 0;//Specific player number for testing.
  struct gameState*g;//Game state struct
  int status;//Return for initializeGame(). -1 = fail, 0 = success.
  int i,x;//Iterators for loops
  int loop = 100;//Number of times the program loops this section.
  int precoin, pretokens, prehand;

  //Loop through random testing algorithm.
  for(i = 0; i < loop; i++){
    players = rand()%4;//Set our number of players.
    g = malloc(sizeof(struct gameState)); //Allocate memory for our gameState object.
    //status = 
    initializeGame(players, kingdom, rand(), g);//Initialize the game struct.

    //Setup card related objects. (MAX_DECK & MAX_HAND are Macros set in dominion.h for a value of 500).
    g->deckCount[p] = rand() % MAX_DECK;//Set the deck size.
    g->discardCount[p] = rand() % MAX_DECK;//Randomize discard pile size.
    g->handCount[p] = rand() % MAX_HAND;//Randomize size of the hand.
    g->supplyCount[p] = rand() % MAX_NUM;//Randomize Supply.
    g->embargoTokens[1] = rand() % MAX_NUM;//Randomize embargo tokens.
    g->coins = rand() % MAX_NUM;//Randomize coins.
		g->whoseTurn = p;
    //Store the initial size of our stuff.
    precoin = g->coins;
    pretokens = g->embargoTokens[1];
    prehand = g->handCount[p];
    
    status = cardEffect(embargo, 1, 1, 1, g, 0, 0); //Run our function.

    //If there are three more cards, count as success.
    if(status == 0){
      if(prehand - 1 == g->handCount[p]){
				if(pretokens + 1 == g->embargoTokens[1]){
					if(precoin + 2 == g->coins){
						counterS++;
					}
					else{
						countercoincountF++;
					}
				}
				else{
					printf("Original count: %d\t New count: %d\n", pretokens, g->embargoTokens[p]);
					countertokencountF++;
				}
      }
			else{
				printf("Original count: %d\t New count: %d\n", prehand, g->handCount[p]);
				countercardcountF++;
			}
    }
    else{
      counterstatusF++;
    }

    //Free our memory.
    free(g);
  }

  //Print results.
  printf("Random Test for Embargo Card:\n");
  printf("There were %d successful Embargo card plays.\n", counterS);//Successful cases.
  printf("There were %d failing Embargo card plays.\n", counterstatusF + countercardcountF + countertokencountF + countercoincountF);//Failing cases.
	printf("Of the failues, %d were failed status, %d were wrong handcount, %d were failed token count, and %d were failed coin count\n\n", counterstatusF, countercardcountF, countertokencountF, countercoincountF);
  printf("This was out of %d loops.\n", loop);//Output number of loops for testing.
  
  return 0;
}
