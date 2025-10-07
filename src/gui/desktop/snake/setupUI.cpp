#include "../../../brick_game/snake/desktop_snake/desktop_snake.h"

namespace s21 {
/**
 * @brief Настраивает графический интерфейс окна игры.
 *
 * Создает:
 * - кнопку "START GAME" для запуска игры,
 * - текстовое поле gameLabel для отображения игрового поля.
 *
 * Использует QVBoxLayout для размещения элементов.
 */
void SnakeWindow::setupUI() {
  setWindowTitle("Snake Game");
  resize(200, 350);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  startButton = new QPushButton("START GAME", this);
  startButton->setStyleSheet(
      "QPushButton {"
      "  background-color: white;"
      "  color: black;"
      "  font-size: 24px;"
      "  font-weight: bold;"
      "  border: none;"
      "}"
      "QPushButton:hover {"
      "  background-color: #D3D3D3;"
      "}");
  startButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  connect(startButton, &QPushButton::clicked, this, &SnakeWindow::startGame);

  gameLabel = new QLabel(this);
  gameLabel->setTextFormat(Qt::RichText);
  gameLabel->setFont(QFont("Monospace", 12));
  gameLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  gameLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  gameLabel->hide();

  layout->addWidget(startButton);
  layout->addWidget(gameLabel);
  setLayout(layout);
}
}  // namespace s21