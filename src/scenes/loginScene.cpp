/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Window.hpp>
#include "scenes/loginScene.h"
#include "managers/gameManager.h"
#include "managers/sceneManager.h"

void LoginScene::start() {
  //User text
  txtUser_.setTexture("textFormulary.png");
  txtUser_.setText("");
  txtUser_.setHintText("User");
  txtUser_.setPosition(GameManager::getWindowWidth() * 0.5f, GameManager::getWindowHeight() * 0.3f);
  GameManager::addText(&txtUser_);

  //Password text
  txtPass_.setTexture("textFormulary.png");
  txtPass_.setText("");
  txtPass_.setHintText("Password");
  txtPass_.setPosition(GameManager::getWindowWidth() * 0.5f, GameManager::getWindowHeight() * 0.4f);
  GameManager::addText(&txtPass_);

  //Login button
  btnLogin_.setTexture("btnLogin.png");
  btnLogin_.setText("Login");
  btnLogin_.setPosition(GameManager::getWindowWidth() * 0.5f, GameManager::getWindowHeight() * 0.5f);
  GameManager::addButton(&btnLogin_);

  //Forgot the Pass button
  btnForgotPass_.setTexture("btnForgotPass.png");
  btnForgotPass_.setText("Forgot password ?");
  btnForgotPass_.setPosition(GameManager::getWindowWidth() * 0.5f, GameManager::getWindowHeight() * 0.6f);
  GameManager::addButton(&btnForgotPass_);

  //New Account button
  btnNewAccount_.setTexture("btnNewAccount.png");
  btnNewAccount_.setText("Create New Account");
  btnNewAccount_.setPosition(GameManager::getWindowWidth() * 0.5f, GameManager::getWindowHeight() * 0.7f);
  GameManager::addButton(&btnNewAccount_);
}

void LoginScene::input() {
  if (GameManager::windowHasFocus()) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      //Check collision with the mouse and the txt and buttons
    }
  }
}

void LoginScene::update() {
}

void LoginScene::finish() {
  GameManager::removeBackground();
}