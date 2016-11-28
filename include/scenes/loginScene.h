/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "scenes/scene.h"
#include "formulary/button.h"
#include "formulary/text.h"

class LoginScene : public Scene {
public:
  LoginScene() {};
  ~LoginScene() {};

  void start();

  void input();
  
  void update();

  void finish();

private:
  Text txtUser_;
  Text txtPass_;
  Button btnLogin_;
  Button btnForgotPass_;
  Button btnNewAccount_;
};

#endif //__LOGIN_SCENE_H__