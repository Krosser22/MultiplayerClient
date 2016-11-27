/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "managers/sceneManager.h"
#include "scenes/introScene.h"
#include "scenes/gameScene.h"

int main(int argc, char **argv) {
  //Intro Scene
  IntroScene introScene;
  introScene.setName("Intro");
  SceneManager::AddScene(&introScene);

  //Game Scene
  GameScene gameScene;
  gameScene.setName("Game");
  SceneManager::AddScene(&gameScene);

  SceneManager::StartSceneManager("Intro");
  return 0;
}