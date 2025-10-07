#ifndef SNAKE_TERMINAL_H
#define SNAKE_TERMINAL_H

#include <locale.h>
#include <ncursesw/ncurses.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @file snake_terminal.h
 * @brief Заголовочный файл с определениями классов, структур и функций
 *        для консольной версии игры "Змейка".
 */

/** @brief Ширина игрового поля (включая рамку). */
const int WIDTH = 12;
/** @brief Высота игрового поля (включая рамку). */
const int HEIGHT = 22;
/** @brief Рабочая ширина поля (без рамки). */
const int FIELD_W = 10;
/** @brief Рабочая высота поля (без рамки). */
const int FIELD_H = 20;
/** @brief Максимальный уровень игры. */
const int MAX_LEVEL = 10;
/** @brief Длина змейки, необходимая для победы. */
const int WIN_LENGTH = 200;
/** @brief Имя файла для сохранения рекорда. */
const std::string HIGH_SCORE_FILE = "snake_high_score.txt";

/**
 * @enum UserAction_t
 * @brief Возможные действия пользователя.
 */
typedef enum {
  Start,     /**< Запуск игры */
  Pause,     /**< Пауза */
  Terminate, /**< Завершение игры */
  Left,      /**< Движение влево */
  Right,     /**< Движение вправо */
  Up,        /**< Движение вверх */
  Down,      /**< Движение вниз */
  Action, /**< Действие (например, подтверждение) */
  Turbo   /**< Ускорение (турбо-режим) */
} UserAction_t;

/**
 * @struct GameInfo_t
 * @brief Состояние игры, передаваемое между логикой и интерфейсом.
 */
typedef struct {
  int **field;    /**< Текущее поле */
  int **next;     /**< Следующее состояние поля */
  int score;      /**< Текущий счёт */
  int high_score; /**< Рекорд */
  int level;      /**< Текущий уровень */
  int speed; /**< Задержка в мс (чем меньше, тем быстрее) */
  int pause; /**< Флаг паузы (1 — игра на паузе) */
} GameInfo_t;

/**
 * @struct SnakeSegment
 * @brief Сегмент змейки (координаты).
 */
struct SnakeSegment {
  int y; /**< Координата Y */
  int x; /**< Координата X */
};

namespace s21 {
/**
 * @class SnakeGame
 * @brief Основной класс игры "Змейка".
 *
 * Хранит состояние игры, управляет движением змейки, яблоками,
 * уровнями, очками и победными условиями.
 */
class SnakeGame {
 private:
  int directionX;  /**< Направление движения по оси X */
  int directionY;  /**< Направление движения по оси Y */
  bool gameOver;   /**< Флаг окончания игры */
  bool gamePaused; /**< Флаг паузы */
  bool isTurbo;    /**< Флаг турбо-режима */
  void fillFieldWithFrame(); /**< Заполняет поле рамкой */
  void spawnSnake();    /**< Создаёт начальную змейку */
  void generateApple(); /**< Генерирует новое яблоко */
  void convertFieldToInt(); /**< Конвертирует wchar_t-поле в int-поле */

 public:
  std::vector<SnakeSegment> snake; /**< Текущая змейка */
  bool gameWon;                    /**< Флаг победы */
  int currentScore;                /**< Текущий счёт */
  int currentLevel;                /**< Текущий уровень */
  int highScore;                   /**< Рекорд */
  wchar_t field[HEIGHT][WIDTH]; /**< Игровое поле (символьное) */
  int **fieldInt; /**< Игровое поле (числовое) */
  int **nextInt;  /**< Следующее состояние поля */

  SnakeGame();  /**< Конструктор */
  ~SnakeGame(); /**< Деструктор */

  int getHighScore() { return highScore; } /**< Получить рекорд */
  void setCurrentLevel(int level) {
    currentLevel = level;
  } /**< Установить уровень */
  void setTurbo(bool turbo) { isTurbo = turbo; } /**< Установить турбо-режим */
  void setPaused(bool paused) { gamePaused = paused; } /**< Установить паузу */
  int getCurrentLevel() const {
    return currentLevel;
  } /**< Получить текущий уровень */
  void loadHighScore(); /**< Загрузить рекорд из файла */
  void saveHighScore(); /**< Сохранить рекорд в файл */

  void userInput(UserAction_t action,
                 bool hold); /**< Обработка ввода пользователя */
  void updateGameInfo(GameInfo_t &info); /**< Обновить состояние игры */
  bool checkCollisionWithWalls(
      int newY, int newX); /**< Проверка столкновения со стеной */
  bool checkCollisionWithSelf(int newY,
                              int newX); /**< Проверка столкновения с собой */
  void handleCollision(GameInfo_t &info); /**< Обработка столкновения */
  void moveSnake(int newY, int newX); /**< Перемещение змейки */
  void handleAppleCollision(GameInfo_t &info, int newY,
                            int newX); /**< Обработка поедания яблока */
  void checkWinCondition(GameInfo_t &info); /**< Проверка победы */
  GameInfo_t updateCurrentState(); /**< Получить обновлённое состояние */
  bool getTurboState() const; /**< Получить состояние турбо-режима */
  bool isGameOver() const; /**< Проверить окончание игры */
};

/**
 * @brief Глобальный объект игры (используется в C-интерфейсе).
 */
extern SnakeGame *game;

extern "C" {
/**
 * @brief Обработка ввода пользователя (C-интерфейс).
 * @param action действие пользователя
 * @param hold удерживается ли кнопка
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Обновление текущего состояния игры (C-интерфейс).
 * @return структура с состоянием игры
 */
GameInfo_t updateCurrentState();

/**
 * @brief Инициализация игры (C-интерфейс).
 */
void initializeGame();

/**
 * @brief Завершение игры (C-интерфейс).
 */
void terminateGame();
}

/**
 * @brief Обработчик ввода.
 * @param paused ссылка на флаг паузы
 * @param running ссылка на флаг работы игры
 */
void inputHandler(bool &paused, bool &running);

/**
 * @brief Включение турбо-режима.
 */
void turbo();

/**
 * @brief Отрисовка игрового поля.
 * @param paused ссылка на флаг паузы
 * @param info структура с состоянием игры
 */
void drawField(bool &paused, GameInfo_t &info);

/**
 * @brief Запуск игрового цикла.
 * @param running ссылка на флаг работы игры
 * @param ch код нажатой клавиши
 * @param paused ссылка на флаг паузы
 */
void run(bool &running, int &ch, bool &paused);
}  // namespace s21

#endif