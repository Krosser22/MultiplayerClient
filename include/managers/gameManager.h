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
  void Start(sf::RenderWindow *window);

  //Finish the GameManager
  void Finish();

  //Set the background of the game
  void SetBackground(const char *imagePath);

  //Remove the actual background of the game
  void RemoveBackground();

  //Add an object to the draw list
  void AddObject(Object *object);

  //Add an actor to the draw list
  void AddActor(Actor *actor);

  //Add an enemy that will be controlled by other computer
  void AddEnemy(Actor *actor);

  //Add a bullet to the draw list
  void AddBullet(Bullet *bullet);

  //Remove an enemy
  void RemoveEnemy(Actor *actor);

  //Remove a bullet
  void RemoveBullet(std::string ownerID, std::string ID);

  //Clear the list of objects to draw
  void ClearDrawList();

  //Return if the window is open
  bool IsOpen();

  //Close the actual window
  void CloseWindow();

  //Return if the windows has the focus
  bool WindowHasFocus();

  //Draw all the elements on the render buffer
  void Draw();

  //Return the position X of the mouse
  float MouseX();

  //Return the position Y of the mouse
  float MouseY();

  //Return the width of the window
  const int WindowWidth();

  //Return the height of the window
  const int WindowHeight();

  //Return if an objects make collision with all the other objects
  bool CheckCollision(Actor *actor);

  //Return the time since the application starts
  sf::Time Time();

  //Return the font of the project
  sf::Font *Font();
};

#endif //__GAME_MANAGER_H__