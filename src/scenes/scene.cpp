/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/scene.h"

void Scene::setName(std::string newName) {
  name_ = newName;
}

std::string Scene::name() {
  return name_;
}