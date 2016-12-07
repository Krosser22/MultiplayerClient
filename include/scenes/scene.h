/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_H__
#define __SCENE_H__

#include <imgui-sfml.h>
#include <deque>
#include <SFML/Window.hpp>
#include "managers/gameManager.h"
#include "managers/sceneManager.h"
#include "server.h"

static struct GameData {
  Actor player;
  std::deque<Actor> enemies;
  bool completed = false;
} gameData;

class Scene {
public:
  Scene() {};
  ~Scene() {};

  virtual void start() = 0;

  virtual void input() = 0;
  
  virtual void update() = 0;

  virtual void finish() = 0;

  void setName(std::string newName);

  std::string name();

protected:
  std::string name_;
};

#endif //__SCENE_H__