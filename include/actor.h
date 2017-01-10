/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "bullet.h"

struct ActorMovement {
  ActorMovement() {
    left = false;
    right = false;
    up = false;
    down = false;
    interact = false;
    action = false;
    sound = false;
    drop = false;
  }
  bool left;
  bool right;
  bool up;
  bool down;
  bool interact;
  bool action;
  bool sound;
  bool drop;
};

class Actor : public Object {
public:
  Actor();
  ~Actor();

  //Move the actor to the left
  void moveLeft();

  //Move the actor to the right
  void moveRight();

  //Makes the actor jump
  void jump();

  //Makes the actor crouch
  void crouch();

  //Interacts with anything near you
  void interact();

  //Shoots at the movement direction
  void action();

  //Update the collisions (This function will be called at the gameManager)
  void updateCollisions();

  //Return if the actor is jumping
  bool isJumping();

  //Return if the actor is grounded
  bool isGrounded();

  //Return if the actor is interacting
  bool isInteracting();

  //Gets a pickup
  //void getPickup(Pickup *pickup);

  //Sets the life of the actor
  void setLife(float life);

  //Return the life of the actor
  float life();

  //Damage the actor
  void damage(float damage);

  ActorMovement getMovement();

private:
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

  ActorMovement movement_;

  //The actual weapon
  //Weapon *weapon_;

  float maxLife_ = 100.0f;

  float life_ = 100.0f;
};

#endif //__ACTOR_H__