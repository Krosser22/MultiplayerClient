/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

// To create the button images I used this web page
// https://dabuttonfactory.com/

#ifndef __UI_OBJECT_H__
#define __UI_OBJECT_H__

#include "object.h"

//I know... but time is time and this is not a 'graphics module'
#define UIOBJECT_WIDTH 222
#define UIOBJECT_HALF_WIDTH UIOBJECT_WIDTH / 2

class UIObject : public Object {
public:
  UIObject();
  ~UIObject();

  void setFocus(bool focus);

  //The texture of the UIObject when it has the focus
  void setFocusTexture(const char *imagePath = "default.png");

private:
  sf::Texture focusTexture_;
};

#endif //__UI_OBJECT_H__