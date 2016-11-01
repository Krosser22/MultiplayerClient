/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "object.h"
#include "gameManager.h"

Object::Object() {}

Object::~Object() {}

void Object::setTexture(const char *imagePath) {
  texture_.loadFromFile(ASSETS::ImagePath(imagePath));
  sprite_.setTexture(texture_);
  sprite_.setOrigin(0.0f, 0.0f);
  sprite_.setRotation(0.0f);
  sprite_.setScale(1.0f, 1.0f);
  sprite_.setPosition(0.0f, 0.0f);
}

void Object::setPosition(float x, float y) {
  float lastX = sprite_.getPosition().x;
  float lastY = sprite_.getPosition().y;
  sprite_.setPosition(x, y);
  if (GameManager::checkCollision(this)) sprite_.setPosition(lastX, lastY);
}

void Object::setPositionX(float x) {
  float lastX = sprite_.getPosition().x;
  sprite_.setPosition(x, sprite_.getPosition().y);
  if (GameManager::checkCollision(this)) sprite_.setPosition(lastX, sprite_.getPosition().y);
}

void Object::setPositionY(float y) {
  float lastY = sprite_.getPosition().y;
  sprite_.setPosition(sprite_.getPosition().x, y);
  if (GameManager::checkCollision(this)) sprite_.setPosition(sprite_.getPosition().x, lastY);
}

void Object::move(float x, float y) {
  float lastX = sprite_.getPosition().x;
  float lastY = sprite_.getPosition().y;
  sprite_.setPosition(sprite_.getPosition().x + x, sprite_.getPosition().y + y);
  if (GameManager::checkCollision(this)) sprite_.setPosition(lastX, lastY);
}

void Object::moveX(float x) {
  float lastX = sprite_.getPosition().x;
  sprite_.setPosition(sprite_.getPosition().x + x, sprite_.getPosition().y);
  if (GameManager::checkCollision(this)) sprite_.setPosition(lastX, sprite_.getPosition().y);
}

void Object::moveY(float y) {
  float lastY = sprite_.getPosition().y;
  sprite_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y + y);
  if (GameManager::checkCollision(this)) sprite_.setPosition(sprite_.getPosition().x, lastY);
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