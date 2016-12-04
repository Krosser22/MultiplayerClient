/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __GAME_MENU_SCENE_H__
#define __GAME_MENU_SCENE_H__

#include "scenes/scene.h"

class GameMenuScene : public Scene {
public:
  GameMenuScene() {};
  ~GameMenuScene() {};

  void start();

  void input();
  
  void update();

  void finish();

private:
  UIButton btnCreateGame_;
  UIButton btnJoinGame_;
};

#endif //__GAME_MENU_SCENE_H__