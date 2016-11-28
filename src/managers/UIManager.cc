/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "managers/UIManager.h"
#include "managers/gameManager.h"

#define DELETE_KEY 8

struct UIManagerData {
  sf::RenderWindow *window;
  std::vector<UIButton *> buttonList;
  std::vector<UITextBox *> textList;
  UIObject *actualFocus;
  bool isATextBoxFocused = false;
} UIData;

void UIManager::Start(sf::RenderWindow *window) {
  UIData.window = window;
}

void UIManager::Update() {
  static sf::FloatRect intersection;

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::FloatRect mousePosition(sf::Vector2f(GameManager::MouseX(), GameManager::MouseY()), sf::Vector2f(1, 1));

    //Check collision with the buttons
    bool collision = false;
    for (unsigned int i = 0; i < UIData.buttonList.size() && !collision; ++i) {
      if (UIData.buttonList.at(i)->sprite()->getGlobalBounds().intersects(mousePosition, intersection)) {
        collision = true;
        if (UIData.actualFocus != UIData.buttonList.at(i)) {
          if (UIData.actualFocus != nullptr) UIData.actualFocus->setFocus(false);
          UIData.actualFocus = UIData.buttonList.at(i);
          UIData.actualFocus->setFocus(true);
          UIData.buttonList.at(i)->onClick();
          UIData.isATextBoxFocused = false;
        }
      }
    }

    //Check collision with the textBox
    for (unsigned int i = 0; i < UIData.textList.size() && !collision; ++i) {
      if (UIData.textList.at(i)->sprite()->getGlobalBounds().intersects(mousePosition, intersection)) {
        collision = true;
        if (UIData.actualFocus != UIData.textList.at(i)) {
          if (UIData.actualFocus != nullptr) UIData.actualFocus->setFocus(false);
          UIData.actualFocus = UIData.textList.at(i);
          UIData.actualFocus->setFocus(true);
          UIData.isATextBoxFocused = true;
        }
      }
    }

    if (!collision) UIData.isATextBoxFocused = false;
  }

  //Write on the textBox focused
  sf::Event event;
  UITextBox *textBox;
  std::string newChar;
  std::string str;
  if (UIData.isATextBoxFocused) {
    textBox = (UITextBox *)(UIData.actualFocus);
    str = textBox->text()->getString().toAnsiString();
  }
  while (UIData.window->pollEvent(event)) {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !UIData.isATextBoxFocused && UIData.actualFocus != nullptr) {
      UIData.actualFocus->setFocus(false);
      UIData.actualFocus = nullptr;
    }
    if (event.type == sf::Event::Closed) GameManager::CloseWindow();
    if (UIData.isATextBoxFocused && event.type == sf::Event::TextEntered) {
      // Handle ASCII characters only
      if ((event.text.unicode >= 48 && event.text.unicode <= 57) || //Numbers
        (event.text.unicode >= 65 && event.text.unicode <= 90) ||   //Mayus
        (event.text.unicode >= 97 && event.text.unicode <= 122) ||  //Minus
        (event.text.unicode == DELETE_KEY)) {                       //Delete key
        newChar += static_cast<char>(event.text.unicode);
        if (event.text.unicode == DELETE_KEY) {
          str = str.substr(0, str.size() - 1);
        } else {
          str += newChar;
        }
        textBox->setText(str.c_str());
      }
    }
  }
}

void UIManager::Draw() {
  //Draw the list of buttons
  for (unsigned int i = 0; i < UIData.buttonList.size(); ++i) UIData.window->draw(*UIData.buttonList.at(i)->sprite());

  //Draw the list of text
  for (unsigned int i = 0; i < UIData.textList.size(); ++i) {
    UIData.window->draw(*UIData.textList.at(i)->sprite());
    UIData.window->draw(*UIData.textList.at(i)->textToDraw());
  }
}

void UIManager::AddUIButton(UIButton *button) {
  UIData.buttonList.push_back(button);
}

void UIManager::AddUITextBox(UITextBox *textBox) {
  UIData.textList.push_back(textBox);
}

void UIManager::ClearUI() {
  UIData.buttonList.clear();
  UIData.textList.clear();
}