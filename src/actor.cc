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
#include "managers/networkManager.h"


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
  movement_.left = true;
}

void Actor::moveRight() {
  movement_.right = true;
}

void Actor::jump() {
  movement_.up = true;
}

void Actor::crouch() {
  movement_.down = true;
}

void Actor::interact() {
  movement_.interact = true;
}

void Actor::action() {
  movement_.action = true;
}

void Actor::updateCollisions() {
  movementList.push_back(movement_);
  movement_ = movementList.front();
  //printf("%d\n", movement.ID);
  movementList.pop_front();
  //Backup of the last valid position
  float lastX = sprite_.getPosition().x;
  float lastY = sprite_.getPosition().y;

  //Variable to store the new X position
  float newX = sprite_.getPosition().x; //Actual X position
  newX += movement_.left * ((-movementVelocityOnAir_ * !bIsGrounded_) + (-movementVelocity_ * bIsGrounded_)); //If going left
  newX += movement_.right * ((movementVelocityOnAir_ * !bIsGrounded_) + (movementVelocity_ * bIsGrounded_)); //If going right

  if (movement_.up) {
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
  movement_.left = false;
  movement_.right = false;
  movement_.up = false;
  movement_.down = false;
  movement_.interact = false;
  movement_.action = false;
  movement_.sound = false;
  movement_.drop = false;
}

bool Actor::isJumping() {
  return movement_.up;
}

bool Actor::isGrounded() {
  return bIsGrounded_;
}

bool Actor::isInteracting() {
  return movement_.interact;
}

/*void Actor::getPickup(Pickup *pickup) {
  weapon_ = pickup;
}*/

void Actor::setLife(float life) {
  life_ = life;
}

float Actor::life() {
  return life_;
}

void Actor::damage(float damage) {
  life_ -= damage;

  if (life_ <= 0) {
    life_ = 0;
  } else if (life_ > maxLife_) {
    life_ = maxLife_;
  }
}

ActorMovement Actor::getMovement() {
  return movement_;
}