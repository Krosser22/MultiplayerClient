/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __MAP_SELECTION_SCENE_H__
#define __MAP_SELECTION_SCENE_H__

#include "scenes/scene.h"

class MapSelectionScene : public Scene {
public:
  MapSelectionScene() {};
  ~MapSelectionScene() {};

  void start();

  void input();
  
  void update();

  void finish();
};

#endif //__MAP_SELECTION_SCENE_H__