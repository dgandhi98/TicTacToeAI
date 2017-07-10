#ifndef TICTACTOE_AGENT_H
#define TICTACTOE_AGENT_H

#include "GameState.h"

struct Agent {
  char agent;
};
typedef struct Agent Agent;

//constructor
Agent* newAgent(char);

//returns 0 or 1
int terminalTest(GameState*);

int utility(Agent*, GameState*);

GameState* result(GameState*, Action*);

Action* alphaBetaSearch(Agent*, GameState*);

int maxValue(Agent*, GameState*, int, int);
int minValue(Agent*, GameState*, int, int);

#endif
