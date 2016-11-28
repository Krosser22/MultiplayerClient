/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "managers/UIManager.h"
#include "managers/sceneManager.h"
#include "managers/gameManager.h"
#include "scenes/gameScene.h"
#include "scenes/introScene.h"
#include <assert.h>

struct SceneData {
  sf::RenderWindow window;
  Scene *actualScene;
  Scene *nextScene;
  bool sceneChanged = false;
  std::vector<Scene *> sceneList;
} sceneData;

Scene *getSceneByName(std::string sceneName) {
  Scene *scene = nullptr;

  for (unsigned int i = 0; i < sceneData.sceneList.size(); ++i) {
    if (sceneData.sceneList.at(i)->name() == sceneName) {
      scene = sceneData.sceneList.at(i);
    }
  }
  return scene;
}

void SceneManager::AddScene(Scene *scene) {
  sceneData.sceneList.push_back(scene);
}

void SceneManager::StartSceneManager(std::string sceneName) {
  //Create the window with a default values
  sceneData.window.create(sf::VideoMode(GameManager::WindowWidth(), GameManager::WindowHeight()), "Multiplayer");
  sceneData.window.setFramerateLimit(60);

  //Starts the GameManager
  GameManager::Start(&sceneData.window);

  //Starts the UIManager
  UIManager::Start(&sceneData.window);

  //Set the default values of the scene
  sceneData.nextScene = getSceneByName(sceneName);
  sceneData.actualScene = sceneData.nextScene;

  //Start the default scene
  sceneData.actualScene->start();

  //Main loop
  while (GameManager::IsOpen()) {
    if (sceneData.sceneChanged) {
      UIManager::ClearUI();
      sceneData.actualScene->finish();
      sceneData.actualScene = sceneData.nextScene;
      sceneData.actualScene->start();
      sceneData.sceneChanged = false;
    }
    sceneData.actualScene = sceneData.nextScene;
    sceneData.actualScene->input();
    sceneData.actualScene->update();
    UIManager::Update();

    //Display the buffer on the screen
    GameManager::Draw();
    UIManager::Draw();
    sceneData.window.display();
  }

  //Finish the game
  sceneData.actualScene->finish();
  sceneData.actualScene = nullptr;
  sceneData.nextScene = nullptr;
  GameManager::Finish();
}

void SceneManager::ChangeScene(std::string sceneName) {
  Scene *newScene = getSceneByName(sceneName);

  if (newScene != nullptr) {
    sceneData.nextScene = newScene;
    sceneData.sceneChanged = true;
  } else {
    printf("ERROR LOADING SCENE: NOT FOUND\n");
  }
}