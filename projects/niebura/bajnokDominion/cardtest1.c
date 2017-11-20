#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  srand(time(NULL));
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  initializeGame(2, k, rand(), &G);
  int drawntreasure = 0;
  int currentPlayer = whoseTurn(&G);
  int temphand[MAX_HAND];
  int cardDrawn;
  int z = 0;

  //Loop through each card in the hand to print out current hand.
  int itr = 0;
  for(itr = 0; itr < numHandCards(&G); itr++){
    printf("Card %d: %d\n", itr, handCard(itr, &G));
  }

  cardEffect(adventurer, 1, 1, 1, &G, 0, 0);
  //card_adventurer(drawntreasure, currentPlayer, &G, temphand, cardDrawn, z);

  //Reprint hand to see changes.
  for(itr = 0; itr < numHandCards(&G); itr++){
    printf("New Card %d: %d\n", itr, handCard(itr, &G));
  }
}
