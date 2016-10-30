/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "object.h"

void Object::setTexture(const char *imagePath) {
  texture_.loadFromFile(ASSETS::ImagePath(imagePath));
  sprite_.setTexture(texture_);
  setOrigin(originX_, originY_);
  setPosition(positionX_, positionY_);
}

void Object::setOrigin(float x, float y) {
  originX_ = x;
  originY_ = y;
  sprite_.setOrigin(originX_, originY_);
}

void Object::setPosition(float x, float y) {
  positionX_ = x;
  positionY_ = y;
  sprite_.setPosition(positionX_, positionY_);
}

void Object::setPositionX(float x) {
  positionX_ = x;
  sprite_.setPosition(positionX_, positionY_);
}

void Object::setPositionY(float y) {
  positionY_ = y;
  sprite_.setPosition(positionX_, positionY_);
}

void Object::move(float x, float y) {
  positionX_ += x;
  positionY_ += y;
  sprite_.setPosition(positionX_, positionY_);
}

void Object::moveX(float x) {
  positionX_ += x;
  sprite_.setPosition(positionX_, positionY_);
}

void Object::moveY(float y) {
  positionY_ += y;
  sprite_.setPosition(positionX_, positionY_);
}

void *Object::sprite() {
  return &sprite_;
}

float Object::positionX() {
  return positionX_;
}

float Object::positionY() {
  return positionY_;
}