#include <stdio.h>
#include <stdlib.h>

int game[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
int player = 1;
int gameover;

int gameOver(int game[3][3]) {
    for (int r = 0; r < 3; r++) {
        if (game[r][0] == game[r][1] && game[r][0] == game[r][2] && game[r][0] != 0) {
            printf("row, %d\n", r);
            return 1;
        }
    }
    for (int c = 0; c < 3; c++) {
        if (game[0][c] == game[1][c] && game[0][c] == game[2][c] && game[0][c] != 0) {
            printf("col, %d\n", c);
            return 1;
        }
    }
    if (game[0][0] == game[1][1] && game[0][0] == game[2][2] && game[0][0] != 0) {
        printf("diag 1");
        return 1;
    } else if (game[0][2] == game[1][1] && game[0][2] == game[2][0] && game[0][2] != 0) {
        printf("diag 2");
        return 1;
    } else {
        return 0;
    }
}