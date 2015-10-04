#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QFrame>
#include "chesspiece.h"

namespace Ui {
class ChessBoard;
}

// Шахматная доска - опредение
// ---------------------------
class ChessBoard : public QFrame {
  Q_OBJECT

 public:
  explicit ChessBoard(QWidget* parent = 0);
  ~ChessBoard();

  // Загрузка доски из файла
  void loadFile(QString fileName);

  // Загрузка доски из ресурса
  void loadRes(QString fileName);

 protected:
  void dragEnterEvent(QDragEnterEvent* event);
  void dragMoveEvent(QDragMoveEvent* event);
  void dropEvent(QDropEvent* event);
  void mousePressEvent(QMouseEvent* event);

  // Текущая фигура
  ChessPiece* cur;

 private:
  Ui::ChessBoard* ui;
};

#endif // CHESSBOARD_H
