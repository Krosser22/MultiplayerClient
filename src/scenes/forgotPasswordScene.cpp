/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/forgotPasswordScene.h"

static struct ForGotPasswordSceneData {
  sf::Text textInfo;
  UITextBox txtEmail;
} data;

static void sendInfoToEmail() {
  data.textInfo.setString("");
  std::string strEmail = data.txtEmail.text()->getString().toAnsiString();
  int atPos = strEmail.find('@');
  int dotPos = strEmail.find('.');
  if (atPos > 0 && dotPos > 0 && atPos < dotPos) {
    Server::ForgotPassword(strEmail.c_str());
  } else {
    data.textInfo.setString("The email format is incorrect");
  }
}

static void back() {
  SceneManager::ChangeScene("Login");
}

void ForgotPasswordScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");

  //Info textBox
  data.textInfo.setString("");
  data.textInfo.setFont(*GameManager::Font());
  data.textInfo.setFillColor(sf::Color::Red);
  data.textInfo.setCharacterSize(22);
  data.textInfo.setStyle(sf::Text::Bold);
  data.textInfo.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.25f);
  UIManager::AddUIText(&data.textInfo);

  //Email textBox
  data.txtEmail.setText("");
  data.txtEmail.setHintText("Email");
  data.txtEmail.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.3f);
  UIManager::AddUITextBox(&data.txtEmail);

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

void ForgotPasswordScene::finish() {}