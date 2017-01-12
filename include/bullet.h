/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __BULLET_H__
#define __BULLET_H__

#include "object.h"

const float kVelocity = 3.0f;

class Bullet : public Object {
public:
  Bullet();
  ~Bullet();

  float speedX = 0.0f;
  float speedY = 0.0f;
  float damage = 22.0f;
  std::string ownerID;
};

#endif //__BULLET_H__