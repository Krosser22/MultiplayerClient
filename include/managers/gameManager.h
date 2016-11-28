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
#include "formulary/button.h"
#include "formulary/text.h"

namespace GameManager {
  //Starts the GameManager
  void start();

  //Finish the GameManager
  void finish();

  //Set the background of the game
  void setBackground(const char *imagePath);

  //Remove the actual background of the game
  void removeBackground();

  //Add an object to the draw list
  void addObject(Object *object);

  //Add an actor to the draw list
  void addActor(Actor *actor);

  //Add a button to the draw list
  void addButton(Button *button);

  //Add a text to the draw list
  void addText(Text *text);

  //Remove an object from the draw list and from the collision list
  void removeObject(Object *object);

  //Clear the list of objects to draw
  void clearDrawList();

  //Return if the window is open
  bool isOpen();

  //Close the actual window
  void closeWindow();

  //Return if the windows has the focus
  bool windowHasFocus();

  //Draw all the elements on the render buffer
  void draw();

  //Return the position X of the mouse
  float mouseX();

  //Return the position Y of the mouse
  float mouseY();

  //Return the width of the window
  float getWindowWidth();

  //Return the height of the window
  float getWindowHeight();

  //Return if an objects make collision with all the other objects
  bool checkCollision(Actor *actor);

  //Return the time since the application starts
  sf::Time getTime();

  //Return the font of the project
  sf::Font *getFont();
};

#endif //__GAME_MANAGER_H__