/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <assert.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "managers/sceneManager.h"
#include "managers/gameManager.h"
#include "input.h"
#include "UI/UIChat.h"

static struct SceneManagerData {
  sf::RenderWindow window;
  Scene *actualScene;
  Scene *nextScene;
  bool sceneChanged = false;
  std::vector<Scene *> sceneList;
  std::vector<Scene *> popupSceneList;
  std::vector<Scene *> visiblePopupSceneList;
  SceneData sceneData;
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
  sf::Clock deltaClock;

  //Init
  {
    //Create the window with a default values
    data.window.create(sf::VideoMode(GameManager::WindowWidth(), GameManager::WindowHeight()), "MultiplayerClient", !sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close);
    data.window.setFramerateLimit(60);
    //data.window.setVerticalSyncEnabled(true);
    
    //Starts the GameManager
    GameManager::Start(&data.window);

    //Starts the SFML+ImGui
    ImGui::SFML::Init(data.window);

    //Set the default values of the scene
    data.nextScene = getSceneByName(sceneName);
    data.actualScene = data.nextScene;

    //Server
    NetworkManager::Start();
    NetworkManager::SetSceneData(&data.sceneData);

    //Start the default scene
    data.actualScene->start();
    data.actualScene->sceneData_ = &data.sceneData;

    data.window.clear(sf::Color::White);

    //ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.ChildWindowRounding = 0.0f;
    style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    //style.Colors[ImGuiCol_TextHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //style.Colors[ImGuiCol_TextActive] = ImVec4(1.00f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
    style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    //style.Colors[ImGuiCol_TooltipBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    //Chat
    UIChat::Init();
  }
  
  //Main loop
  sf::Event newEvent;
  while (GameManager::IsOpen()) {
    //Input
    MYINPUT::Update();
    while (data.window.pollEvent(newEvent)) {
      ImGui::SFML::ProcessEvent(newEvent);

      //Close windows
      if (newEvent.type == sf::Event::Closed) GameManager::CloseWindow();
    }

    //Update
    ImGui::SFML::Update(data.window, deltaClock.restart());
    if (data.sceneChanged) {
      GameManager::ClearDrawList();
      data.actualScene->finish();
      data.actualScene = data.nextScene;
      NetworkManager::SetSceneData(&data.sceneData);
      data.actualScene->sceneData_ = &data.sceneData;
      data.actualScene->start();
      data.sceneChanged = false;
    }
    data.actualScene = data.nextScene;
    data.actualScene->input();
    data.actualScene->update();
    
    //For testing
    //ImGui::ShowTestWindow();

    //Server
    NetworkManager::Update();

    //FPS and Latency
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    if (ImGui::BeginMainMenuBar()) {
      char fps[256];
      sprintf(fps, "%.3f ms/frame (%.1f FPS), Latency: %dms", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate, NetworkManager::getLatency());
      ImGui::MenuItem(fps);
      ImGui::EndMainMenuBar();
    }

    //Draw
    GameManager::Draw();
    ImGui::Render();
    data.window.display();
    data.window.resetGLStates();
  }

  //Finish the game
  NetworkManager::Finish();
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

std::vector<Bullet *> *SceneManager::getBullets() {
  return &data.sceneData.bullets;
}

Actor *SceneManager::getPlayer() {
  return &data.sceneData.player;
}