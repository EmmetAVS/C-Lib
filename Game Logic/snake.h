#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "linkedlist.h"
#define UNSET NULL
#define EMPTY 0
#define APPLE 1
#define SNAKE 2
#define SNAKE_RIGHT 3
#define SNAKE_DOWN 4
#define SNAKE_LEFT 5
#define SNAKE_UP 6

linkedList snake;
int headr, headc;
int score;
int gameover = 0;

int** initBoard(int size) {
    srand(time(NULL));
    score = 0;
    int** board = (int**)malloc(size * sizeof(int*));;
    for (int i = 0; i < size; i++) {
        board[i] = (int*)malloc(size * sizeof(int));
        for (int q = 0; q < size; q++) {
            board[i][q] = 0;
        }
    }
    snake = initLinkedList();
    board[(int) size/2][1] = SNAKE;
    board[(int) size/2][2] = SNAKE;
    board[(int) size/2][3] = SNAKE_RIGHT;
    headc = 3;
    headr = (int) size/2;
    snake.insert(&snake, &board[(int) size/2][1]);
    snake.insert(&snake, &board[(int) size/2][2]);
    snake.insert(&snake, &board[(int) size/2][3]);
    return board;
}
void generateApple(int** board, int size) {
    if (score == (size*size)-4) {
        gameover == 1;
        return;
    }
    while (1) {
        int r = (rand() % size);
        int c = (rand() % size);
        if (board[r][c] == EMPTY) {
            board[r][c] = APPLE;
            return;
        }
    }
}
int onApple(int** board, int r, int c) {
    if (board[r][c] == APPLE) {
        return 1;
    }
    return 0;
}
int onSnake(int** board, int r, int c) {
    if (board[r][c] == SNAKE || board[r][c]  == SNAKE_UP || board[r][c]  == SNAKE_LEFT || board[r][c]  == SNAKE_RIGHT || board[r][c]  == SNAKE_DOWN) {
        return 1;
    }
    return 0;
}
int moveSnake(int** board, int size, int m) {
    if (m == EMPTY || m == -1) {
        return 0;
    } else if (m == SNAKE_DOWN) {
        if (headr - 1 >= size || headr - 1 < 0) {
            return 1;
        } 
        headr = headr - 1;
    } else if (m == SNAKE_RIGHT) {
        if (headc + 1 >= size || headc + 1 < 0) {
            return 1;
        }
        headc += 1;
    } else if (m == SNAKE_LEFT) {
        if (headc - 1 >= size || headc - 1 < 0) {
            return 1;
        }
        headc -= 1;
    } else if (m == SNAKE_UP) {
        if (headr + 1 >= size || headr + 1< 0) {
            return 1;
        } 
        headr = headr + 1;
    }
    if (onSnake(board, headr, headc) == 1) {
        return 1;
    } else if (onApple(board, headr, headc) == 1) {
        //If at apple, do not delete tail
        score++;
        generateApple(board, size);
    } else {
        //Delete old tail
        *snake.tail.value = EMPTY;
        snake.remove(&snake);
    }
    *snake.head.value = SNAKE;
    board[headr][headc] = m;
    snake.insert(&snake, &board[headr][headc]);
    //Insert new head at moved to location
    return 0;
}

#endif