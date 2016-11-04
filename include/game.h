/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __GAME_H__
#define __GAME_H__

#include "actor.h"
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
  Object ground;
  Object platformLeft;
  Object platformRight;
  Object platformCenter;
  Actor actor;
  std::vector<Object> objectList;
};

#endif //__GAME_H__