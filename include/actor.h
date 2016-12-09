/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "object.h"

class Actor : public Object {
public:
  Actor();
  ~Actor();

  void setID(std::string *newID);

  std::string ID();

  //Move the actor to the left
  void moveLeft();

  //Move the actor to the right
  void moveRight();

  //Makes the actor jump
  void jump();

  //Makes the actor crouch
  void crouch();

  //Update the collisions (This function will be called at the gameManager
  void updateCollisions();

  //Return if the actor is jumping
  bool isJumping();

  //Return if the actor is grounded
  bool isGrounded();

private:
  //The ID of the actor
  std::string ID_;

  //The velocity to the left and right movements
  float movementVelocity_ = 6.22f;

  //The movement velocity when is in air
  float movementVelocityOnAir_ = 4.4f;

  //The jump velocity
  float jumpVelocity_ = 14.22f;

  //The impulse of the jump
  float jumpImpulse_ = 0.0f;

  //The decrease of the impulse of the jump
  float jumpImpulseDecrease_ = 0.4f;

  //The gravity velocity
  float gravityVelocity_ = 6.4f;

  //If the player is grounded
  bool bIsGrounded_ = false;

  //The max time the actor can jump until starts falling
  sf::Time actorMaxJumpTime_;

  //The time when the actor starts the jump
  sf::Time actorStartJumpTime_;

  //Time to be jumping in milliseconds
  int timeToBeJumping_ = 1000;

  //The time the actor starts falling
  sf::Time actorStartFallingTime_;

  //The time to get the max falling speed
  float timeToMaxFallingSpeed_ = 600;
};

#endif //__ACTOR_H__