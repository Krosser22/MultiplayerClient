/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <imgui-sfml.h>
#include "UI/UIRank.h"
#include "managers/networkManager.h"
#include "managers/gameManager.h"
#include "input.h"

struct RankingPlayer {
  RankingPlayer(int newPoints, std::string newNick) {
    points = newPoints;
    nick = newNick;
  }
  int points;
  std::string nick;
};

static struct UIRankData {
  sf::Time lastUpdate;
  const float kTimeToUpdate = 5.0f;
  std::vector<RankingPlayer> players;
} data;

void UIRank::Draw(bool open) {
  if (open) {
    ImGui::SetNextWindowSize(ImVec2(150, 120), ImGuiSetCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(810, 584), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Ranking", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders);
    for (unsigned int i = 0; i < data.players.size(); ++i) {
      char label[32]; sprintf(label, "%d [%s]", data.players.at(i).points, data.players.at(i).nick.c_str());
      ImGui::Bullet(); ImGui::Text(label);
    }
    ImGui::End();
  }

  //Update the info
  if (data.lastUpdate.asSeconds() + data.kTimeToUpdate < GameManager::Time().asSeconds()) {
    data.lastUpdate = GameManager::Time();
    NetworkManager::SendTCPMsgToServer("Ranking\0");
  }
}

void UIRank::AddData(int points, std::string nick) {
  data.players.push_back(RankingPlayer(points, nick));
}

void UIRank::Clear() {
  data.players.clear();
}