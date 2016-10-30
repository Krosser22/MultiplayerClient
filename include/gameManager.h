/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "object.h"

namespace GameManager {
  //Starts the GameManager
  void start();

  //Finish the GameManager
  void finish();

  //Add an object to the draw list
  void addToDraw(Object *object);

  //Return if the window is open
  bool isOpen();

  //Draw all the elements on the render buffer
  void draw();
};

#endif //__GAME_MANAGER_H__