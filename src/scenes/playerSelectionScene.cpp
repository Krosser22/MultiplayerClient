/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/playerSelectionScene.h"
#include "UI/UIChat.h"

static struct PlayerSelectionSceneData {
} data;

void PlayerSelectionScene::start() {
  GameManager::SetBackground("background.png"); //Set the background
}

void PlayerSelectionScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void PlayerSelectionScene::update() {
  UIChat::Draw();
}

void PlayerSelectionScene::finish() {}