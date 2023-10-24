#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Define constants
#define BOARD_SIZE 3
const char PLAYER = 'X';
const char COMPUTER = 'O';

char board[BOARD_SIZE][BOARD_SIZE];

void resetBoard();
void displayBoard();
int countFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main() {
    char winner = ' ';
    char response;

    do {
        winner = ' ';
        response = ' ';
        resetBoard();

        while (winner == ' ' && countFreeSpaces() != 0) {
            displayBoard();
            playerMove();
            winner = checkWinner();

            if (winner != ' ' || countFreeSpaces() == 0) {
                break;
            }

            computerMove();
            winner = checkWinner();

            if (winner != ' ' || countFreeSpaces() == 0) {
                break;
            }
        }

        displayBoard();
        printWinner(winner);

        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response);
        response = toupper(response);
    } while (response == 'Y');

    printf("Thanks for playing!\n");

    return 0;
}

void resetBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int countFreeSpaces() {
    int freeSpaces = BOARD_SIZE * BOARD_SIZE;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove() {
    int x, y;

    do {
        printf("Enter row #(1-%d): ", BOARD_SIZE);
        scanf("%d", &x);
        printf("Enter column #(1-%d): ", BOARD_SIZE);
        scanf("%d", &y);
        x--;
        y--;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != ' ') {
            printf("Invalid move!\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (1);
}

void computerMove() {
    // Seed the random number generator (once)
    static int seeded = 0;
    if (!seeded) {
        srand(time(0));
        seeded = 1;
    }

    int x, y;

    if (countFreeSpaces() > 0) {
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    } else {
        printWinner(' ');
    }
}

char checkWinner() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }

    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER) {
        printf("YOU WIN!\n");
    } else if (winner == COMPUTER) {
        printf("YOU LOSE!\n");
    } else {
        printf("IT'S A TIE!\n");
    }
}
