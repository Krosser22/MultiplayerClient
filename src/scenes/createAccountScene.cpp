/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/createAccountScene.h"

struct CreateAccountSceneData {
  sf::Text textInfo;
  UITextBox txtEmail;
  UITextBox txtNick;
  UITextBox txtPassword1;
  UITextBox txtPassword2;
} data;

static void createAccount() {
  data.textInfo.setString("");
  std::string strEmail = data.txtEmail.text()->getString().toAnsiString();
  std::string strNick = data.txtNick.text()->getString().toAnsiString();
  std::string strPass1 = data.txtPassword1.text()->getString().toAnsiString();
  std::string strPass2 = data.txtPassword2.text()->getString().toAnsiString();
  int atPos = strEmail.find('@');
  int dotPos = strEmail.find('.');
  if (atPos > 0 && dotPos > 0 && atPos < dotPos && !strNick.empty() && !strPass1.empty() && strPass1 == strPass2) {
    Server::CreateAccount(strEmail.c_str(), strNick.c_str(), strPass1.c_str());
  } else {
    data.textInfo.setString("Something is not correct");
  }
}

static void back() {
  SceneManager::ChangeScene("Login");
}

void CreateAccountScene::start() {
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
  data.txtEmail.setText("condadodaniel@hotmail.com");
  data.txtEmail.setHintText("Email");
  data.txtEmail.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.3f);
  UIManager::AddUITextBox(&data.txtEmail);

  //Nick textBox
  data.txtNick.setText("");
  data.txtNick.setHintText("Nick");
  data.txtNick.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.4f);
  UIManager::AddUITextBox(&data.txtNick);

  //Password1 textBox
  data.txtPassword1.setText("");
  data.txtPassword1.setHintText("Password");
  data.txtPassword1.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.5f);
  data.txtPassword1.setIsPassword(true);
  UIManager::AddUITextBox(&data.txtPassword1);

  //Password2 textBox
  data.txtPassword2.setText("");
  data.txtPassword2.setHintText("Password");
  data.txtPassword2.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.6f);
  data.txtPassword2.setIsPassword(true);
  UIManager::AddUITextBox(&data.txtPassword2);

  //Create account button
  btnCreateAccount_.setTexture("btnCreateAccount.png");
  btnCreateAccount_.setFocusTexture("btnFocusCreateAccount.png");
  btnCreateAccount_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.7f);
  btnCreateAccount_.setOnClick(createAccount);
  UIManager::AddUIButton(&btnCreateAccount_);

  //Back button
  btnBack_.setTexture("btnBack.png");
  btnBack_.setFocusTexture("btnFocusBack.png");
  btnBack_.setPosition(GameManager::WindowWidth() * 0.5f - UIOBJECT_HALF_WIDTH, GameManager::WindowHeight() * 0.8f);
  btnBack_.setOnClick(back);
  UIManager::AddUIButton(&btnBack_);
}

void CreateAccountScene::input() {
  if (GameManager::WindowHasFocus()) {}
}

void CreateAccountScene::update() {}

void CreateAccountScene::finish() {}