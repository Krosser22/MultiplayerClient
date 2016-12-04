/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __CREATE_ACCOUNT_SCENE_H__
#define __CREATE_ACCOUNT_SCENE_H__

#include "scenes/scene.h"

class CreateAccountScene : public Scene {
public:
  CreateAccountScene() {};
  ~CreateAccountScene() {};

  void start();

  void input();
  
  void update();

  void finish();

private:
  UIButton btnCreateAccount_;
  UIButton btnBack_;
};

#endif //__CREATE_ACCOUNT_SCENE_H__