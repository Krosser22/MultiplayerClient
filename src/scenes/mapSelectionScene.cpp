/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/mapSelectionScene.h"

struct MapSelectionSceneData {
} data;

void MapSelectionScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");
}

void MapSelectionScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void MapSelectionScene::update() {}

void MapSelectionScene::finish() {}