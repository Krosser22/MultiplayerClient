/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Window.hpp>
#include "scenes/loginScene.h"
#include "managers/UIManager.h"
#include "managers/gameManager.h"
#include "managers/sceneManager.h"
#include "server.h"

UITextBox txtUser_;
UITextBox txtPass_;

void checkLogin() {
  if (Server::Login(txtUser_.text()->getString().toAnsiString().c_str(), txtPass_.text()->getString().toAnsiString().c_str())) {
    SceneManager::ChangeScene("Game");
  }
}

void forgotPassword() {
  SceneManager::ChangeScene("ForgotPassword");
}

void createAccount() {
  SceneManager::ChangeScene("CreateAccount");
}

void LoginScene::start() {
  //User text
  txtUser_.setText("Admin");
  txtUser_.setHintText("User");
  txtUser_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.3f);
  UIManager::AddUITextBox(&txtUser_);

  //Password text
  txtPass_.setText("Password");
  txtPass_.setHintText("Password");
  txtPass_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.4f);
  txtPass_.setIsPassword(true);
  UIManager::AddUITextBox(&txtPass_);

  //Login button
  btnLogin_.setTexture("btnLogin.png");
  btnLogin_.setFocusTexture("btnFocusLogin.png");
  btnLogin_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.5f);
  btnLogin_.setOnClick(checkLogin);
  UIManager::AddUIButton(&btnLogin_);

  //Forgot the Pass button
  btnForgotPassword_.setTexture("btnForgotPassword.png");
  btnForgotPassword_.setFocusTexture("btnFocusForgotPassword.png");
  btnForgotPassword_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.6f);
  btnForgotPassword_.setOnClick(forgotPassword);
  UIManager::AddUIButton(&btnForgotPassword_);

  //New Account button
  btnNewAccount_.setTexture("btnNewAccount.png");
  btnNewAccount_.setFocusTexture("btnFocusNewAccount.png");
  btnNewAccount_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.7f);
  btnNewAccount_.setOnClick(createAccount);
  UIManager::AddUIButton(&btnNewAccount_);
}

void LoginScene::input() {
  if (GameManager::WindowHasFocus()) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      //Check collision with the mouse and the txt and buttons
    }
  }
}

void LoginScene::update() {
}

void LoginScene::finish() {
  GameManager::RemoveBackground();
}