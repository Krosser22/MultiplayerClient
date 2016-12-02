/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "scenes/scene.h"

class IntroScene : public Scene {
public:
  IntroScene() {};
  ~IntroScene() {};

  void start();

  void input();
  
  void update();

  void finish();

private:
  sf::Time startTime_;
  float timeInScene_ = 2.2f;
};

#endif //__INTRO_SCENE_H__