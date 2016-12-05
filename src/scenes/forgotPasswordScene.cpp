/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/forgotPasswordScene.h"

static struct ForgotPasswordSceneData {
  ImGuiWindowFlags flags = 0;

  bool opened = true;

  float positionX = 0.0f;
  float positionY = 0.0f;

  float width = 200.0f;
  float height = 350.0f;

  char email[32] = { "" };
  std::string info;
} data;

static void sendInfoToEmail() {
  data.info = ""; //Reset the info msg
  std::string strEmail = data.email;
  int atPos = strEmail.find('@');
  int dotPos = strEmail.find('.');
  if (atPos > 0 && dotPos > 0 && atPos < dotPos) {
    if (Server::ForgotPassword(data.email)) {
      SceneManager::ChangeScene("Login");
    } else {
      data.info = "Something goes wrong";
    }
  } else {
    data.info = "Incorrect Email format";
  }
}

static void back() {
  data.info = ""; //Reset the info msg

  SceneManager::ChangeScene("Login");
}

void ForgotPasswordScene::start() {
  GameManager::SetBackground("background.png"); //Set the background

  data.flags |= ImGuiWindowFlags_NoResize;
  data.flags |= ImGuiWindowFlags_NoMove;
  data.flags |= ImGuiWindowFlags_NoCollapse;
  data.flags |= ImGuiWindowFlags_NoTitleBar;

  data.positionX = GameManager::WindowWidth() * 0.5f - data.width * 0.5f;
  data.positionY = GameManager::WindowHeight() * 0.5f - data.height * 0.5f;
}

void ForgotPasswordScene::input() {
  if (GameManager::WindowHasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      SceneManager::ChangeScene("Login");
    }
  }
}

void ForgotPasswordScene::update() {
  ImGui::SetNextWindowPos(ImVec2(data.positionX, data.positionY));
  ImGui::Begin("CreateAccount", &data.opened, ImVec2(data.width, data.height), 0.0f, data.flags);
  {
    //Info
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), data.info.c_str());

    ImGui::NewLine();

    //Email
    ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Email:");
    ImGui::InputText("##Email", data.email, IM_ARRAYSIZE(data.email));

    ImGui::NewLine();

    //Create Account
    if (ImGui::Button("Send To Email")) sendInfoToEmail();

    ImGui::NewLine();

    //Back
    if (ImGui::Button("Back")) back();
  }
  ImGui::End();
}

void ForgotPasswordScene::finish() {}