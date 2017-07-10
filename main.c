#include <stdio.h>
#include <stdlib.h>
#include "GameState.h"
#include "Agent.h"
int main(int argc, char* argv[]) {
  Agent** players = malloc(2*sizeof(Agent*));
  players[0] = newAgent('O');
  players[1] = newAgent('X');
  int userTurn = 0;
  int userIndex= 0;
  char user;
  int play = 1;
  int userChosen = 0;
  while(play) {
    //Choosing order
    printf("Would you like to be X or O?\n");
    userChosen = 0;
    while(!userChosen) {
      scanf("%c", &user);
      while(getchar()!='\n');
      if(user=='X' || user=='x') {
        userTurn = 1;
        userIndex = 1;
        userChosen = 1;
      }
      else if(user=='O' || user=='o') {
        userTurn = 0;
        userIndex = 0;
        userChosen = 1;
      }
      else {
        printf("Please choose X or O.\n");
      }
    }

    //Starting a new gamestate
    int b;
    char bo[10] = "#########";
    GameState** games = malloc(10*sizeof(GameState*));
    for(int i= 0; i< 10;i++) {
      games[i] = malloc(sizeof(GameState));
    }
    *games = newGameState_p1(bo);
    printf("%d\n", terminalTest(*games));

    //Play until game is over
    while(!terminalTest(*games)) {
      printGameState(*games);
      // USER'S TURN
      if(userTurn) {
        userChosen = 0;
        while(!userChosen) {
          printf("Enter an empty board position (0-8):\n");
          scanf("%d", &b);
          if(b < 9 && b > -1) {
            if((*games)->gameBoard[b]!='#') {
              printf("The position you chose is not empty.\n");
            } else {
              userChosen = 1;
            }
          }
          else if(b >= 9 || b <= -1) {
            printf("The position you chose is out of range.\n");
          }
          else {
            printf("The position you chose is out of range.\n");
          }
        }
        *(games + 1) = result(*games, newAction_p3(b,players[userIndex]->agent));
      }
      // COMPUTER'S TURN
      else {
        Action* computerAct = alphaBetaSearch(players[userIndex^(1<<0)], *games);
        *(games + 1) = result(*games, computerAct);
        printf("Computer Moved: %d\n", computerAct->bPos);
        free(computerAct);
      }
      userTurn = userTurn^(1<<0); //toggle turn
      games++;
    }
    printGameState(*games);

    //Endgame messages
    int res = utility(players[0],*games);
    if(res==1) {
      printf("You Won!\n");
    }
    else if(res==-1) {
      printf("Game Over...\n");
    }
    else {
      printf("Draw!\n");
    }

    //Again?
    printf("Play again? (y) or (n):\n");
    userChosen = 0;
    while(getchar()!='\n'); //theres residue from last input
    while(!userChosen) {
      scanf("%c", &user);
      while(getchar()!='\n');
      if(user=='Y' || user=='y') {
        printf("Restarting...\n");
        play = 1;
        userChosen = 1;
      }
      else if(user=='N' || user=='n') {
        play = 0;
        userChosen = 1;
      }
      else {
        printf("Please choose Y or N.\n");
      }
    }
  }
  printf("See you again!\n");
}
