/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "UI/UITextBox.h"
#include "managers/gameManager.h"

UITextBox::UITextBox() {
  setTexture("textBox.png");
  setFocusTexture("textBoxFocused.png");

  //Text
  text_.setString("");
  text_.setFont(*GameManager::Font());
  text_.setFillColor(sf::Color::Black);
  text_.setCharacterSize(24);
  text_.setStyle(sf::Text::Bold);

  //Password text
  passwordText_.setString("");
  passwordText_.setFont(*GameManager::Font());
  passwordText_.setFillColor(sf::Color::Black);
  passwordText_.setCharacterSize(24);
  passwordText_.setStyle(sf::Text::Bold);

  //Hint text
  hintText_.setString("");
  hintText_.setFont(*GameManager::Font());
  hintText_.setFillColor(sf::Color(125, 125, 125));
  hintText_.setCharacterSize(24);
  hintText_.setStyle(sf::Text::Bold);

  /*text.setCharacterSize(24);
  text.setColor(sf::Color::Red);
  text.setFillColor(sf::Color::Black);
  text.setFont(getFont());
  text.setOrigin(100.0f, 100.0f);
  text.setOutlineColor(sf::Color::White);
  text.setPosition(100.0f, 100.0f);
  text.setRotation(0.0f);
  text.setScale(1.0f, 1.0f);
  text.setString("Hello world");
  text.setStyle(sf::Text::Regular);*/
}

UITextBox::~UITextBox() {}

void UITextBox::setIsPassword(bool isPassword) {
  isPassword_ = isPassword;
}

bool UITextBox::isPassword() {
  return isPassword_;
}

void UITextBox::setMaxTextLength(int maxTextLength) {
  maxTextLength_ = maxTextLength;
}

int UITextBox::maxTextLength() {
  return maxTextLength_;
}

void UITextBox::setText(const char *newText) {
  text_.setString(newText);

  passwordText_.setString("");
  for (unsigned int i = 0; i < text_.getString().getSize(); ++i) {
    passwordText_.setString(passwordText_.getString() + "*");
  }
}

void UITextBox::setHintText(const char *newHintText) {
  hintText_.setString(newHintText);
}

void UITextBox::setPosition(float x, float y) {
  Object::setPosition(x, y);
  text_.setPosition(x + 10.0f, y + 10.0f);
  passwordText_.setPosition(x + 10.0f, y + 10.0f);
  hintText_.setPosition(x + 10.0f, y + 10.0f);
}

sf::Text *UITextBox::text() {
  return &text_;
}

sf::Text *UITextBox::hintText() {
  return &hintText_;
}

sf::Text *UITextBox::textToDraw() {
  if (text_.getString() == "") {
    return &hintText_;
  } else if (isPassword_) {
    return &passwordText_;
  } else {
    return &text_;
  }
}