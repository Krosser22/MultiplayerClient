/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Window.hpp>
#include <imgui.h>
#include "scenes/loginScene.h"
#include "managers/gameManager.h"
#include "managers/sceneManager.h"

void LoginScene::start() {
  txtPass_.setString("hello");
  txtPass_.setFont(GameManager::getFont());
  txtPass_.setCharacterSize(30);
  txtPass_.setStyle(sf::Text::Bold);
  txtPass_.setOutlineColor(sf::Color::Red);
  //GameManager::addObject(&txtPass_);
}

void LoginScene::input() {
  if (GameManager::windowHasFocus()) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      //Check collision with the mouse and the txt and buttons
      ImguiTestWindowOpened_ = !ImguiTestWindowOpened_;
    }
  }
}

void LoginScene::update() {
  ImGui::ShowTestWindow(&ImguiTestWindowOpened_);
}

void LoginScene::finish() {
  GameManager::removeBackground();
}