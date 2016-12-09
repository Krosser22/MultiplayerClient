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
  Object();
  ~Object();

  void setID(std::string *newID);

  std::string ID();
  
  void setTexture(const char *imagePath = "default.png");

  void setPosition(float x, float y);

  sf::Sprite *sprite();

  float positionX();

  float positionY();

  float width();

  float height();

protected:
  //The ID of the actor
  std::string ID_;

  sf::Texture texture_;

  sf::Sprite sprite_;
};

#endif //__OBJECT_H__