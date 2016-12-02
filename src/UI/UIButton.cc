/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "UI/UIButton.h"
#include "managers/gameManager.h"

void defaultOnClick() {
  printf("Click\n");
}

UIButton::UIButton() {
  functOnClick_ = defaultOnClick;
}

UIButton::~UIButton() {}

void UIButton::setOnClick(void(*f)()) {
  functOnClick_ = f;
}

void UIButton::onClick() {
  functOnClick_();
}