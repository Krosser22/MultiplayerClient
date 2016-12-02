/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

// To create the button images I used this web page
// -Normal texture-
// https://dabuttonfactory.com/#t=&f=Calibri-Bold&ts=24&tc=fff&tshs=1&tshc=000&w=222&h=50&c=5&bgt=gradient&bgc=3d85c6&ebgc=073763
//
// -Focused texture-
// https://dabuttonfactory.com/#t=&f=Calibri-Bold&ts=24&tc=fff&tshs=1&tshc=000&w=222&h=50&c=5&bgt=gradient&bgc=073763&ebgc=3d85c6&bs=1&bc=000

#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include "UIObject.h"

class UIButton : public UIObject {
public:
  UIButton();
  ~UIButton();

  void setOnClick(void (*f)());

  void onClick();

private:
  void (*functOnClick_)();
};

#endif //__UI_BUTTON_H__