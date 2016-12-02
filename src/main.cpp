/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "managers/sceneManager.h"
#include "scenes/forgotPasswordScene.h"
#include "scenes/introScene.h"
#include "scenes/loginScene.h"
#include "scenes/gameScene.h"

int main(int argc, char **argv) {
  //Forgot Password Scene
  ForgotPasswordScene forgotPasswordScene;
  forgotPasswordScene.setName("ForgotPassword");
  SceneManager::AddScene(&forgotPasswordScene);

  //Intro Scene
  IntroScene introScene;
  introScene.setName("Intro");
  SceneManager::AddScene(&introScene);

  //Login Scene
  LoginScene loginScene;
  loginScene.setName("Login");
  SceneManager::AddScene(&loginScene);

  //Game Scene
  GameScene gameScene;
  gameScene.setName("Game");
  SceneManager::AddScene(&gameScene);

  //Starts the scene manager
  SceneManager::StartSceneManager("Intro");
  return 0;
}