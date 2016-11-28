/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

// To create the textBox images I used this web page
// -Normal texture-
// https://dabuttonfactory.com/#t=&f=Calibri-Bold&ts=24&tc=fff&tshs=1&tshc=000&w=222&h=50&c=5&bgt=gradient&bgc=eee&ebgc=ccc&bs=1&bc=569
//
// -Focused texture-
// https://dabuttonfactory.com/#t=&f=Calibri-Bold&ts=24&tc=fff&tshs=1&tshc=000&w=222&h=50&c=5&bgt=gradient&bgc=ccc&ebgc=eee&bs=1&bc=fff

#ifndef __UI_TEXTBOX_H__
#define __UI_TEXTBOX_H__

#include "UIObject.h"

class UITextBox : public UIObject {
public:
  UITextBox();
  ~UITextBox();

  //If the text is hidden it will show '*' instead of the real characters
  void setIsPassword(bool isPassword = false);

  bool isPassword();

  void setMaxTextLength(int maxTextLength = 22);

  int maxTextLength();
  
  void setText(const char *newText);

  void setHintText(const char *newHintText);

  void setPosition(float x, float y);

  sf::Text *text();

  sf::Text *hintText();

  sf::Text *textToDraw();

private:
  int maxTextLength_ = 22;

  bool isPassword_ = false;

  sf::Text text_;

  sf::Text passwordText_;

  sf::Text hintText_;
};

#endif //__UI_TEXTBOX_H__