/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/System/Time.hpp>
#include "actor.h"
#include "managers/gameManager.h"
#include "server.h"

struct ActorMovement {
  bool left;
  bool right;
  bool up;
  bool down;
} actorMovement;

Actor::Actor() {}

Actor::~Actor() {}

void Actor::moveLeft() {
  actorMovement.left = true;
  Server::sendUDPMsgToServer("Left");
}

void Actor::moveRight() {
  actorMovement.right = true;
  Server::sendUDPMsgToServer("Right");
}

void Actor::jump() {
  actorMovement.up = true;
  Server::sendUDPMsgToServer("Jumping");

  if (bIsGrounded_) {
    jumpImpulse_ = -jumpVelocity_;
    actorStartJumpTime_ = GameManager::getTime();
    actorMaxJumpTime_ = actorStartJumpTime_ + sf::milliseconds(timeToBeJumping_);
  }
}

void Actor::stopJumping() {
  if (jumpImpulse_ < 0.0f) {
    Server::sendUDPMsgToServer("StopJumping");
    jumpImpulse_ *= 0.8f;
  }
}

void Actor::crouch() {
  actorMovement.down = true;
}

void Actor::updateCollisions() {
  //Backup of the last valid position
  float lastX = sprite_.getPosition().x;
  float lastY = sprite_.getPosition().y;

  //Variable to store the new X position
  float newX = sprite_.getPosition().x; //Actual X position
  newX += actorMovement.left * ((-movementVelocityOnAir_ * !bIsGrounded_) + (-movementVelocity_ * bIsGrounded_)); //If going left
  newX += actorMovement.right * ((movementVelocityOnAir_ * !bIsGrounded_) + (movementVelocity_ * bIsGrounded_)); //If going right

  //Variable to store the new Y position
  float newY = sprite_.getPosition().y; //Actual Y position
  newY += jumpImpulse_;
  //Jumping
  //float jumpTimePercent = ((float)(GameManager::getTime().asMilliseconds() - actorStartJumpTime_.asMilliseconds())) / timeToBeJumping_;
  //newY += -jumpVelocity_ * (1.0f - jumpTimePercent) * actorMovement.up; //If jumping
  //Falling
  //newY += gravityVelocity_ * !bIsGrounded_;
  //float fallingTimePercent = ((float)(GameManager::getTime().asMilliseconds() - actorStartFallingTime_.asMilliseconds())) / timeToMaxFallingSpeed_;
  //if (fallingTimePercent > 1.0f) fallingTimePercent = 1.0f;
  //newY += gravityVelocity_ * fallingTimePercent * (actorMovement.down | !bIsGrounded_) * !actorMovement.up; //If falling and not jumping
  
  //Collisions
  float finalX = newX, finalY = newY;

  //Check horizontal collisions
  sprite_.setPosition(newX, lastY);
  if (GameManager::checkCollision(this)) {
    finalX = lastX;
  }

  //Check vertical collisions
  sprite_.setPosition(lastX, newY);
  if (GameManager::checkCollision(this)) {
    finalY = lastY;
    if (lastY < newY) {
      bIsGrounded_ = true;
    } else {
      jumpImpulse_ = gravityVelocity_;
    }
  } else {
    bIsGrounded_ = false;
  }

  jumpImpulse_ += jumpImpulseDecrease_;
  if (jumpImpulse_ > gravityVelocity_) jumpImpulse_ = gravityVelocity_;

  //Confirm the final position after the collisions
  sprite_.setPosition(finalX, finalY);

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
  return bIsGrounded_;
}