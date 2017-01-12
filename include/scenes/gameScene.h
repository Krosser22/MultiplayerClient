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
  Object ground1_;
  Object ground2_;
  Object leftWall_;
  Object rightWall_;
  Object roof_;
  std::vector<Object *> platforms_;

  bool chatEnable_ = false;
};

#endif //__GAME_SCENE_H__