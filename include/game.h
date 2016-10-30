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
#include <vector>

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
  Object ground;
  Player player;
  float playerSpeed = 2.22f;
  std::vector<Object> objectList;
};

#endif //__GAME_H__