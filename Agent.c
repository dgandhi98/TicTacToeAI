#include "Agent.h"
#include <stdlib.h>
// Constructor
Agent* newAgent(char c) {
  Agent* doer = malloc(sizeof(Agent));
  doer->agent = c;
  return doer;
}

// Checks if no moves left or if someone won
int terminalTest(GameState* gs) {
  if(gs->numPossMoves==0) {
    return 1;
  }
  else {
    for(int i = 0; i < 3;i++) {
      if(gs->gameBoard[i*3] == gs->gameBoard[i*3 + 1]
      && gs->gameBoard[i*3] == gs->gameBoard[i*3 + 2]
      && gs->gameBoard[i*3]!='#') {
          return 1;
      }
      if(gs->gameBoard[0+i] == gs->gameBoard[3+i]
      && gs->gameBoard[0+i] == gs->gameBoard[6+i]
      && gs->gameBoard[0+i]!='#') {
        return 1;
      }
    }
    if(gs->gameBoard[0] == gs->gameBoard[1*3 + 1]
    && gs->gameBoard[0]== gs->gameBoard[2*3 + 2]
    && gs->gameBoard[0]!='#') {
      return 1;
    }
    if(gs->gameBoard[2] == gs->gameBoard[1*3 + 1]
    && gs->gameBoard[2]== gs->gameBoard[2*3 + 0]
    && gs->gameBoard[2]!='#') {
      return 1;
    }
  }
  return 0;
}

// when we know the gamestate is terminal, we can return
// the utility value for agent A.
int utility(Agent* A, GameState* gs) {
  for(int i = 0; i < 3;i++) {
    if(gs->gameBoard[i*3] == gs->gameBoard[i*3 + 1]
    && gs->gameBoard[i*3] == gs->gameBoard[i*3 + 2]
    && gs->gameBoard[i*3]!='#') {
      if(gs->gameBoard[i*3]==A->agent)
        return 1;
      else
        return -1;
    }
    if(gs->gameBoard[0+i] == gs->gameBoard[3+i]
    && gs->gameBoard[0+i] == gs->gameBoard[6+i]
    && gs->gameBoard[0+i]!='#') {
      if(gs->gameBoard[0+i]==A->agent)
        return 1;
      else
        return -1;
    }
  }
  if(gs->gameBoard[0] == gs->gameBoard[1*3 + 1]
  && gs->gameBoard[0]== gs->gameBoard[2*3 + 2]
  && gs->gameBoard[0]!='#') {
    if(gs->gameBoard[0]==A->agent)
      return 1;
    else
      return -1;
  }
  if(gs->gameBoard[2] == gs->gameBoard[1*3 + 1]
  && gs->gameBoard[2]== gs->gameBoard[2*3 + 0]
  && gs->gameBoard[2]!='#') {
    if(gs->gameBoard[2]==A->agent)
      return 1;
    else
      return -1;
  }
  return 0;
}

// Returns a resulting gamestate using the previous gs and an action a
GameState* result(GameState* gs, Action* a) {
  GameState* gs2 = newGameState_p1(gs->gameBoard);
  gs2->gameBoard[a->bPos] = a->agent;
  gs2->numPossMoves--;
  return gs2;
}

// Minimax algorithm with Alpha Beta Pruning
// I complete the first analysis of max within the
// first call of the search to be able to return the action
// of the value
Action* alphaBetaSearch(Agent* doer, GameState* gs) {
  Action* maxAction = newAction();
  int alp = -2;
  int bet = 2;
  int maxV = -2;
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(gs->gameBoard[3*i + j]=='#') {
        Action* na = newAction_p3(3*i+j,doer->agent);
        GameState* ngs = result(gs, na);
        int newV = minValue(doer, ngs, alp, bet);
        if(maxV < newV) {
          maxV = newV;
          maxAction->bPos = na->bPos;
          maxAction->agent = na->agent;
        }
        free(na);
        free(ngs->gameBoard);
        free(ngs);
        alp = alp > maxV ? alp:maxV;
      }
    }
  }
  return maxAction;
}

// Analysis of the max opponent, if one of the siblings
// turns out to be greater than or equal to the beta
// then we know we can skip the rest of the siblings.
int maxValue(Agent* doer, GameState* gs, int alp, int bet) {
  if(terminalTest(gs)) {
    return utility(doer,gs);
  }
  int currV = -2;
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(gs->gameBoard[3*i + j]=='#') {
        Action* na = newAction_p3(3*i+j,doer->agent);
        GameState* ngs = result(gs, na);
        int newV = minValue(doer, ngs, alp, bet);
        currV = currV > newV ? currV:newV;
        free(na);
        free(ngs->gameBoard);
        free(ngs);
        if(currV >= bet) return currV;
        alp = alp > currV ? alp:currV;
      }
    }
  }
  return currV;
}

// Analysis of the max opponent, if one of the siblings
// turns out to be less than or equal to the alpha
// then we know we can skip the rest of the siblings.
int minValue(Agent* doer, GameState* gs, int alp, int bet) {
  char c;
  if(doer->agent == 'X') {
    c='O';
  }
  else {
    c='X';
  }
  if(terminalTest(gs)) {
    return utility(doer,gs);
  }
  int currV = 2;
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(gs->gameBoard[3*i + j]=='#') {
        Action* na = newAction_p3(3*i + j,c);
        GameState* ngs = result(gs, na);
        int newV = maxValue(doer, ngs, alp, bet);
        currV = currV < newV ? currV:newV;
        free(na);
        free(ngs->gameBoard);
        free(ngs);
        if(currV <= alp) return currV;
        bet = bet < currV ? bet:currV;
      }
    }
  }
  return currV;
}
