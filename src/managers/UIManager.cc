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

static struct UIManagerData {
  sf::RenderWindow *window;
  std::vector<UIObject *> focusOrderList;
  std::vector<UIButton *> buttonList;
  std::vector<UITextBox *> textBoxList;
  std::vector<sf::Text *> textList;
  UIObject *actualFocus;
  bool isATextBoxFocused = false;
} data;

void UIManager::Start(sf::RenderWindow *window) {
  data.window = window;
}

void UIManager::Update() {
  static sf::FloatRect intersection;

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::FloatRect mousePosition(sf::Vector2f(GameManager::MouseX(), GameManager::MouseY()), sf::Vector2f(1, 1));

    //Check collision with the buttons
    bool collision = false;
    for (unsigned int i = 0; i < data.buttonList.size() && !collision; ++i) {
      if (data.buttonList.at(i)->sprite()->getGlobalBounds().intersects(mousePosition, intersection)) {
        collision = true;
        if (data.actualFocus != data.buttonList.at(i)) {
          if (data.actualFocus != nullptr) data.actualFocus->setFocus(false);
          data.actualFocus = data.buttonList.at(i);
          data.actualFocus->setFocus(true);
          data.buttonList.at(i)->onClick();
          data.isATextBoxFocused = false;
        }
      }
    }

    //Check collision with the textBox
    for (unsigned int i = 0; i < data.textBoxList.size() && !collision; ++i) {
      if (data.textBoxList.at(i)->sprite()->getGlobalBounds().intersects(mousePosition, intersection)) {
        collision = true;
        if (data.actualFocus != data.textBoxList.at(i)) {
          if (data.actualFocus != nullptr) data.actualFocus->setFocus(false);
          data.actualFocus = data.textBoxList.at(i);
          data.actualFocus->setFocus(true);
          data.isATextBoxFocused = true;
        }
      }
    }

    if (!collision) data.isATextBoxFocused = false;
  }

  //Write on the textBox focused
  UITextBox *textBox;
  std::string str;
  if (data.isATextBoxFocused) {
    textBox = (UITextBox *)(data.actualFocus);
    str = textBox->text()->getString().toAnsiString();
  }

  //Events
  sf::Event event;
  std::string newChar;
  while (data.window->pollEvent(event)) {
    //Remove focus
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !data.isATextBoxFocused && data.actualFocus != nullptr) {
      data.actualFocus->setFocus(false);
      data.actualFocus = nullptr;
    }

    //Close windows
    if (event.type == sf::Event::Closed) {
      GameManager::CloseWindow();
    }

    //Change focus (TAB key)
    /*if (data.focusOrderList.size() > 0) {
      if (event.text.unicode == sf::Keyboard::Tab && event.type == sf::Event::KeyReleased) {
        if (data.actualFocus == nullptr) {
          data.actualFocus = data.focusOrderList.at(0);
        } else {
          int pos = -1;
          for (unsigned int i = 0; i < data.focusOrderList.size() && pos == -1; ++i) {
            if (data.actualFocus == data.focusOrderList.at(i)) {
              pos = i + 1;
            }
          }

          if (pos == data.focusOrderList.size()) {
            pos = 0;
          }

          data.actualFocus = data.focusOrderList.at(pos);
        }
      }
    }*/

    //Delete key
    if (data.isATextBoxFocused && event.text.unicode == DELETE_KEY) {
      str = str.substr(0, str.size() - 1);
      textBox->setText(str.c_str());
    }

    //TextBox keys
    if (data.isATextBoxFocused && event.type == sf::Event::TextEntered) {
      // Handle a few amount of characters only
      if ((event.text.unicode >= 48 && event.text.unicode <= 57) || //Numbers
        (event.text.unicode >= 65 && event.text.unicode <= 90) ||   //Mayus
        (event.text.unicode >= 97 && event.text.unicode <= 122)) {  //Minus
        newChar += static_cast<char>(event.text.unicode);
        str += newChar;
        textBox->setText(str.c_str());
      }
    }
  }
}

void UIManager::Draw() {
  //Draw the list of buttons
  for (unsigned int i = 0; i < data.buttonList.size(); ++i) data.window->draw(*data.buttonList.at(i)->sprite());

  //Draw the list of textBox
  for (unsigned int i = 0; i < data.textBoxList.size(); ++i) {
    data.window->draw(*data.textBoxList.at(i)->sprite());
    data.window->draw(*data.textBoxList.at(i)->textToDraw());
  }

  //Draw the list of text
  for (unsigned int i = 0; i < data.textList.size(); ++i) data.window->draw(*data.textList.at(i));
}

void UIManager::AddUIButton(UIButton *button) {
  data.buttonList.push_back(button);
  data.focusOrderList.push_back(button);
}

void UIManager::AddUITextBox(UITextBox *textBox) {
  data.textBoxList.push_back(textBox);
  data.focusOrderList.push_back(textBox);
}

void UIManager::AddUIText(sf::Text *text) {
  data.textList.push_back(text);
}

void UIManager::ClearUI() {
  data.buttonList.clear();
  data.textBoxList.clear();
  data.textList.clear();
}