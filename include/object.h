/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics.hpp>
#include "assets.h"

class Object {
public:
  Object() {};
  ~Object() {};
  
  void setTexture(const char *imagePath = "default.png");

  void setOrigin(float x, float y);

  void setPosition(float x, float y);

  void setPositionX(float x);

  void setPositionY(float y);

  void move(float x, float y);

  void moveX(float x);

  void moveY(float y);

  void *sprite();

  float positionX();

  float positionY();

private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  float originX_;
  float originY_;
  float positionX_;
  float positionY_;
};

#endif //__OBJECT_H__