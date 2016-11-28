/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __TEXT_H__
#define __TEXT_H__

#include "object.h"

class Text : public Object {
public:
  Text();
  ~Text();
  
  void setText(const char *newText);

  void setHintText(const char *newHintText);

  void setPosition(float x, float y);

  sf::Text *getText();

  sf::Text *getHintText();

private:
  sf::Text text_;

  sf::Text hintText_;
};

#endif //__TEXT_H__