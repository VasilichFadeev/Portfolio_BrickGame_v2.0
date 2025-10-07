#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#define _POSIX_C_SOURCE 199309L
#include <locale.h>
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#define WIDTH 12
#define HEIGHT 22
#define WINDOW_WIDTH 35
#define PINK_COLOR 213
#define ORANGE_COLOR 208
#define PURPLE_COLOR 90
#define PINK_PAIR 1
#define RED_PAIR 2
#define ORANGE_PAIR 3
#define YELLOW_PAIR 4
#define GREEN_PAIR 5
#define BLUE_PAIR 6
#define PURPLE_PAIR 7
#define HIGH_SCORE_FILE "tetris_high_score.txt"

typedef struct {
  int x, y;
  int shape[4][4];
  int size;
  int color_pair;
} Tetromino;

int readHighScore();
void writeHighScore(int score);
int checkCollision(int nx, int ny, const int shape[4][4],
                   const int field[HEIGHT][WIDTH]);
void mergeTetromino(const Tetromino *t, int field[HEIGHT][WIDTH]);
void rotate(int shape[4][4], int result[4][4]);
void initNextTetromino(Tetromino *t);
void spawnTetromino(Tetromino *current, Tetromino *next);
void clearLines(int *points, int *level, int field[HEIGHT][WIDTH]);
int calculateSpeed(int level);
int handleTick(int *tick, Tetromino *current, Tetromino *next,
               int field[HEIGHT][WIDTH], int *points, int *level,
               int *highScore);
void sleepWithLevel(int level);

void drawPauseScreen();
void drawField(int points, int level, int speed, int highScore,
               int field[HEIGHT][WIDTH]);
void drawTetromino(Tetromino *t);
extern int shapes[7][4][4];
void handleInput(int key, Tetromino *t, int *paused, int field[HEIGHT][WIDTH]);
void drawNextTetromino(Tetromino *t);
void setupTerminal();
void setupColors();
void renderGame(int field[HEIGHT][WIDTH], Tetromino *current, Tetromino *next,
                int points, int level, int highScore, int paused,
                int first_move);
int handleQuit(int ch);

#endif