/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "scenes/scene.h"

class GameScene : public Scene {
public:
  GameScene() {};
  ~GameScene() {};

  void start();

  void input();
  
  void update();

  void finish();

private:
  Object ground_;
  Object platformLeft_;
  Object platformRight_;
  Object platformCenter_;
};

#endif //__GAME_SCENE_H__