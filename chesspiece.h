#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QLabel>
#include <QMetaEnum>
#include <QStaticAssertFailure>
#include "game.h"

class ChessBoard;

// Шахматная фигура
class ChessPiece : public QLabel {
  Q_OBJECT

 public:
  static int count; // Количество созданных фигур (для отладки)
  int id; // Идентификатор фигуры

  // parent - шахматная доска
  // side - цвет: чёрный / белый
  // type - тип фигуры
  // row, col - строка и столбец 0..7
  ChessPiece(ChessBoard* parent, PlayerSide side, PieceType type,
             int row, int col);
  ~ChessPiece();

  PlayerSide side; // Белая / чёрная
  PieceType type; // Тип фигуры: пешка, ладья, конь, слон, ферзь, король

  int row, col; // row - строка, col - столбец (0..7)

  // Выровнять фигуру по сетке
  void alignToGrid();
};

#endif // CHESSPIECE_H
