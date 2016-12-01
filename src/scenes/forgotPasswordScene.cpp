/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Window.hpp>
#include "scenes/forgotPasswordScene.h"
#include "managers/gameManager.h"
#include "managers/sceneManager.h"
#include "server.h"

struct ForgotPasswordSceneData {
  sf::Text textInfo;
  UITextBox txtEmail;
} forgotPasswordSceneData;

void sendInfoToEmail() {
  /*if (Server::Login(forgotPasswordSceneData.txtNick.text()->getString().toAnsiString().c_str(), forgotPasswordSceneData.txtPass.text()->getString().toAnsiString().c_str())) {
    SceneManager::ChangeScene("Game");
  } else {
    forgotPasswordSceneData.textInfo.setString("Incorrect Nick or Password");
  }*/
}

void back() {
  SceneManager::ChangeScene("Login");
}

void ForgotPasswordScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");

  //Info text
  forgotPasswordSceneData.textInfo.setString("");
  forgotPasswordSceneData.textInfo.setFont(*GameManager::Font());
  forgotPasswordSceneData.textInfo.setFillColor(sf::Color::Red);
  forgotPasswordSceneData.textInfo.setCharacterSize(22);
  forgotPasswordSceneData.textInfo.setStyle(sf::Text::Bold);
  forgotPasswordSceneData.textInfo.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.25f);
  UIManager::AddUIText(&forgotPasswordSceneData.textInfo);

  //Email text
  forgotPasswordSceneData.txtEmail.setText("");
  forgotPasswordSceneData.txtEmail.setHintText("Email");
  forgotPasswordSceneData.txtEmail.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.3f);
  UIManager::AddUITextBox(&forgotPasswordSceneData.txtEmail);

  //Send info to email button
  btnSendInfoToEmail_.setTexture("btnSendToEmail.png");
  btnSendInfoToEmail_.setFocusTexture("btnFocusSendToEmail.png");
  btnSendInfoToEmail_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.4f);
  btnSendInfoToEmail_.setOnClick(sendInfoToEmail);
  UIManager::AddUIButton(&btnSendInfoToEmail_);

  //Back button
  btnBack_.setTexture("btnBack.png");
  btnBack_.setFocusTexture("btnFocusBack.png");
  btnBack_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.5f);
  btnBack_.setOnClick(back);
  UIManager::AddUIButton(&btnBack_);
}

void ForgotPasswordScene::input() {
  if (GameManager::WindowHasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      SceneManager::ChangeScene("Login");
    }
  }
}

void ForgotPasswordScene::update() {}

void ForgotPasswordScene::finish() {
  GameManager::RemoveBackground();
}