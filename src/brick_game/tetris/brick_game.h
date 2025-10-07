#ifndef BRICK_GAME_H
#define BRICK_GAME_H

/**
 * @file brick_game.h
 * @brief Заголовочный файл консольной версии игры "Тетрис".
 *
 * Содержит определения структур, констант и функций, необходимых для работы
 * логики тетриса (управление фигурами, коллизии, счёт, уровни и отрисовка).
 */

#define _POSIX_C_SOURCE 199309L
#include <locale.h>
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

/** @brief Ширина игрового поля (включая границы). */
#define WIDTH 12
/** @brief Высота игрового поля (включая границы). */
#define HEIGHT 22
/** @brief Ширина окна терминала. */
#define WINDOW_WIDTH 35

/** @brief Код розового цвета. */
#define PINK_COLOR 213
/** @brief Код оранжевого цвета. */
#define ORANGE_COLOR 208
/** @brief Код фиолетового цвета. */
#define PURPLE_COLOR 90

/** @brief Цветовые пары для фигур. */
#define PINK_PAIR 1
#define RED_PAIR 2
#define ORANGE_PAIR 3
#define YELLOW_PAIR 4
#define GREEN_PAIR 5
#define BLUE_PAIR 6
#define PURPLE_PAIR 7

/** @brief Файл, в котором хранится рекорд тетриса. */
#define HIGH_SCORE_FILE "tetris_high_score.txt"

/**
 * @struct Tetromino
 * @brief Структура, описывающая фигуру (тетромино).
 */
typedef struct {
  int x;            ///< Позиция фигуры по оси X.
  int y;            ///< Позиция фигуры по оси Y.
  int shape[4][4];  ///< Матрица формы фигуры 4x4.
  int size;         ///< Размер используемой матрицы.
  int color_pair;   ///< Цвет фигуры (ncurses color pair).
} Tetromino;

/**
 * @brief Считывает рекорд из файла.
 * @return Рекорд (0, если файл отсутствует).
 */
int readHighScore();

/**
 * @brief Записывает рекорд в файл.
 * @param score Рекордное значение.
 */
void writeHighScore(int score);

/**
 * @brief Проверяет, произойдёт ли коллизия фигуры с полем.
 * @param nx Новая позиция по оси X.
 * @param ny Новая позиция по оси Y.
 * @param shape Матрица фигуры 4x4.
 * @param field Игровое поле.
 * @return 1 — если есть коллизия, 0 — если движения возможно.
 */
int checkCollision(int nx, int ny, const int shape[4][4],
                   const int field[HEIGHT][WIDTH]);

/**
 * @brief "Приклеивает" фигуру к полю.
 * @param t Указатель на фигуру.
 * @param field Игровое поле.
 */
void mergeTetromino(const Tetromino *t, int field[HEIGHT][WIDTH]);

/**
 * @brief Поворачивает фигуру на 90 градусов по часовой стрелке.
 * @param shape Исходная фигура 4x4.
 * @param result Результат поворота.
 */
void rotate(int shape[4][4], int result[4][4]);

/**
 * @brief Инициализирует следующую фигуру случайным образом.
 * @param t Указатель на фигуру.
 */
void initNextTetromino(Tetromino *t);

/**
 * @brief Перемещает фигуру из "next" в "current" и генерирует новую "next".
 * @param current Текущая фигура.
 * @param next Следующая фигура.
 */
void spawnTetromino(Tetromino *current, Tetromino *next);

/**
 * @brief Проверяет заполненные линии, удаляет их и обновляет очки/уровень.
 * @param points Указатель на текущие очки.
 * @param level Указатель на текущий уровень.
 * @param field Игровое поле.
 */
void clearLines(int *points, int *level, int field[HEIGHT][WIDTH]);

/**
 * @brief Вычисляет скорость игры в зависимости от уровня.
 * @param level Текущий уровень.
 * @return Скорость (меньше значение → быстрее игра).
 */
int calculateSpeed(int level);

/**
 * @brief Обновляет состояние игры за один тик.
 * @param tick Счётчик тиков.
 * @param current Текущая фигура.
 * @param next Следующая фигура.
 * @param field Игровое поле.
 * @param points Очки.
 * @param level Уровень.
 * @param highScore Рекорд.
 * @return 1 — если игра окончена, 0 — иначе.
 */
int handleTick(int *tick, Tetromino *current, Tetromino *next,
               int field[HEIGHT][WIDTH], int *points, int *level,
               int *highScore);

/**
 * @brief Приостанавливает выполнение на время, зависящее от уровня.
 * @param level Текущий уровень.
 */
void sleepWithLevel(int level);

/**
 * @brief Отрисовывает экран паузы.
 */
void drawPauseScreen();

/**
 * @brief Отрисовывает поле.
 * @param points Текущий счёт.
 * @param level Текущий уровень.
 * @param speed Текущая скорость.
 * @param highScore Рекорд.
 * @param field Игровое поле.
 */
void drawField(int points, int level, int speed, int highScore,
               int field[HEIGHT][WIDTH]);

/**
 * @brief Отрисовывает фигуру.
 * @param t Указатель на фигуру.
 */
void drawTetromino(Tetromino *t);

/** @brief Глобальный массив форм фигур. */
extern int shapes[7][4][4];

/**
 * @brief Обрабатывает пользовательский ввод.
 * @param key Нажатая клавиша.
 * @param t Текущая фигура.
 * @param paused Флаг паузы.
 * @param field Игровое поле.
 */
void handleInput(int key, Tetromino *t, int *paused, int field[HEIGHT][WIDTH]);

/**
 * @brief Отрисовывает "следующую" фигуру.
 * @param t Указатель на фигуру.
 */
void drawNextTetromino(Tetromino *t);

/**
 * @brief Настраивает режим терминала (ncurses).
 */
void setupTerminal();

/**
 * @brief Настраивает цветовые пары (ncurses).
 */
void setupColors();

/**
 * @brief Отрисовывает весь экран игры.
 */
void renderGame(int field[HEIGHT][WIDTH], Tetromino *current, Tetromino *next,
                int points, int level, int highScore, int paused,
                int first_move);

/**
 * @brief Проверяет, нужно ли выйти из игры.
 * @param ch Код нажатой клавиши.
 * @return 1 — если выход, 0 — иначе.
 */
int handleQuit(int ch);

#endif