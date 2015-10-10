// Шахматная доска - реализация
// ----------------------------
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include "chessboard.h"
#include "ui_chessboard.h"

QVector<Area> ChessBoard::getTurnArea(ChessPiece* piece) {
  QVector<Area> sArea;
  status st;
  int max;
  PlayerSide side = piece->getSide();
  int sRow = piece->getRow();
  int sCol = piece->getCol();

  switch (piece->getType()) {
    case PAWN: {
      if(side == WHITE) {
        if(piece->getCol() == 2) max = 3;
        else max = 2;
      }

      if(side == BLACK) {
        if(piece->getCol() == 7) max = 3;
        else max = 2;
      }

      for (int var = 1; var < max; ++var) {
        if(side == WHITE) st = getPoleStatus(sRow, sCol + var, WHITE);

        if(side == BLACK) st = getPoleStatus(sRow, sCol - var, BLACK);

        if(st != DISABLE) {
          Area ar;
          ar.row = sRow;
          ar.col = sCol + var;
          ar.state = st;
          sArea.append(ar);
        }
      }

      if(side == WHITE) st = getPoleStatus(sRow - 1, sCol + 1, WHITE);

      if(side == BLACK) st = getPoleStatus(sRow - 1, sCol - 1, BLACK);

      if(st != ATTACK) {
        Area ar;
        ar.row = sRow - 1;

        if(side == WHITE) ar.col = sCol + 1;

        if(side == BLACK) ar.col = sCol - 1;

        ar.state = st;
        sArea.append(ar);
      }

      if(side == WHITE) st = getPoleStatus(sRow + 1, sCol + 1, WHITE);

      if(side == BLACK) st = getPoleStatus(sRow + 1, sCol - 1, BLACK);

      if(st != ATTACK) {
        Area ar;
        ar.row = sRow + 1;

        if(side == WHITE) ar.col = sCol + 1;

        if(side == BLACK) ar.col = sCol - 1;

        ar.state = st;
        sArea.append(ar);
      }

      return sArea;
      break;
    }

    case BISHOP: {
      return getDiagonalStatus(sRow, sCol, side);
      break;
    }

    case KNIGHT: {
      int kTurns[2][8] = {2, 1, 2, -1, 1, -2, -1, -2, -2, -1, -2, 1, -1, 2, 1, 2};

      for (int var = 0; var < 8; ++var) {
        if (getPoleStatus(sRow + kTurns[var][1], sCol + kTurns[var][2], side) != DISABLE) {
          Area ar;
          ar.row = sRow + kTurns[var][1];
          ar.col = sCol + kTurns[var][2];
          ar.state = getPoleStatus(sRow + kTurns[var][1], sCol + kTurns[var][2], side);
          sArea.append(ar);
        }
      }

      break;
    }

    case ROOK: {
      return getHorizontalStatus(sRow, sCol, side);
      break;
    }

    case QUEEN: {
      return getHorizontalStatus(sRow, sCol, side) + getDiagonalStatus(sRow, sCol, side);
      break;
    }

    case KING: {
      int kTurns[2][8] = {1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, 1};
      fillEndOfGame(side);

      for (int var = 0; var < 8; ++var) {
        if ((getPoleStatus(sRow + kTurns[var][1], sCol + kTurns[var][2], side) != DISABLE) | (endOfGame[sRow][sCol] == TRUE)) {
          Area ar;
          ar.row = sRow + kTurns[var][1];
          ar.col = sCol + kTurns[var][2];
          ar.state = getPoleStatus(sRow + kTurns[var][1], sCol + kTurns[var][2], side);
          sArea.append(ar);
        }
      }

      break;
    }

    case EMPTY: {

      break;
    }

    default: {
      break;
    }
  }

  return sArea;
}

void ChessBoard::clearAvMoves() {
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      avMoves[i][j] = DISABLE;
}

ChessBoard::ChessBoard(QWidget* parent) :
  QFrame(parent),
  ui(new Ui::ChessBoard) {
  ui->setupUi(this);
  setAcceptDrops(true);
  // Очищаем карту доступных ходов
  clearAvMoves();
}

ChessBoard::~ChessBoard() {
  delete ui;
}



const char* mimeFormat = "application/x-chesspiece";

void ChessBoard::dragEnterEvent(QDragEnterEvent* event) {
  if (event->mimeData()->hasFormat(mimeFormat)) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else
      event->acceptProposedAction();
  } else
    event->ignore();
}

void ChessBoard::dragMoveEvent(QDragMoveEvent* event) {
  if (event->mimeData()->hasFormat(mimeFormat)) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else
      event->acceptProposedAction();
  } else
    event->ignore();
}

void ChessBoard::dropEvent(QDropEvent* event) {
  if (event->mimeData()->hasFormat(mimeFormat)) {
    qDebug() << "drop" << cur->getId();

    QByteArray itemData = event->mimeData()->data(mimeFormat);
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap; // Картинка
    QPoint offset; // Смещение
    dataStream >> pixmap >> offset;

    cur->setPixmap(pixmap);

    // Перемещаем фигуру
    QPoint p = event->pos() - offset;
    int tmpRow, tmpCol;
    tmpRow = cur->getRow();
    tmpCol = cur->getCol();
    cur->setRow((p.y() + CELL / 2) / CELL);
    cur->setCol((p.x() + CELL / 2) / CELL);
    cur->alignToGrid();
    cur->show();
    cur->setAttribute(Qt::WA_DeleteOnClose);

    if (event->source() == this) {
      //привязываем к предыдущему месту пустой обьект
      boardMap[tmpRow][tmpCol] = NULL;
      //к новому месту текущий
      boardMap[cur->getRow()][cur->getCol()] = cur;
      //
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else
      event->acceptProposedAction();
  } else
    event->ignore();
}

void ChessBoard::mousePressEvent(QMouseEvent* event) {
  ChessPiece* piece = static_cast<ChessPiece*>(childAt(event->pos()));

  if (!piece)
    return;

  QVector<Area> area = getTurnArea(piece);
  //по идее тут мы должны переслать mainwindow area для перерисовки доски с доступными для ходов клетками
  cur = piece;
  qDebug() << "Move " << piece->getId() << piece->getRow() << piece->getCol();

  // Меняем подсветку карты
  QVector<Area> moves = getTurnArea(cur);

  foreach (Area a, moves) {
    avMoves[a.row][a.col] = a.state;
    qDebug() << ">> " << a.row << a.col << a.state;
  }

  QPixmap pixmap = *piece->pixmap();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << pixmap << QPoint(event->pos() - piece->pos());

  QMimeData* mimeData = new QMimeData;
  mimeData->setData(mimeFormat, itemData);

  QDrag* drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(event->pos() - piece->pos());

  QPixmap tempPixmap = pixmap;
  QPainter painter;
  painter.begin(&tempPixmap);
  painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
  painter.end();

  piece->setPixmap(tempPixmap);

  if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
    //piece->close();
  } else {
    piece->show();
    piece->setPixmap(pixmap);
  }
}

status ChessBoard::getPoleStatus(int row, int col, PlayerSide side) {
  if((row < 0) | (row > 8) | (col < 0) | (col > 8)) return DISABLE;

  if(boardMap[row][col] == NULL) return ENABLE;
  else {
    if(side == boardMap[row][col]->getSide()) return DISABLE;
    else return ATTACK;
  }
}

QVector<Area> ChessBoard::getDiagonalStatus(int row, int col, PlayerSide side) {
  QVector<Area> sArea;
  int bRow = row;
  int bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bCol++;
    bRow++;
  }

  bRow = row;
  bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bCol--;
    bRow--;
  }

  bRow = row;
  bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bCol++;
    bRow--;
  }

  bRow = row;
  bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bCol--;
    bRow++;
  }

  return sArea;
}

QVector<Area> ChessBoard::getHorizontalStatus(int row, int col, PlayerSide side) {
  QVector<Area> sArea;
  int bRow = row;
  int bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bCol++;
  }

  bRow = row;
  bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bCol--;
  }

  bRow = row;
  bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bRow--;
  }

  bRow = row;
  bCol = col;

  while (getPoleStatus(bRow, bCol, side) != DISABLE) {
    Area ar;
    ar.col = bCol;
    ar.row = bRow;
    ar.state = getPoleStatus(bRow, bCol, side);
    sArea.append(ar);
    bRow++;
  }

  return sArea;
}


// Загрузка доски из файла
void ChessBoard::loadFile(QString fileName) {
  QFile f(fileName);

  if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::critical(this, "Не могу прочитать файл",
                          QString("\"%1\" ошибка \"%2\"")
                          .arg(f.fileName()).arg(f.errorString()));

    qDebug() << "Не могу открыть: " << f.fileName() <<
             " ошибка " << f.errorString() << endl;
    return;
  }

  QTextStream in(&f);

  for(int row = 0; row < 8; ++row) {

    // Читаем очередную строчку из файла
    QString line = in.readLine();
    qDebug() << "Прочитали:" << line;

    for(int col = 0; col < 8; ++col) {
      boardMap[row][col] = NULL;
      QChar c = line.at(col);

      if(c == '_') continue;

      PlayerSide side = (c.isLower()) ? BLACK : WHITE;
      PieceType type = char2pieceType(c);

      ChessPiece* piece = new ChessPiece(this, side, type, row, col);
      boardMap[row][col] = piece;
    }
  }
}

//проверяем для данной стороны все те поля где в принципе может находится король, тоесть поля, которые не бьются и не заняты своими фигурами
void ChessBoard::fillEndOfGame(PlayerSide side) {
  QVector<Area> endOfGameArea;

  for (int col = 0; col < 8; ++col) {
    for (int row = 0; row < 8; ++row) {
      endOfGame[row][col] = TRUE;
      ChessPiece* piece = boardMap[row][col];

      if (piece != NULL) {
        if (side != piece->getSide())
          endOfGameArea = endOfGameArea + getTurnArea(piece);
      }
    }
  }

  for (int var = 0; var < endOfGameArea.size(); ++var) {
    Area pole = endOfGameArea[var];
    endOfGame[pole.row][pole.col] = FALSE;
  }
}

// Загрузка доски из ресурса
void ChessBoard::loadRes(QString fileName) {
  qDebug() << "Загрузка ресурса " << fileName;
  QResource res(fileName);
  loadFile(res.absoluteFilePath());
}

