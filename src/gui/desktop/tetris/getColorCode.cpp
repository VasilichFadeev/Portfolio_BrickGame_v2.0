#include "../../../brick_game/tetris/tetris_game.h"


/**
 * @brief Преобразует цвет фигуры в HTML-строку
 *
 * @param color Цвет фигуры
 * @return QString с HTML-кодом цвета
 */
QString getColorCode(PieceColor color) {
  switch (color) {
    case PINK:
      return "#FFC0CB";
    case RED:
      return "#FF0000";
    case ORANGE:
      return "#FFA500";
    case YELLOW:
      return "#FFFF00";
    case GREEN:
      return "#00FF00";
    case BLUE:
      return "#0000FF";
    case PURPLE:
      return "#800080";
    default:
      return "#FFFFFF";
  }
}