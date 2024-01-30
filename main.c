/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Chan Chi Yung
 * Student ID    : 1155175838
 * Class/Section : ENGG1110 - C
 * Date          : 2021-12-02
 */

#include <stdio.h>
/* NO other header files are allowed */

/* NO global variables are allowed */

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2



/* Initialize the game board by setting all squares to EMPTY */
void initGameBoard(int gameBoard[6][7]) {
  int i, j;
  for (i = 0; i <= 5; i++) {
    for (j = 0; j <= 6; j++) {
      gameBoard[i][j] = EMPTY;
    }
  }
}



/* Display the game board on the screen.
   You are required to exactly follow the output format stated in the project specification.
   IMPORTANT: Using other output format will result in mark deduction. */
void printGameBoard(int gameBoard[6][7]) {
  int i ,j;
  for (i = 0; i <= 5; i++) {
    printf("|");
    for (j = 0; j <= 6; j++) {
      if (gameBoard[i][j] == EMPTY) {
        printf(" ");
      }
      if (gameBoard[i][j] == CIRCLE) {
        printf("O");
      }
      if (gameBoard[i][j] == CROSS) {
        printf("X");
      }
      printf("|");
    }
    printf("\n");
  }
  printf(" 1 2 3 4 5 6 7\n");
}



/* Ask the human player to place the mark.
   You can assume that the user input must be an integer. */
void placeMarkByHumanPlayer(int gameBoard[6][7], int mark) {
  int move, i, istrue;
  scanf("%d", &move);
  while (move < 1 || move > 7 || gameBoard[0][move-1] != EMPTY) {
    while (move < 1 || move > 7) {
      printf("Input out of range. Please input again:\n");
      scanf("%d", &move);
    }
    while (gameBoard[0][move-1] != EMPTY) {
      printf("Column is full. Please input again:\n");
      scanf("%d", &move);
    }
  }
  istrue = 0;
  i = 5;
  while (i >= 0 && istrue == 0) {
    if (gameBoard[i][move-1] == EMPTY) {
      gameBoard[i][move-1] = mark;
      istrue = 1;
    }
    i--;
  }
}



/* Return 1 if there is a winner in the game, otherwise return 0.
   Note: the winner is the current player indicated in main(). */
int hasWinner(int gameBoard[6][7]) {
  int i, j, k, count, target, iswin = 0;

  for (i = 0; i <= 5; i++) {
    for (j = 0; j <= 3; j++) {
      target = gameBoard[i][j];
      count = 0;
      for (k = 0; k <= 3; k++) {
        if (gameBoard[i][j+k] == target && gameBoard[i][j+k] != EMPTY) {
          count++;
        }
      }
      if (count == 4) {
        iswin = 1;
        return 1;
      }
    }
  }

  for (i = 0; i <= 6; i++) {
    for (j = 0; j <= 2; j++) {
      target = gameBoard[j][i];
      count = 0;
      for (k = 0; k <= 3; k++) {
        if (gameBoard[j+k][i] == target && gameBoard[j+k][i] != EMPTY) {
          count++;
        }
      }
      if (count == 4) {
        iswin = 1;
        return 1;
      }
    }
  }

  for (i = 0; i <= 2; i++) {
    for (j = 0; j <= 3; j++) {
      target = gameBoard[i][j];
      count = 0;
      for (k = 0; k <= 3; k++) {
        if (gameBoard[i+k][j+k] == target && gameBoard[i+k][j+k] != EMPTY) {
          count++;
        }
      }
      if (count == 4) {
        iswin = 1;
        return 1;
      }
    }
  }

  for (i = 3; i <= 5; i++) {
    for (j = 0; j <= 3; j++) {
      target = gameBoard[i][j];
      count = 0;
      for (k = 0; k <= 3; k++) {
        if (gameBoard[i-k][j+k] == target && gameBoard[i-k][j+k] != EMPTY) {
          count++;
        }
      }
      if (count == 4) {
        iswin = 1;
        return 1;
      }
    }
  }
  if (iswin != 1) {
      return 0;
  }
}



/* Return 1 if the game board is full, otherwise return 0. */
int isFull(int gameBoard[6][7]) {
  int i, count = 0;
  for (i = 0; i <= 6; i++) {
    if (gameBoard[0][i] != EMPTY) {
      count++;
    }
  }
  if (count == 7) {
    return 1;
  }
  else {
    return 0;
  }
}



/* Determine the next move of the computer player.
   You are required to exactly follow the strategy mentioned in the project specification.
   Using other strategies will result in mark deduction. */

void placeMarkByComputerPlayer(int gameBoard[6][7]) {
  int i, j, istrue = 0;
  for (i = 0; i <= 6; i++) {
    if (gameBoard[0][i] == EMPTY) {
      istrue = 0;
      j = 5;
      while (j >= 0 && istrue == 0) {
        if (gameBoard[j][i] == EMPTY) {
          gameBoard[j][i] = 2;
          istrue = 1;
        }
        j--;
      }
      j++;
    }
    if (istrue == 1) {
      if (hasWinner(gameBoard) != 1) {
        gameBoard[j][i] = EMPTY;
      }
      if (hasWinner(gameBoard) == 1) {
        return;
      }
    }
  }
  for (i = 0; i <= 6; i++) {
    if (gameBoard[0][i] == EMPTY) {
      istrue = 0;
      j = 5;
      while (j >= 0 && istrue == 0) {
        if (gameBoard[j][i] == EMPTY) {
          gameBoard[j][i] = 1;
          istrue = 1;
        }
        j--;
      }
      j++;
    }
    if (istrue == 1) {
      if (hasWinner(gameBoard) != 1) {
        gameBoard[j][i] = EMPTY;
      }
      if (hasWinner(gameBoard) == 1) {
        gameBoard[j][i] = 2;
        return;
      }
    }
  }
  for (i = 5; i >= 0; i--) {
    for (j = 6; j >= 0; j--) {
      if (gameBoard[i][j] == EMPTY) {
        gameBoard[i][j] = 2;
        return;
      }
    }
  }
}

/* The main function */
int main()
{
    /* Local variables */
    int gameBoard[6][7];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1             2: Player 2
    int gameContinue;       // 1: The game continues   0: The game ends
    int numOfHumanPlayers;  // 1 or 2

    /* Initialize the local variables */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameContinue = 1;
    printf("Enter the number of human players [1-2]:\n");
    scanf("%d", &numOfHumanPlayers);    // You can assume that the user input must be valid

    /* Uncomment the following statements to test whether the printGameBoard() and the placeMarkByHumanPlayer() functions
       are implemented correctly.
       You can add more if you wish.
       After testing, you can delete them or move them elsewhere. */
    if (numOfHumanPlayers == 2) {
      currentPlayer = 1;
      printGameBoard(gameBoard);
      while (gameContinue == 1) {
        printf("Player %d's turn\n", currentPlayer);
        if (currentPlayer == 1) {
          placeMarkByHumanPlayer(gameBoard, CIRCLE);
        }
        else if (currentPlayer == 2) {
          placeMarkByHumanPlayer(gameBoard, CROSS);
        }
        printGameBoard(gameBoard);
        if (hasWinner(gameBoard) == 1 || isFull(gameBoard) == 1) {
          gameContinue = 0;
        }
        else if (currentPlayer == 1) {
          currentPlayer = 2;
        }
        else if (currentPlayer == 2) {
          currentPlayer = 1;
        }
      }
      if (hasWinner(gameBoard) == 1 && currentPlayer == 1) {
        printf("Congratulations! Player 1 wins!\n");
      }
      else if (hasWinner(gameBoard) == 1 && currentPlayer == 2) {
        printf("Congratulations! Player 2 wins!\n");
      }
      else if (isFull(gameBoard) == 1) {
        printf("Draw game.\n");
      }
    }
    else if (numOfHumanPlayers == 1) {
      currentPlayer = 1;
      printGameBoard(gameBoard);
      while (gameContinue == 1) {
        printf("Player %d's turn\n", currentPlayer);
        if (currentPlayer == 1) {
          placeMarkByHumanPlayer(gameBoard, CIRCLE);
        }
        else if (currentPlayer == 2) {
          placeMarkByComputerPlayer(gameBoard);
        }
        printGameBoard(gameBoard);
        if (hasWinner(gameBoard) == 1 || isFull(gameBoard) == 1) {
          gameContinue = 0;
        }
        else if (currentPlayer == 1) {
          currentPlayer = 2;
        }
        else if (currentPlayer == 2) {
          currentPlayer = 1;
        }
      }
      if (hasWinner(gameBoard) == 1 && currentPlayer == 1) {
        printf("Congratulations! Player 1 wins!\n");
      }
      else if (hasWinner(gameBoard) == 1 && currentPlayer == 2) {
        printf("Computer wins!\n");
      }
      else if (isFull(gameBoard) == 1) {
        printf("Draw game.\n");
      }
    }

    /* Game start
       If there are two human players, they are Player 1 and Player 2
       If there is only one human player, he/she is Player 1 and another player is the computer player
       For both cases, Player 1 moves first and places the CIRCLE mark; while Player 2 (or the computer player) places the CROSS mark
       Hint: use a while loop */

    // TODO : Complete this part

    return 0;
}
