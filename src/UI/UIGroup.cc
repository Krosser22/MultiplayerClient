/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <imgui-sfml.h>
#include "UI/UIGroup.h"
#include "managers/networkManager.h"
#include "input.h"

void UIGroup::Draw(bool open) {
  if (open) {
    ImGui::SetNextWindowSize(ImVec2(150, 120), ImGuiSetCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(660, 584), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Group", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders);

    char label[32]; sprintf(label, "[%s]", NetworkManager::GetSceneData()->player.ID().c_str());
    ImGui::Bullet(); ImGui::Text(label);
    for (unsigned int i = 0; i < NetworkManager::GetSceneData()->enemies.size(); ++i) {
      sprintf(label, "[%s]", NetworkManager::GetSceneData()->enemies.at(i)->ID().c_str());
      ImGui::Bullet(); ImGui::Text(label);
    }
    for (unsigned int i = NetworkManager::GetSceneData()->enemies.size(); i < 2; ++i) {
      ImGui::Bullet(); ImGui::Text("[]");
    }
    ImGui::End();
  }
}