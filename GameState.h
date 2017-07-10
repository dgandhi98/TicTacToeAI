
#ifndef TICTACTOE_GAMESTATE_H
#define TICTACTOE_GAMESTATE_H

typedef struct Node GameState;
struct Node {
  char* gameBoard;
  int numPossMoves;
  GameState* sibling;
  GameState* child;
};

struct Action {
  int bPos;
  char agent;
};
typedef struct Action Action;

//Constructors
GameState* newGameState();
GameState* newGameState_p1(char*);
Action* newAction_p3(int, char);
Action* newAction();

void printGameState(GameState*);

#endif
