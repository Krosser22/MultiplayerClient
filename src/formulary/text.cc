/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "formulary/text.h"
#include "managers/gameManager.h"

Text::Text() {
  text_.setString("Button");
  text_.setFont(*GameManager::getFont());
  text_.setFillColor(sf::Color::Black);
  text_.setCharacterSize(22);
  text_.setStyle(sf::Text::Bold);

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

Text::~Text() {}

void Text::setText(const char *newText) {
  text_.setString(newText);
}

void Text::setHintText(const char *newHintText) {

}

void Text::setPosition(float x, float y) {
  Object::setPosition(x, y);
  text_.setPosition(x + 10.0f, y + 5.0f);
}

sf::Text *Text::getText() {
  return &text_;
}

sf::Text *Text::getHintText() {
  return &hintText_;
}