#include "game.h"

Game::Game() {
  // TODO: перенести в отдельный класс
  for(int i = 0; i < 8; ++i)
    for(int j = 0; j < 8; ++j)
      map[i][j] = '_';
}

