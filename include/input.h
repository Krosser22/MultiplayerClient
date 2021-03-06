/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __INPUT_H__
#define __INPUT_H__

#define INPUT_KEY_ENTER 155

namespace MYINPUT {
  //Update the input variables (this is being executed by the engine)
  void Update();

  //The key is down
  bool IsKeyDown(unsigned char key);

  //The key has been pressed this frame
  bool IsKeyPressed(unsigned char key);

  //The key has been released this frame
  bool IsKeyReleased(unsigned char key);

  //The button is down (0=Left, 1=Right, 2=Midle)
  bool IsMouseDown(unsigned char button);

  //The button has been pressed this frame (0=Left, 1=Right, 2=Midle)
  bool IsMousePressed(unsigned char button);

  //The button has been released this frame (0=Left, 1=Right, 2=Midle)
  bool IsMouseReleased(unsigned char button);

  //The rolling of the mouse wheel
  float MouseWheel();

  //The position X of the mouse
  float MousePositionX();

  //The position Y of the mouse
  float MousePositionY();
} //TODO - Diferenciate between mayus and minus

#endif //__INPUT_H__