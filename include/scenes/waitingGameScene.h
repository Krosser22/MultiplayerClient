/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __WAITING_GAME_SCENE_H__
#define __WAITING_GAME_SCENE_H__

#include "scenes/scene.h"

class WaitingGameScene : public Scene {
public:
  WaitingGameScene() {};
  ~WaitingGameScene() {};

  void start();

  void input();
  
  void update();

  void finish();
};

#endif //__WAITING_GAME_SCENE_H__