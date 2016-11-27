/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Window.hpp>
#include "scenes/introScene.h"
#include "managers/gameManager.h"
#include "managers/sceneManager.h"

void IntroScene::start() {
  //Set the background
  GameManager::setBackground("credits.png");

  //Set the start time of the scene
  startTime_ = GameManager::getTime();
}

void IntroScene::input() {
  if (GameManager::windowHasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      SceneManager::ChangeScene("Game");
    }
  }
}

void IntroScene::update() {
  if (startTime_.asSeconds() + timeInScene_ < GameManager::getTime().asSeconds()) {
    SceneManager::ChangeScene("Game");
  }
}

void IntroScene::finish() {
  GameManager::removeBackground();
}