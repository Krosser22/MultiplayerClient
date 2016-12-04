/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <assert.h>
#include <imgui.h>
#include <imgui-sfml.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "managers/UIManager.h"
#include "managers/sceneManager.h"
#include "managers/gameManager.h"

static struct SceneData {
  sf::RenderWindow window;
  Scene *actualScene;
  Scene *nextScene;
  bool sceneChanged = false;
  std::vector<Scene *> sceneList;
  std::vector<Scene *> popupSceneList;
  std::vector<Scene *> visiblePopupSceneList;
} data;

Scene *getSceneByName(std::string sceneName) {
  Scene *scene = nullptr;

  for (unsigned int i = 0; i < data.sceneList.size(); ++i) {
    if (data.sceneList.at(i)->name() == sceneName) {
      scene = data.sceneList.at(i);
    }
  }
  return scene;
}

Scene *getPopupSceneByName(std::string sceneName) {
  Scene *scene = nullptr;

  for (unsigned int i = 0; i < data.popupSceneList.size(); ++i) {
    if (data.popupSceneList.at(i)->name() == sceneName) {
      scene = data.popupSceneList.at(i);
    }
  }
  return scene;
}

void SceneManager::AddScene(Scene *scene) {
  data.sceneList.push_back(scene);
}

void SceneManager::AddPopupScene(Scene *scene) {
  data.popupSceneList.push_back(scene);
}

void SceneManager::PopInScene(std::string sceneName) {
  Scene *scene = getPopupSceneByName(sceneName);

  if (scene != nullptr) {
    data.visiblePopupSceneList.push_back(scene);
  }
}

void SceneManager::PopOutScene(std::string sceneName) {
  Scene *scene = getPopupSceneByName(sceneName);
  for (unsigned int i = 0; i < data.visiblePopupSceneList.size(); ++i) {
    if (scene == data.visiblePopupSceneList.at(i)) {
      data.visiblePopupSceneList.erase(data.visiblePopupSceneList.begin() + i);
      //IS THIS WORKING???
    }
  }
}

void SceneManager::StartSceneManager(std::string sceneName) {
  //Create the window with a default values
  data.window.create(sf::VideoMode(GameManager::WindowWidth(), GameManager::WindowHeight()), "MultiplayerClient");
  data.window.setFramerateLimit(60);
  //data.window.setVerticalSyncEnabled(true);

  //Starts the GameManager
  GameManager::Start(&data.window);

  //Starts the UIManager
  ImGui::SFML::Init(data.window);
  UIManager::Start(&data.window);

  //Set the default values of the scene
  data.nextScene = getSceneByName(sceneName);
  data.actualScene = data.nextScene;

  //Start the default scene
  data.actualScene->start();

  sf::Clock deltaClock;
  data.window.clear(sf::Color::White);

  //Main loop
  while (GameManager::IsOpen()) {
    ImGui::SFML::Update(data.window, deltaClock.restart());
    if (data.sceneChanged) {
      UIManager::ClearUI();
      GameManager::ClearDrawList();
      data.actualScene->finish();
      data.actualScene = data.nextScene;
      data.actualScene->start();
      data.sceneChanged = false;
    }
    data.actualScene = data.nextScene;
    data.actualScene->input();
    data.actualScene->update();
    UIManager::Update();
    
    //For testing
    ImGui::ShowTestWindow();

    GameManager::Draw();
    UIManager::Draw();
    ImGui::Render();
    data.window.resetGLStates();
    data.window.display();
  }

  //Finish the game
  ImGui::SFML::Shutdown();
  data.actualScene->finish();
  data.actualScene = nullptr;
  data.nextScene = nullptr;
  GameManager::Finish();
}

void SceneManager::ChangeScene(std::string sceneName) {
  Scene *newScene = getSceneByName(sceneName);

  if (newScene != nullptr) {
    data.nextScene = newScene;
    data.sceneChanged = true;
  } else {
    printf("ERROR LOADING SCENE: NOT FOUND\n");
  }
}