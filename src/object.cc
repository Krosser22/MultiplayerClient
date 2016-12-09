/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "object.h"

Object::Object() {}

Object::~Object() {}

void Object::setID(std::string *newID) {
  ID_ = *newID;
}

std::string Object::ID() {
  return ID_;
}

void Object::setTexture(const char *imagePath) {
  texture_.loadFromFile(ASSETS::ImagePath(imagePath));
  sprite_.setTexture(texture_);
  sprite_.setOrigin(0.0f, 0.0f);
  sprite_.setRotation(0.0f);
  sprite_.setScale(1.0f, 1.0f);
  sprite_.setPosition(0.0f, 0.0f);
}

void Object::setPosition(float x, float y) {
  sprite_.setPosition(x, y);
}

sf::Sprite *Object::sprite() {
  return &sprite_;
}

float Object::positionX() {
  return sprite_.getPosition().x;
}

float Object::positionY() {
  return sprite_.getPosition().y;
}

float Object::width() {
  return texture_.getSize().x * sprite_.getScale().x;
}

float Object::height() {
  return texture_.getSize().y * sprite_.getScale().y;
}