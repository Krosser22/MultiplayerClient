/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/loginScene.h"

static struct LoginSceneData {
  ImGuiWindowFlags flags = 0;

  bool opened = true;

  float positionX = 0.0f;
  float positionY = 0.0f;

  float width = 200.0f;
  float height = 350.0f;

  char nick[32] = { "" };
  char password[32] = { "" };
  std::string info;
} data;

static void checkLogin(SceneData *sceneData) {
  data.info = ""; //Reset the info msg
  NetworkManager::Login(data.nick, data.password);
}

static void forgotPassword() {
  data.info = ""; //Reset the info msg
  SceneManager::ChangeScene("ForgotPassword");
}

static void createAccount() {
  data.info = ""; //Reset the info msg
  SceneManager::ChangeScene("CreateAccount");
}

void LoginScene::start() {
  GameManager::SetBackground("background.png"); //Set the background

  data.flags |= ImGuiWindowFlags_NoResize;
  data.flags |= ImGuiWindowFlags_NoMove;
  data.flags |= ImGuiWindowFlags_NoCollapse;
  data.flags |= ImGuiWindowFlags_NoTitleBar;

  data.positionX = GameManager::WindowWidth() * 0.5f - data.width * 0.5f;
  data.positionY = GameManager::WindowHeight() * 0.5f - data.height * 0.5f;

  NetworkManager::Logout();
}

void LoginScene::input() {}

void LoginScene::update() {
  ImGui::SetNextWindowPos(ImVec2(data.positionX, data.positionY));
  ImGui::Begin("Login", &data.opened, ImVec2(data.width, data.height), 0.0f, data.flags);
  {
    //Info
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), data.info.c_str());

    ImGui::NewLine();

    //Nick
    ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Nick:");
    ImGui::InputText("##Nick", data.nick, IM_ARRAYSIZE(data.nick));

    ImGui::NewLine();

    //Password
    ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Password:");
    ImGui::InputText("##Password", data.password, IM_ARRAYSIZE(data.password), ImGuiInputTextFlags_Password);

    ImGui::NewLine();

    //Check Login
    if (ImGui::Button("Login")) checkLogin(sceneData_);

    ImGui::NewLine();

    //Create Account
    if (ImGui::Button("Create Account")) createAccount();

    ImGui::NewLine();

    //Forgot Password
    if (ImGui::Button("Forgot Password")) forgotPassword();
  }
  ImGui::End();
  
  if (sceneData_->completed) {
    SceneManager::ChangeScene("Game");
  }
}

void LoginScene::finish() {}