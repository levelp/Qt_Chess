#ifndef GAME_H
#define GAME_H

#include <QString>

// Цвета фигур: Чёрный / белый
enum PlayerSide { BLACK, WHITE };
QString playerSide2s(PlayerSide type);

// Тип шахматной фигуры: пешка, ладья, конь, слон, ферзь, король
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
// Тип фигуры в строку
QString pieceType2s(PieceType type);
// Символ в тип фигуры
PieceType char2pieceType(QChar c);

// Размер клетки доски в пикселях
const int CELL = 50;

// Игровой процесс
class Game {
 public:
  // Игровое поле (доска)
  char map[8][8];
  // Конструктор
  Game();
};

#endif // GAME_H
