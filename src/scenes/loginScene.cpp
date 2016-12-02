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
#include "server.h"

struct LoginSceneData {
  sf::Text textInfo;
  UITextBox txtNick;
  UITextBox txtPass;
} loginSceneData;

void checkLogin() {
  loginSceneData.textInfo.setString("");
  if (Server::Login(loginSceneData.txtNick.text()->getString().toAnsiString().c_str(), loginSceneData.txtPass.text()->getString().toAnsiString().c_str())) {
    SceneManager::ChangeScene("Game");
  } else {
    loginSceneData.textInfo.setString("Incorrect Nick or Password");
  }
}

void forgotPassword() {
  SceneManager::ChangeScene("ForgotPassword");
}

void createAccount() {
  SceneManager::ChangeScene("CreateAccount");
}

void LoginScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");

  //Info text
  loginSceneData.textInfo.setString("");
  loginSceneData.textInfo.setFont(*GameManager::Font());
  loginSceneData.textInfo.setFillColor(sf::Color::Red);
  loginSceneData.textInfo.setCharacterSize(22);
  loginSceneData.textInfo.setStyle(sf::Text::Bold);
  loginSceneData.textInfo.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.25f);
  UIManager::AddUIText(&loginSceneData.textInfo);

  //Nick text
  loginSceneData.txtNick.setText("Admin");
  loginSceneData.txtNick.setHintText("Nick");
  loginSceneData.txtNick.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.3f);
  UIManager::AddUITextBox(&loginSceneData.txtNick);

  //Password text
  loginSceneData.txtPass.setText("Password");
  loginSceneData.txtPass.setHintText("Password");
  loginSceneData.txtPass.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.4f);
  loginSceneData.txtPass.setIsPassword(true);
  UIManager::AddUITextBox(&loginSceneData.txtPass);

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

void LoginScene::update() {}

void LoginScene::finish() {
  GameManager::RemoveBackground();
}