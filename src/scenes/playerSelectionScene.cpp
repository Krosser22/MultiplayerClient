/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/playerSelectionScene.h"

static struct PlayerSelectionSceneData {
} data;

void PlayerSelectionScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");
}

void PlayerSelectionScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void PlayerSelectionScene::update() {}

void PlayerSelectionScene::finish() {}