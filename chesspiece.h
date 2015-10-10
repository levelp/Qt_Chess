#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QLabel>
#include <QMetaEnum>
#include <QStaticAssertFailure>
#include "game.h"
#include <QVector>

class ChessBoard;

// Шахматная фигура
class ChessPiece : public QLabel {
  Q_OBJECT

 public:

  ChessPiece(ChessBoard* parent, PlayerSide side, PieceType type,
             int row, int col);
  ~ChessPiece();

  void setSide(PlayerSide pSide) {
    side = pSide;
  }
  void setRow(int pRow) {
    row = pRow;
  }
  void setCol(int pCol) {
    col = pCol;
  }
  void setId(int pId) {
    id = pId;
  }
  void setType(PieceType pType) {
    type = pType;
  }
  void setTurn(int pTurn) {
    turn = pTurn;
  }
  int getId() {
    return id;
  }
  PieceType getType() {
    return type;
  }
  PlayerSide getSide() {
    return side;
  }
  int getRow() {
    return row;
  }
  int getCol() {
    return col;
  }
  int getTurn() {
    return turn;
  }
  // Выровнять фигуру по сетке
  void alignToGrid();
 private:
  static int count; // Количество созданных фигур (для отладки)
  int id; // Идентификатор фигуры
  // parent - шахматная доска
  // side - цвет: чёрный / белый
  // type - тип фигуры
  // row, col - строка и столбец 0..7
  PlayerSide side; // Белая / чёрная
  PieceType type;
  //параметр указывающий ход на котором сделано некоторое действие. Для пешек-первый ход, для короля-рокировка, для ладьй-первый ход
  signed int turn;
  int row, col; // row - строка, col - столбец (0..7)

};



#endif // CHESSPIECE_H
