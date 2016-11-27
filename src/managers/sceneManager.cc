/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "managers/sceneManager.h"
#include "managers/gameManager.h"
#include "scenes/gameScene.h"
#include "scenes/introScene.h"
#include <assert.h>

struct SceneData {
  Scene *actualScene;
  Scene *nextScene;
  bool sceneChanged = false;
  std::vector<Scene *> sceneList;
} sceneData;

Scene *getSceneByName(std::string sceneName) {
  Scene *scene = nullptr;

  for (unsigned int i = 0; i < sceneData.sceneList.size(); ++i) {
    if (sceneData.sceneList.at(i)->getName() == sceneName) {
      scene = sceneData.sceneList.at(i);
    }
  }
  return scene;
}

void SceneManager::AddScene(Scene *scene) {
  sceneData.sceneList.push_back(scene);
}

void SceneManager::StartSceneManager(std::string sceneName) {
  //Starts the GameManager
  GameManager::start();

  //Set the default values of the scene
  sceneData.nextScene = getSceneByName(sceneName);
  sceneData.actualScene = sceneData.nextScene;

  //Start the default scene
  sceneData.actualScene->start();

  //Main loop
  while (GameManager::isOpen()) {
    if (sceneData.sceneChanged) {
      sceneData.actualScene->finish();
      sceneData.actualScene = sceneData.nextScene;
      sceneData.actualScene->start();
      sceneData.sceneChanged = false;
    }
    sceneData.actualScene = sceneData.nextScene;
    sceneData.actualScene->input();
    sceneData.actualScene->update();
    GameManager::draw();
  }

  //Finish the game
  sceneData.actualScene->finish();
  sceneData.actualScene = nullptr;
  sceneData.nextScene = nullptr;
  GameManager::finish();
}

void SceneManager::ChangeScene(std::string sceneName) {
  sceneData.nextScene = getSceneByName(sceneName);
  sceneData.sceneChanged = true;
}