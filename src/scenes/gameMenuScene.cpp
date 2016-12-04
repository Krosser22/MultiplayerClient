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

static void createGame() {
  printf("createGame is an empty function\n");
}

static void joinGame() {
  printf("joinGame is an empty function\n");
}

void GameMenuScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");

  //Create Game button
  btnCreateGame_.setTexture("btnCreateGame.png");
  btnCreateGame_.setFocusTexture("btnFocusCreateGame.png");
  btnCreateGame_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.4f);
  btnCreateGame_.setOnClick(createGame);
  UIManager::AddUIButton(&btnCreateGame_);

  //Join Game button
  btnJoinGame_.setTexture("btnJoinGame.png");
  btnJoinGame_.setFocusTexture("btnFocusJoinGame.png");
  btnJoinGame_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.5f);
  btnJoinGame_.setOnClick(joinGame);
  UIManager::AddUIButton(&btnJoinGame_);
}

void GameMenuScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void GameMenuScene::update() {}

void GameMenuScene::finish() {}