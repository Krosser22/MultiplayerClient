/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __GAME_H__
#define __GAME_H__

#include "player.h"

class Game {
public:
  Game() {};
  ~Game() {};

  void start();

  void input();
  
  void update();

  void finish();

private:
  Object map;
  Object box;
  Player player;
  float playerSpeed = 1.8f;
};

#endif //__GAME_H__