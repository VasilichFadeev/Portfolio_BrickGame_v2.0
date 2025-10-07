#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <QChar>
#include <QString>
#include <random>
#include <vector>

/** @brief Ширина игрового поля (без границ) */
const int FIELD_W = 10;

/** @brief Высота игрового поля (без границ) */
const int FIELD_H = 20;

/** @brief Ширина поля с границами */
const int WIDTH = FIELD_W + 2;

/** @brief Высота поля с границами */
const int HEIGHT = FIELD_H + 2;

/** @brief Возможные действия пользователя */
enum UserAction_t { Start, Pause, Terminate, Left, Right, Up, Down, Action };

/** @brief Цвета фигур */
enum PieceColor { PINK = 0, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };

/** @brief Структура, представляющая тетрис-фигуру */
struct Piece {
  int shape[4][4];  /**< Матрица 4x4 для формы фигуры */
  PieceColor color; /**< Цвет фигуры */
};

/**
 * @brief Класс для управления логикой игры Тетрис
 */
namespace s21 {
/**
 * @brief Основной класс десктопного тетриса на Qt.
 */
class TetrisGame {
 public:
  /** @brief Конструктор по умолчанию */
  TetrisGame();

  /** @brief Сброс игры до начального состояния */
  void reset();

  /** @brief Обработка пользовательского ввода
   *  @param action Действие пользователя
   */
  void userInput(UserAction_t action);

  /** @brief Обновление состояния игры
   *  @return true, если игра продолжается, false если окончена
   */
  bool update();

  /** @brief Получение текстового представления игрового поля в HTML
   *  @return HTML-строка с визуализацией поля
   */
  QString render() const;

  /** @brief Получить текущую скорость игры (мс между падениями фигуры) */
  int getSpeed() const;

  /** @brief Проверка, приостановлена ли игра */
  bool isPaused() const;

  /** @brief Получение текущего рекорда */
  int getHighScore() const { return highScore; }

  /** @brief Загрузка рекорда из файла */
  void loadHighScore();

  /** @brief Сохранение рекорда в файл */
  void saveHighScore();

  /** @brief Создание новой фигуры и установка ее текущей позиции */
  void spawnPiece();

  /** @brief Проверка допустимости позиции фигуры на поле
   *  @param shape Форма фигуры
   *  @param x Координата X верхнего левого угла фигуры
   *  @param y Координата Y верхнего левого угла фигуры
   *  @return true, если фигура помещается, false при столкновении
   */
  bool isValid(const int shape[4][4], int x, int y) const;

  /** @brief Размещает текущую фигуру на поле */
  void placePiece();

  /** @brief Проверяет заполненные линии и удаляет их, начисляя очки */
  void checkLines();

  /** @brief Получить координату X текущей фигуры */
  int getCurrentX() const { return currentX; }

  /** @brief Получить координату Y текущей фигуры */
  int getCurrentY() const { return currentY; }

  /** @brief Получить текущий счёт */
  int getScore() const { return score; }

  /** @brief Получить текущий уровень */
  int getLevel() const { return level; }

  /** @brief Получить текущую фигуру */
  const Piece& getCurrentPiece() const { return currentPiece; }

  /** @brief Получить следующую фигуру */
  const Piece& getNextPiece() const { return nextPiece; }

  /** @brief Получить ширину поля */
  int getWidth() { return WIDTH; }

  /** @brief Получить высоту поля */
  int getHeight() { return HEIGHT; }

  /** @brief Игровое поле символами */
  std::vector<std::vector<QChar>> field;

  /** @brief Цвета ячеек игрового поля */
  std::vector<std::vector<QString>> colors;
  int score = 0; /**< Текущий счёт */

 private:
  std::vector<Piece> pieces; /**< Все фигуры */
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dist;

  int highScore = 0;  /**< Рекорд */
  int level = 1;      /**< Текущий уровень */
  int speed = 400;    /**< Скорость игры в мс */
  bool pause = false; /**< Флаг паузы */

  Piece currentPiece; /**< Текущая фигура */
  Piece nextPiece;    /**< Следующая фигура */
  int currentX = 4;   /**< Координата X текущей фигуры */
  int currentY = 1;   /**< Координата Y текущей фигуры */
};
}  // namespace s21

/** @brief Получение цвета фигуры в формате HTML
 *  @param color Цвет фигуры
 *  @return Строка с HTML-цветом
 */
QString getColorCode(PieceColor color);

#endif  // TETRIS_GAME_H