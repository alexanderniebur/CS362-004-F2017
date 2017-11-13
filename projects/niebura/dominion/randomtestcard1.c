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
  int counterF = 0;//Failed test counter
  int players;//Number of players
  int p = 0;//Specific player number for testing.
  struct gameState*g;//Game state struct
  int status;//Return for initializeGame(). -1 = fail, 0 = success.
  int i,x;//Iterators for loops
  int loop = 100;//Number of times the program loops this section.

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

    //Store the initial size of our hand.
    status = g->handCount[p];

    cardEffect(smithy, 1, 1, 1, g, 0, 0); //Run our function.

    //If there are three more cards, count as success.
    if(status + 2 == g->handCount[p]){
      counterS++;
    }
    else{
      counterF++;
    }

    //Free our memory.
    free(g);
  }

  //Print results.
  printf("Random Test for Smithy Card:\n");
  printf("There were %d successful smithy card plays.\n", counterS);//Successful cases.
  printf("There were %d failing smithy card plays.\n", counterF);//Failing cases.
  printf("This was out of %d loops.\n", loop);//Output number of loops for testing.
  
  return 0;
}
