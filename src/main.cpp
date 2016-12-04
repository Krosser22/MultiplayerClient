/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "managers/sceneManager.h"
#include "scenes/createAccountScene.h"
#include "scenes/forgotPasswordScene.h"
#include "scenes/gameMenuScene.h"
#include "scenes/gameScene.h"
#include "scenes/introScene.h"
#include "scenes/loginScene.h"
#include "scenes/mapSelectionScene.h"
#include "scenes/playerSelectionScene.h"
#include "scenes/waitingGameScene.h"

int main(int argc, char **argv) {
  //Create Account Scene
  CreateAccountScene createAccountScene;
  createAccountScene.setName("CreateAccount");
  SceneManager::AddScene(&createAccountScene);

  //Forgot Password Scene
  ForgotPasswordScene forgotPasswordScene;
  forgotPasswordScene.setName("ForgotPassword");
  SceneManager::AddScene(&forgotPasswordScene);

  //Game Menu Scene
  GameMenuScene gameMenuScene;
  gameMenuScene.setName("GameMenu");
  SceneManager::AddScene(&gameMenuScene);

  //Game Scene
  GameScene gameScene;
  gameScene.setName("Game");
  SceneManager::AddScene(&gameScene);

  //Intro Scene
  IntroScene introScene;
  introScene.setName("Intro");
  SceneManager::AddScene(&introScene);

  //Login Scene
  LoginScene loginScene;
  loginScene.setName("Login");
  SceneManager::AddScene(&loginScene);

  //MapSelection Scene
  MapSelectionScene mapSelectionScene;
  mapSelectionScene.setName("MapSelection");
  SceneManager::AddScene(&mapSelectionScene);

  //PlayerSelection Scene
  PlayerSelectionScene playerSelection;
  playerSelection.setName("PlayerSelection");
  SceneManager::AddScene(&playerSelection);

  //Waiting Game Scene
  WaitingGameScene waitingGameScene;
  waitingGameScene.setName("WaitingGame");
  SceneManager::AddScene(&waitingGameScene);

  //Starts the scene manager
  SceneManager::StartSceneManager("Intro");
  return 0;
}