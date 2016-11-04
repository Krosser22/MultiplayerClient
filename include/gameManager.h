/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "actor.h"

namespace GameManager {
  //Starts the GameManager
  void start();

  //Finish the GameManager
  void finish();

  //Set the background of the game
  void setBackground(const char *imagePath);

  //Add an object to the draw list
  void addObject(Object *object);

  //Add an actor to the draw list
  void addActor(Actor *actor);

  //Remove an object from the draw list and from the collision list
  void removeObject(Object *object);

  //Return if the window is open
  bool isOpen();

  //Draw all the elements on the render buffer
  void draw();

  //Return the position X of the mouse
  float mouseX();

  //Return the position Y of the mouse
  float mouseY();

  //Return if an objects make collision with all the other objects
  bool checkCollision(Actor *actor);

  sf::Time getTime();
};

#endif //__GAME_MANAGER_H__