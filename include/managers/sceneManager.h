/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "scenes/scene.h"

namespace SceneManager {
  void AddScene(Scene *scene);

  void StartSceneManager(std::string sceneName);

  void ChangeScene(std::string sceneName);
};

#endif //__SCENE_MANAGER_H__