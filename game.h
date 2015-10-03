#ifndef GAME_H
#define GAME_H

// Цвета фигур
enum PlayerSide {
  BLACK, WHITE
};

// Игровой процесс
class Game {
 public:
  // Игровое поле (доска)
  char map[8][8];
  // Конструктор
  Game();
};

#endif // GAME_H
