/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __FORGOT_PASSWORD_SCENE_H__
#define __FORGOT_PASSWORD_SCENE_H__

#include "scenes/scene.h"

class ForgotPasswordScene : public Scene {
public:
  ForgotPasswordScene() {};
  ~ForgotPasswordScene() {};

  void start();

  void input();
  
  void update();

  void finish();

private:
  UIButton btnSendInfoToEmail_;
  UIButton btnBack_;
};

#endif //__FORGOT_PASSWORD_SCENE_H__