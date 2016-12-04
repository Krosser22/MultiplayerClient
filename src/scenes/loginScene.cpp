/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/loginScene.h"

static struct LoginSceneData {
  sf::Text textInfo;
  UITextBox txtNick;
  UITextBox txtPass;
} data;

static void checkLogin() {
  data.textInfo.setString("");
  if (Server::Login(data.txtNick.text()->getString().toAnsiString().c_str(), data.txtPass.text()->getString().toAnsiString().c_str())) {
    SceneManager::ChangeScene("Game");
  } else {
    data.textInfo.setString("Incorrect Nick or Password");
  }
}

static void forgotPassword() {
  SceneManager::ChangeScene("ForgotPassword");
}

static void createAccount() {
  SceneManager::ChangeScene("CreateAccount");
}

void LoginScene::start() {
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

  //Nick textBox
  data.txtNick.setText("Admin");
  data.txtNick.setHintText("Nick");
  data.txtNick.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.3f);
  UIManager::AddUITextBox(&data.txtNick);

  //Password textBox
  data.txtPass.setText("Password");
  data.txtPass.setHintText("Password");
  data.txtPass.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.4f);
  data.txtPass.setIsPassword(true);
  UIManager::AddUITextBox(&data.txtPass);

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

void LoginScene::finish() {}