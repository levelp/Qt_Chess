#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QFrame>
#include "chesspiece.h"

#include "addition.h"
#include <QVector>

namespace Ui {
class ChessBoard;
}

// Шахматная доска - опредение
// ---------------------------
class ChessBoard : public QFrame {
  Q_OBJECT


 public:
  //получаем доступные для хода клетки
  QVector<Area> getTurnArea(ChessPiece* piece);
  explicit ChessBoard(QWidget* parent = 0);
  ~ChessBoard();
  // Загрузка доски из файла
  void loadFile(QString fileName);
  void fillEndOfGame(PlayerSide side);
  // Загрузка доски из ресурса
  void loadRes(QString fileName);

  void clearAvMoves();
  // Доступные ходы
  status avMoves[8][8];

 protected:
  void dragEnterEvent(QDragEnterEvent* event);
  void dragMoveEvent(QDragMoveEvent* event);
  void dropEvent(QDropEvent* event);
  void mousePressEvent(QMouseEvent* event);

  // Текущая фигура
  ChessPiece* cur;

 private:
  //соответствие клеткам и фигурам, которые ими заняты, тоесть расположение фигур на доске
  ChessPiece* boardMap[8][8];
  //все поля которые не простреливаются фигурами противника, необходимо для определения ходов короля/шах/мат
  bool endOfGame[8][8];

  //получаем статус клетки занята/свободна/занята фигурой противника
  status getPoleStatus(int row, int col, PlayerSide side);
  QVector<Area> getDiagonalStatus(int row, int col, PlayerSide side);
  QVector<Area> getHorizontalStatus(int row, int col, PlayerSide side);
  Ui::ChessBoard* ui;
};

#endif // CHESSBOARD_H
