/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "object.h"

class Button : public Object {
public:
  Button();
  ~Button();
  
  void setText(const char *newText);

  void setPosition(float x, float y);

  sf::Text *getText();

private:
  sf::Text text_;
};

#endif //__BUTTON_H__