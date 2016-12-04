/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/gameMenuScene.h"

static struct GameMenuSceneData {
} data;

void GameMenuScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");
}

void GameMenuScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void GameMenuScene::update() {}

void GameMenuScene::finish() {}