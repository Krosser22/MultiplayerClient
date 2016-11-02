/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "object.h"

class Player : public Object {
public:
  Player() {};
  ~Player() {};

  void update();
};

#endif //__PLAYER_H__