/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/createAccountScene.h"

static struct CreateAccountSceneData {
  ImGuiWindowFlags flags = 0;

  bool opened = true;

  float positionX = 0.0f;
  float positionY = 0.0f;

  float width = 200.0f;
  float height = 350.0f;

  char email[32] = { "" };
  char nick[32] = { "" };
  char password1[32] = { "" };
  char password2[32] = { "" };
  std::string info;
} data;

static void createAccount() {
  data.info = ""; //Reset the info msg

  std::string strEmail = data.email;
  std::string strNick = data.nick;
  std::string strPass1 = data.password1;
  std::string strPass2 = data.password2;
  int atPos = strEmail.find('@');
  int dotPos = strEmail.find('.');
  if (atPos > 0 && dotPos > 0 && atPos < dotPos && !strNick.empty() && !strPass1.empty() && strPass1 == strPass2) {
    NetworkManager::CreateAccount(data.email, data.nick, data.password1);
  } else {
    data.info = "Something goes wrong";
  }
}

static void back() {
  data.info = ""; //Reset the info msg

  SceneManager::ChangeScene("Login");
}

void CreateAccountScene::start() {
  GameManager::SetBackground("background.png"); //Set the background

  data.flags |= ImGuiWindowFlags_NoResize;
  data.flags |= ImGuiWindowFlags_NoMove;
  data.flags |= ImGuiWindowFlags_NoCollapse;
  data.flags |= ImGuiWindowFlags_NoTitleBar;

  data.positionX = GameManager::WindowWidth() * 0.5f - data.width * 0.5f;
  data.positionY = GameManager::WindowHeight() * 0.5f - data.height * 0.5f;
}

void CreateAccountScene::input() {
  if (GameManager::WindowHasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      SceneManager::ChangeScene("Login");
    }
  }
}

void CreateAccountScene::update() {
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

    //Nick
    ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Nick:");
    ImGui::InputText("##Nick", data.nick, IM_ARRAYSIZE(data.nick));

    ImGui::NewLine();

    //Password 1
    ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Password:");
    ImGui::InputText("##Password1", data.password1, IM_ARRAYSIZE(data.password1), ImGuiInputTextFlags_Password);

    ImGui::NewLine();

    //Password 2
    ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Confirm Password:");
    ImGui::InputText("##Password2", data.password2, IM_ARRAYSIZE(data.password2), ImGuiInputTextFlags_Password);

    ImGui::NewLine();

    //Create Account
    if (ImGui::Button("Create Account")) createAccount();

    ImGui::NewLine();

    //Back
    if (ImGui::Button("Back")) back();
  }
  ImGui::End();

  if (sceneData_->completed) SceneManager::ChangeScene("Login");
}

void CreateAccountScene::finish() {}