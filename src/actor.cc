/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <deque>
#include "actor.h"
#include "managers/gameManager.h"
#include "server.h"

static int IDCount = 0;
static struct ActorMovement {
  ActorMovement() {
    left = false;
    right = false;
    up = false;
    down = false;
    ID = ++IDCount;
  }
  bool left;
  bool right;
  bool up;
  bool down;
  int ID;
} movement;

#define kMovementDelay 5

std::deque<ActorMovement> movementList;

Actor::Actor() {
  for (unsigned int i = 0; i < kMovementDelay; ++i) {
    ActorMovement a;
    movementList.push_back(a);
  }
}

Actor::~Actor() {}

void Actor::moveLeft() {
  movement.left = true;
}

void Actor::moveRight() {
  movement.right = true;
}

void Actor::jump() {
  movement.up = true;
}

void Actor::crouch() {
  movement.down = true;
}

void Actor::updateCollisions() {
  movementList.push_back(movement);
  movement = movementList.front();
  printf("%d\n", movement.ID);
  movementList.pop_front();
  //Backup of the last valid position
  float lastX = sprite_.getPosition().x;
  float lastY = sprite_.getPosition().y;

  //Variable to store the new X position
  float newX = sprite_.getPosition().x; //Actual X position
  newX += movement.left * ((-movementVelocityOnAir_ * !bIsGrounded_) + (-movementVelocity_ * bIsGrounded_)); //If going left
  newX += movement.right * ((movementVelocityOnAir_ * !bIsGrounded_) + (movementVelocity_ * bIsGrounded_)); //If going right

  if (movement.up) {
    if (bIsGrounded_) {
      jumpImpulse_ = -jumpVelocity_;
      actorStartJumpTime_ = GameManager::Time();
      actorMaxJumpTime_ = actorStartJumpTime_ + sf::milliseconds(timeToBeJumping_);
    }
  } else if (jumpImpulse_ < 0.0f) {
    jumpImpulse_ *= 0.8f;
  }

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
  if (GameManager::CheckCollision(this)) {
    finalX = lastX;
  }

  //Check vertical collisions
  sprite_.setPosition(lastX, newY);
  if (GameManager::CheckCollision(this)) {
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
  movement.left = false;
  movement.right = false;
  movement.up = false;
  movement.down = false;
  movement.ID = ++IDCount;
}

bool Actor::isJumping() {
  return movement.up;
}

bool Actor::isGrounded() {
  return bIsGrounded_;
}