#include <stdio.h>
#include "GameState.h"
#include <stdlib.h>
//Constructors
GameState* newGameState() {
  GameState* gs = malloc(sizeof(GameState));
  gs->gameBoard = malloc(9*sizeof(char));
  for(int i=0; i < 9; i++) {
    gs->gameBoard[i] = '#';
  }
  gs->sibling = NULL;
  gs->child = NULL;
  gs->numPossMoves = 9;
  return gs;
}

GameState* newGameState_p1(char* tocpy) {
  GameState* gs = malloc(sizeof(GameState));
  gs->gameBoard = malloc(9*sizeof(char));
  gs->numPossMoves = 0;
  for(int i=0; i < 9; i++) {
    if(tocpy[i]=='#') {
      gs->numPossMoves++;
    }
    gs->gameBoard[i] = tocpy[i];
  }
  gs->sibling = NULL;
  gs->child = NULL;
  return gs;
}

Action* newAction_p3(int b, char c) {
  Action* A = malloc(sizeof(Action));
  A->bPos = b;
  A->agent = c;
  return A;
}
Action* newAction() {
  Action* A = malloc(sizeof(Action));
  A->bPos = -1;
  A->agent = '\0';
  return A;
}

void printGameState(GameState* gs) {
/*
+---|---|---+
| # | # | # |
----|---|----
| # | # | # |
----|---|----
| # | # | # |
+-----------+
*/
  printf("+---|---|---+\n");
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      printf("| %c ", gs->gameBoard[j+i*3]);
    }
    if(i<2){
      printf("|\n----|---|----\n");
    }
    else {
      printf("|\n+---|---|---+\n");
    }
  }

}
