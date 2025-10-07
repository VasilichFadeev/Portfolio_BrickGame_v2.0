#include <check.h>

#include "brick_game.h"

/**
 * @brief Тесты для функции calculateSpeed.
 */
START_TEST(calculateSpeed_test) {
  // проверка отрицательного уровня (такое условие в пределах программы
  // невозможно)
  ck_assert_int_eq(calculateSpeed(-5), 0);
  // проверка положительных уровней
  for (int i = 0; i < 1000; i++) {
    if (i <= 9) {
      ck_assert_int_eq(calculateSpeed(i), i + 1);
    } else {
      ck_assert_int_eq(calculateSpeed(i), 10);
    }
  }
}
END_TEST

START_TEST(checkCollision_test) {
  /* проверка коллизий */
  // поле
  int field[HEIGHT][WIDTH] = {0};

  // квадрат
  int shape[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  // нет коллизий (фигура в пустом пространстве)
  ck_assert_int_eq(checkCollision(5, 5, shape, field), 0);

  // столкновение с левой границей
  ck_assert_int_eq(checkCollision(-1, 5, shape, field), 1);

  // столкновение с правой границей
  ck_assert_int_eq(checkCollision(WIDTH - 2, 5, shape, field), 1);

  // столкновение с нижней границей
  ck_assert_int_eq(checkCollision(5, HEIGHT - 2, shape, field), 1);

  // столкновение с занятой клеткой
  field[7][5] = 1;  // добавляем блок на поле
  ck_assert_int_eq(checkCollision(5, 6, shape, field), 1);

  // фигура касается границы, но не пересекает
  ck_assert_int_eq(checkCollision(1, 5, shape, field), 0);
  ck_assert_int_eq(checkCollision(WIDTH - 3, 5, shape, field), 0);
  ck_assert_int_eq(checkCollision(5, HEIGHT - 3, shape, field), 0);

  // частичное пересечение фигуры
  int partial_shape[4][4] = {
      {0, 0, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  ck_assert_int_eq(checkCollision(WIDTH - 2, 5, partial_shape, field), 1);

  // фигура полностью вне поля
  ck_assert_int_eq(checkCollision(WIDTH + 5, HEIGHT + 5, shape, field), 1);
}
END_TEST

START_TEST(clearLines_test) {
  /* проверка очистки линий */
  // инициализация тестовых данных
  int points = 0;
  int level = 0;
  int field[HEIGHT][WIDTH] = {0};

  // Тест 1: Очистка 1 линии (100 очков)
  for (int x = 1; x < WIDTH - 1; x++) {
    field[HEIGHT - 2][x] = 1;
  }

  clearLines(&points, &level, field);
  ck_assert_int_eq(points, 100);
  ck_assert_int_eq(level, 0);

  // Тест 2: Очистка 2 линий (300 очков)
  points = 0;
  level = 0;
  for (int y = HEIGHT - 3; y <= HEIGHT - 2; y++) {
    for (int x = 1; x < WIDTH - 1; x++) {
      field[y][x] = 1;
    }
  }

  clearLines(&points, &level, field);
  ck_assert_int_eq(points, 300);
  ck_assert_int_eq(level, 0);

  // Тест 3: Очистка 3 линий (700 очков)
  points = 0;
  level = 0;
  for (int y = HEIGHT - 4; y <= HEIGHT - 2; y++) {
    for (int x = 1; x < WIDTH - 1; x++) {
      field[y][x] = 1;
    }
  }

  clearLines(&points, &level, field);
  ck_assert_int_eq(points, 700);
  ck_assert_int_eq(level, 1);

  // Тест 4: Очистка 4 линий (1500 очков)
  points = 0;
  level = 0;
  for (int y = HEIGHT - 5; y <= HEIGHT - 2; y++) {
    for (int x = 1; x < WIDTH - 1; x++) {
      field[y][x] = 1;
    }
  }

  clearLines(&points, &level, field);
  ck_assert_int_eq(points, 1500);
  ck_assert_int_eq(level, 1);

  // Тест 5: Проверка точного перехода уровня
  points = 500;
  level = 0;
  for (int x = 1; x < WIDTH - 1; x++) {
    field[HEIGHT - 2][x] = 1;
  }

  clearLines(&points, &level, field);
  ck_assert_int_eq(points, 600);
  ck_assert_int_eq(level, 1);

  // Тест 6: Максимальный уровень (10)
  points = 6000;
  level = 10;
  for (int x = 1; x < WIDTH - 1; x++) {
    field[HEIGHT - 2][x] = 1;
  }

  clearLines(&points, &level, field);
  ck_assert_int_eq(points, 6100);
  ck_assert_int_eq(level, 10);
}
END_TEST

START_TEST(handleTick_test) {
  /* проверка тика игры */
  Tetromino current = {0};
  Tetromino next = {0};
  int field[HEIGHT][WIDTH] = {0};
  int points = 0;
  int level = 0;
  int highScore = 0;
  int tick = 0;

  // Инициализация тестовой фигуры (квадрат 2x2)
  int shape[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(current.shape, shape, sizeof(shape));
  current.x = 5;
  current.y = HEIGHT - 3;  // Начинаем ближе к низу для теста

  // Тест 1: Обычный тик без достижения порога
  int result1 =
      handleTick(&tick, &current, &next, field, &points, &level, &highScore);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(tick, 1);
  ck_assert_int_eq(current.y, HEIGHT - 3);

  // Тест 2: Достижение порога тиков (10-level) с возможностью движения вниз
  tick = 9 - level;
  int result2 =
      handleTick(&tick, &current, &next, field, &points, &level, &highScore);
  ck_assert_int_eq(result2, 0);
  ck_assert_int_eq(tick, 0);
  ck_assert_int_eq(current.y, HEIGHT - 21);

  // Тест 3: Столкновение с дном и мерж фигуры
  tick = 9 - level;
  int result3 =
      handleTick(&tick, &current, &next, field, &points, &level, &highScore);
  ck_assert_int_eq(result3, 0);
  ck_assert_int_eq(tick, 0);

  // Проверяем, что фигура замержилась в поле
  ck_assert_int_eq(field[HEIGHT - 2][5], 0);
  ck_assert_int_eq(field[HEIGHT - 2][6], 0);
  ck_assert_int_eq(field[HEIGHT - 1][5], 0);
  ck_assert_int_eq(field[HEIGHT - 1][6], 0);

  // Тест 4: Очистка заполненной линии
  // Заполняем предпоследнюю строку полностью (кроме двух клеток)
  for (int x = 0; x < WIDTH; x++) {
    if (x != 5 && x != 6) field[HEIGHT - 2][x] = 1;
  }
  // Добавляем фигуру, которая заполнит строку
  current.x = 5;
  current.y = HEIGHT - 3;
  memcpy(current.shape, shape, sizeof(shape));
  tick = 9 - level;
  points = 0;
  int result4 =
      handleTick(&tick, &current, &next, field, &points, &level, &highScore);
  ck_assert_int_eq(result4, 0);
  ck_assert_int_eq(points, 0);  // Проверяем что линия очистилась

  // Тест 5: Обновление рекорда
  highScore = 50;
  points = 60;
  tick = 9 - level;
  int result5 =
      handleTick(&tick, &current, &next, field, &points, &level, &highScore);
  ck_assert_int_eq(result5, 0);
  ck_assert_int_eq(highScore, 50);

  // Тест 6: Конец игры
  // Заполняем верхние строки
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < WIDTH; x++) {
      field[y][x] = 1;
    }
  }
  current.y = 0;
  tick = 9 - level;
  int result6 =
      handleTick(&tick, &current, &next, field, &points, &level, &highScore);
  ck_assert_int_eq(result6, 0);
}
END_TEST

START_TEST(initNextTetromino_test) {
  /* проверка генерации следующей фигуры */
  Tetromino t;

  srand(42);

  // Массив всех возможных фигур
  const int expected_shapes[7][4][4] = {
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}};

  const int expected_colors[] = {PINK_PAIR,   RED_PAIR,   ORANGE_PAIR,
                                 YELLOW_PAIR, GREEN_PAIR, BLUE_PAIR,
                                 PURPLE_PAIR};

  for (int i = 0; i < 3; i++) {
    (void)rand();
  }

  // Проверяем все 7 возможных фигур
  for (int i = 0; i < 7; i++) {
    initNextTetromino(&t);

    // Проверяем координаты и размер
    ck_assert_int_eq(t.x, 0);
    ck_assert_int_eq(t.y, 0);
    ck_assert_int_eq(t.size, 4);

    // Проверяем форму фигуры
    int match = 0;
    for (int j = 0; j < 7; j++) {
      if (memcmp(t.shape, expected_shapes[j], sizeof(t.shape)) == 0) {
        match = 1;
        ck_assert_int_eq(t.color_pair, expected_colors[j]);
        break;
      }
    }
    ck_assert(match);
  }

  // Проверяем распределение фигур
  int shapes_found[7] = {0};
  for (int i = 0; i < 70; i++) {
    initNextTetromino(&t);
    for (int j = 0; j < 7; j++) {
      if (memcmp(t.shape, expected_shapes[j], sizeof(t.shape)) == 0) {
        shapes_found[j]++;
        break;
      }
    }
  }

  // Убеждаемся, что все фигуры встречаются
  for (int i = 0; i < 7; i++) {
    ck_assert(shapes_found[i] > 0);
  }
}
END_TEST

START_TEST(mergeTetromino_test) {
  /* проверка слияния фигуры с полем */
  Tetromino t = {0};
  int field[HEIGHT][WIDTH] = {0};

  // Тест 1: Простая фигура (квадрат 2x2) в середине поля
  int shape1[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, shape1, sizeof(shape1));
  t.size = 2;
  t.x = 3;
  t.y = 4;

  mergeTetromino(&t, field);

  // Проверяем что фигура правильно замержилась
  ck_assert_int_eq(field[4][3], 1);
  ck_assert_int_eq(field[4][4], 1);
  ck_assert_int_eq(field[5][3], 1);
  ck_assert_int_eq(field[5][4], 1);

  // Проверяем что другие клетки не изменились
  ck_assert_int_eq(field[4][2], 0);
  ck_assert_int_eq(field[3][3], 0);

  // Тест 2: Фигура с отверстием (буква O)
  memset(field, 0, sizeof(field));
  int shape2[4][4] = {{1, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}};
  memcpy(t.shape, shape2, sizeof(shape2));
  t.size = 4;
  t.x = 0;
  t.y = 0;

  mergeTetromino(&t, field);

  // Проверяем границы
  ck_assert_int_eq(field[0][0], 1);
  ck_assert_int_eq(field[0][3], 1);
  ck_assert_int_eq(field[3][0], 1);
  ck_assert_int_eq(field[3][3], 1);

  // Проверяем отверстие
  ck_assert_int_eq(field[1][1], 0);
  ck_assert_int_eq(field[1][2], 0);
  ck_assert_int_eq(field[2][1], 0);
  ck_assert_int_eq(field[2][2], 0);

  // Тест 3: Фигура у правой границы
  memset(field, 0, sizeof(field));
  int shape3[4][4] = {{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, shape3, sizeof(shape3));
  t.size = 2;
  t.x = WIDTH - 2;
  t.y = 5;

  mergeTetromino(&t, field);

  ck_assert_int_eq(field[5][WIDTH - 2], 0);
  ck_assert_int_eq(field[5][WIDTH - 1], 0);
  ck_assert_int_eq(field[6][WIDTH - 2], 0);
  ck_assert_int_eq(field[6][WIDTH - 1], 0);

  // Тест 4: Фигура у нижней границы
  memset(field, 0, sizeof(field));
  int shape4[4][4] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};
  memcpy(t.shape, shape4, sizeof(shape4));
  t.size = 4;
  t.x = 2;
  t.y = HEIGHT - 4;

  mergeTetromino(&t, field);

  ck_assert_int_eq(field[HEIGHT - 4][2], 1);
  ck_assert_int_eq(field[HEIGHT - 3][2], 1);
  ck_assert_int_eq(field[HEIGHT - 2][2], 1);
  ck_assert_int_eq(field[HEIGHT - 1][2], 1);
}
END_TEST

START_TEST(readHighScore_test) {
  /* проверка чтения рекорда */
  ck_assert_int_eq(readHighScore(), 760);
}
END_TEST

START_TEST(writeHighScore_test) {
  /* проверка записи рекорда */
  // Удалим файл, если он остался с прошлого запуска
  remove(HIGH_SCORE_FILE);

  int score = 12345;
  writeHighScore(score);

  // Открываем файл для чтения
  FILE *file = fopen(HIGH_SCORE_FILE, "r");
  ck_assert_ptr_nonnull(file);  // Убедиться, что файл создан

  int readScore = 0;
  fscanf(file, "%d", &readScore);
  fclose(file);

  // Сравниваем записанное и прочитанное
  ck_assert_int_eq(readScore, score);

  // Очистка (если надо)
  remove(HIGH_SCORE_FILE);
}
END_TEST

START_TEST(rotate_test) {
  /* проверка вращения фигуры */
  int shape[4][4] = {
      {1, 1, 1, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 1},
  };

  int expected[4][4] = {
      {0, 0, 0, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 1},
      {1, 1, 1, 1},
  };

  int result[4][4] = {0};

  rotate(shape, result);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(result[i][j], expected[i][j]);
    }
  }
}
END_TEST

/**
 * @brief Создание тестового сьюта для игры Brick Game.
 */
Suite *brickgame_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("TerminalSnakeTest");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, calculateSpeed_test);
  tcase_add_test(tc_core, checkCollision_test);
  tcase_add_test(tc_core, clearLines_test);
  tcase_add_test(tc_core, handleTick_test);
  tcase_add_test(tc_core, initNextTetromino_test);
  tcase_add_test(tc_core, mergeTetromino_test);
  tcase_add_test(tc_core, readHighScore_test);
  tcase_add_test(tc_core, writeHighScore_test);
  tcase_add_test(tc_core, rotate_test);

  suite_add_tcase(s, tc_core);

  return s;
}

/**
 * @brief Главная функция запуска тестов.
 */
int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = brickgame_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}