/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/System/Time.hpp>
#include "actor.h"
#include "gameManager.h"

struct ActorMovement {
  bool left;
  bool right;
  bool up;
  bool down;
} actorMovement;

Actor::Actor() {

}

Actor::~Actor() {

}

void Actor::moveLeft() {
  actorMovement.left = true;
}

void Actor::moveRight() {
  actorMovement.right = true;
}

void Actor::jump() {
  if (bisGrounded_) {
    //printf("Starts Jumping\n");
    actorMovement.up = true;
    actorStartJumpTime_ = GameManager::getTime();
    actorMaxJumpTime_ = actorStartJumpTime_ + sf::milliseconds(timeToBeJumping_);
  } else if (actorMaxJumpTime_ > GameManager::getTime() && bcanJump_) {
    //printf("Continue Jumping\n");
    actorMovement.up = true;
  }
}

void Actor::crouch() {
  actorMovement.down = true;
}

void Actor::updateCollisions() {
  //Backup of the last valid position
  float lastX = sprite_.getPosition().x;
  float lastY = sprite_.getPosition().y;

  //Variable to store the new Y position
  float newY = sprite_.getPosition().y; //Actual Y position
  //Jumping
  float jumpTimePercent = ((float)(GameManager::getTime().asMilliseconds() - actorStartJumpTime_.asMilliseconds())) / timeToBeJumping_;
  newY += -jumpVelocity_ * (1.0f - jumpTimePercent) * actorMovement.up; //If jumping
  //Falling
  if (!bisFalling_ && jumpTimePercent > 1.0f) {
    bisFalling_ = true;
    actorStartFallingTime_ = GameManager::getTime();
  }

  //Variable to store the new X position
  float newX = sprite_.getPosition().x; //Actual X position
  newX += -movementVelocity_ * actorMovement.left * ((0.5f * !bisGrounded_) + (1.0f * bisGrounded_)); //If going left
  newX += movementVelocity_ * actorMovement.right * ((0.5f * !bisGrounded_) + (1.0f * bisGrounded_)); //If going right

  float fallingTimePercent = ((float)(GameManager::getTime().asMilliseconds() - actorStartFallingTime_.asMilliseconds())) / timeToMaxFallingSpeed_;
  if (fallingTimePercent > 1.0f) fallingTimePercent = 1.0f;
  newY += gravityVelocity_ * fallingTimePercent * (actorMovement.down | !bisGrounded_) * !actorMovement.up; //If falling and not jumping
  sprite_.setPosition(newX, newY);
  if (GameManager::checkCollision(this)) {
    sprite_.setPosition(lastX, lastY);
    if (lastY <= newY) {
      printf("Ground: %f\n", newY);
      bisGrounded_ = true;
      bisFalling_ = false;
      bcanJump_ = true;
    }
  } else {
    bisGrounded_ = false;
    bcanJump_ = bcanJump_ & actorMovement.up;
  }
  printf(".");
  //Restart the movements
  actorMovement.left = false;
  actorMovement.right = false;
  actorMovement.up = false;
  actorMovement.down = false;
}

bool Actor::isJumping() {
  return actorMovement.up;
}

bool Actor::isGrounded() {
  return bisGrounded_;
}