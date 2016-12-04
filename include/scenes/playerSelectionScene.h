/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __PLAYER_SELECTION_SCENE_H__
#define __PLAYER_SELECTION_SCENE_H__

#include "scenes/scene.h"

class PlayerSelectionScene : public Scene {
public:
  PlayerSelectionScene() {};
  ~PlayerSelectionScene() {};

  void start();

  void input();
  
  void update();

  void finish();
};

#endif //__PLAYER_SELECTION_SCENE_H__