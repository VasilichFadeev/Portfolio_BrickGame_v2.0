#ifndef DESKTOP_SNAKE_H
#define DESKTOP_SNAKE_H

#include <QApplication>
#include <QFile>
#include <QFont>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <random>
#include <vector>

/**
 * @brief Размеры и параметры поля игры.
 */
const int WIDTH = 12;
const int HEIGHT = 22;
const int FIELD_W = 10;
const int FIELD_H = 20;
const int MAX_LEVEL = 10;
const int WIN_LENGTH = 200;
const QString HIGH_SCORE_FILE = "snake_high_score.txt";

/**
 * @brief Возможные действия пользователя.
 */
enum UserAction_t { Start, Pause, Terminate, Left, Right, Up, Down, Action };

/**
 * @brief Структура состояния игры для передачи данных.
 */
typedef struct {
  int **field; /**< Текущее поле игры (числовое представление) */
  int **next; /**< Следующее поле (для анимации/состояния) */
  int score;      /**< Текущий счёт */
  int high_score; /**< Рекорд */
  int level;      /**< Текущий уровень */
  int speed;      /**< Скорость игры */
  int pause;      /**< Флаг паузы */
} GameInfo_t;

/**
 * @brief Координаты сегмента змеи.
 */
struct SnakeSegment {
  int y; /**< Координата по вертикали */
  int x; /**< Координата по горизонтали */
};

namespace s21 {
/**
 * @brief Основной класс десктопной змейки на Qt.
 */
class SnakeWindow : public QWidget {
 public:
  /**
   * @brief Конструктор.
   * @param parent Родительский виджет
   */
  explicit SnakeWindow(QWidget *parent = nullptr);

  /** @brief Генерация яблока на поле */
  void generateApple();

  /**
   * @brief Получение текущего поля.
   * @return Указатель на поле
   */
  QChar (*getField() const)[WIDTH] {
    return const_cast<QChar(*)[WIDTH]>(field);
  }

  /** @brief Очистка игрового поля */
  void clearField();

  /** @brief Получить рекорд */
  int getHighScore() { return highScore; }

  /** @brief Проверка, выиграна ли игра */
  bool getGameWon() { return gameWon; }

  /** @brief Проверка, окончена ли игра */
  bool getGameOver() { return gameOver; }

  /** @brief Проверка состояния паузы */
  bool getGamePaused() { return gamePaused; }

  /** @brief Проверка состояния турбо */
  bool getIsTurbo() { return isTurbo; }

  /** @brief Получить текущий уровень */
  int getCurrentLevel() { return currentLevel; }

  /** @brief Получить текущий счёт */
  int getCurrentScore() { return currentScore; }

  /** @brief Вспомогательная функция для теста: запуск игры */
  void StartInTestStartGame() { startGame(); }

  /** @brief Вспомогательная функция для теста: переключение паузы */
  void StartInTestTogglePause() { togglePause(); }

  /** @brief Вспомогательная функция для теста: переключение турбо */
  void StartInTestToggleTurbo() { toggleTurbo(); }

  /** @brief Вспомогательная функция для теста: обновление скорости */
  void StartInTestUpdateSpeed() { updateSpeed(); }

  /** @brief Получить таймер игры */
  QTimer *getTimer() { return timer; }

  /** @brief Загрузка рекорда из файла */
  void loadHighScore();

  /** @brief Сохранение рекорда в файл */
  void saveHighScore();

  /** @brief Сброс игры */
  void resetGame();

 private:
  QTimer *timer;     /**< Таймер игры */
  QLabel *gameLabel; /**< Метка для отображения поля */
  QPushButton *startButton;        /**< Кнопка старт */
  QChar field[HEIGHT][WIDTH];      /**< Игровое поле */
  std::vector<SnakeSegment> snake; /**< Сегменты змеи */
  int directionX;   /**< Направление движения по X */
  int directionY;   /**< Направление движения по Y */
  bool gameOver;    /**< Флаг окончания игры */
  bool gamePaused;  /**< Флаг паузы */
  bool gameWon;     /**< Флаг победы */
  bool isTurbo;     /**< Флаг турбо */
  int currentScore; /**< Текущий счёт */
  int highScore;    /**< Рекорд */
  int currentLevel; /**< Текущий уровень */

  /** @brief Заполнить поле рамкой */
  void fillFieldWithFrame();

  /** @brief Спавн змеи на поле */
  void spawnSnake();

  /** @brief Настройка интерфейса */
  void setupUI();

  /** @brief Настройка таймера игры */
  void setupTimer();

  /** @brief Запуск игры */
  void startGame();

  /** @brief Переключение паузы */
  void togglePause();

  /** @brief Переключение турбо */
  void toggleTurbo();

  /** @brief Обновление скорости в зависимости от уровня */
  void updateSpeed();

  /** @brief Основной игровой цикл */
  void updateGame();

  /** @brief Обработка нажатий клавиш */
  void keyPressEvent(QKeyEvent *event);

  /** @brief Обновление отображения поля */
  void updateGameDisplay();

  /** @brief Получение текущего состояния игры */
  GameInfo_t updateCurrentState();
};
}  // namespace s21

#endif