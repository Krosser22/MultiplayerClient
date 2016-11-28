/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "actor.h"
#include "UI/UIButton.h"
#include "UI/UITextBox.h"

namespace UIManager {
  //Sets the window to draw the UI
  void Start(sf::RenderWindow *window);

  //Update function (inside the main loop)
  void Update();

  //Draw function (inside the main loop)
  void Draw();

  //Add a button to the UI
  void AddUIButton(UIButton *button);

  //Add a text to the UI
  void AddUITextBox(UITextBox *textBox);

  //Clear all the elements from the list of elements to update and draw
  void ClearUI();
};

#endif //__UI_MANAGER_H__