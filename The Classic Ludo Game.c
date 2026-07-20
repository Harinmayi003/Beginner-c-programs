
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLAYERS 4
#define TOKENS 4

typedef struct {
    int position[TOKENS]; // -1 means not yet on board
} Player;

void initPlayers(Player players[]) {
    for (int i = 0; i < PLAYERS; i++) {
        for (int j = 0; j < TOKENS; j++) {
            players[i].position[j] = -1;
        }
    }
}

int rollDice() {
    return (rand() % 6) + 1;
}

void moveToken(Player *p, int tokenIndex, int steps) {
    if (p->position[tokenIndex] == -1 && steps == 6) {
        p->position[tokenIndex] = 0; // enter board
    } else if (p->position[tokenIndex] >= 0) {
        p->position[tokenIndex] += steps;
        if (p->position[tokenIndex] >= 57) { // typical Ludo path length
            p->position[tokenIndex] = 57; // finished
        }
    }
}

void printBoard(Player players[]) {
    for (int i = 0; i < PLAYERS; i++) {
        printf("Player %d: ", i+1);
        for (int j = 0; j < TOKENS; j++) {
            printf("%d ", players[i].position[j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    Player players[PLAYERS];
    initPlayers(players);

    int currentPlayer = 0;
    int turns = 20; // demo limit

    while (turns--) {
        printf("\nPlayer %d's turn:\n", currentPlayer+1);
        int dice = rollDice();
        printf("Rolled: %d\n", dice);

        // For demo: always move first token
        moveToken(&players[currentPlayer], 0, dice);

        printBoard(players);

        currentPlayer = (currentPlayer + 1) % PLAYERS;
    }

    return 0;
}
