/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/waitingGameScene.h"
#include "UI/UIChat.h"
#include "UI/UIRank.h"
#include "UI/UIGroup.h"

void WaitingGameScene::start() {
  GameManager::SetBackground("waitingForPlayersBackground.png"); //Set the background
}

void WaitingGameScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void WaitingGameScene::update() {
  UIChat::Draw();
  UIRank::Draw();
  UIGroup::Draw();
}

void WaitingGameScene::finish() {}