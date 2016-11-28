/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "UI/UIObject.h"
#include "managers/gameManager.h"

UIObject::UIObject() {}

UIObject::~UIObject() {}

void UIObject::setFocus(bool focus) {
  if (focus) {
    sprite_.setTexture(focusTexture_);
  } else {
    sprite_.setTexture(texture_);
  }
}

void UIObject::setFocusTexture(const char *imagePath) {
  focusTexture_.loadFromFile(ASSETS::ImagePath(imagePath));
}