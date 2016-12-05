/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/waitingGameScene.h"

static struct WaitingGameSceneData {
} data;

void WaitingGameScene::start() {
  GameManager::SetBackground("background.png"); //Set the background
}

void WaitingGameScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void WaitingGameScene::update() {}

void WaitingGameScene::finish() {}