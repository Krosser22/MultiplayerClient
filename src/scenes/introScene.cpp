/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/introScene.h"

void IntroScene::start() {
  //Set the background
  GameManager::SetBackground("credits.png");

  //Set the start time of the scene
  startTime_ = GameManager::Time();
}

void IntroScene::input() {
  if (GameManager::WindowHasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      SceneManager::ChangeScene("Login");
    }
  }
}

void IntroScene::update() {
  if (startTime_.asSeconds() + timeInScene_ < GameManager::Time().asSeconds()) {
    SceneManager::ChangeScene("Login");
  }
}

void IntroScene::finish() {}