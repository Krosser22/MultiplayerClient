/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <imgui-sfml.h>
#include "UI/UIChat.h"
#include "managers/networkManager.h"
#include "input.h"

struct UIChatData {
  ImGuiTextBuffer Buf;
  ImVector<int> LineOffsets; // Index to lines offset
  bool ScrollToBottom;

  void Clear() {
    Buf.clear();
    LineOffsets.clear();
  }

  void AddLine(const char* fmt, ...) IM_PRINTFARGS(2) {
    int old_size = Buf.size();
    va_list args;
    va_start(args, fmt);
    Buf.appendv(fmt, args);
    va_end(args);
    for (int new_size = Buf.size(); old_size < new_size; old_size++) {
      if (Buf[old_size] == '\n') {
        LineOffsets.push_back(old_size);
      }
    }
    ScrollToBottom = true;
  }

  void Draw(const char *title, bool open) {
    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 504), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(title, &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
    ImGui::BeginChild("scrolling", ImVec2(0, 159), false, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::TextUnformatted(Buf.begin());

    if (ScrollToBottom) {
      ImGui::SetScrollHere(1.0f);
    }
    ScrollToBottom = false;
    ImGui::EndChild();

    ImGui::Separator();
    const int kNewLineMax = 31; //31 = 32 - '\n'
    static char newLine[kNewLineMax] = "";

    //Input text with new line to chat
    ImGui::SetKeyboardFocusHere();

    if (!open) {
      ImGui::NewLine();
      ImGui::NewLine();
    }

    if (ImGui::InputText("", newLine, IM_ARRAYSIZE(newLine), ImGuiInputTextFlags_EnterReturnsTrue)) {
      if (INPUT::IsKeyPressed(INPUT_KEY_ENTER)) {
        if (newLine[0] != '\0') {
          std::strcat(newLine, "\n");
          NetworkManager::SendChatMsg(newLine);
          for (unsigned int i = 0; i < kNewLineMax; ++i) {
            newLine[i] = '\0';
          }
        }
      }
    }

    ImGui::End();
  }
};

UIChatData *data;

void UIChat::Init() {
  static UIChatData newData;
  data = &newData;
  data->Clear();
}

void UIChat::Draw(bool open) {
  /*// Demo fill
  static float last_time = -1.0f;
  float time = ImGui::GetTime();
  if (time - last_time >= 0.3f) {
    const char* random_words[] = { "system", "info", "warning", "error", "fatal", "notice", "log" };
    data->AddLine("[%s] Hello, time is %.1f, rand() %d\n", random_words[rand() % IM_ARRAYSIZE(random_words)], time, (int)rand());
    last_time = time;
  }*/
  data->Draw("Chat", open);
}

void UIChat::AddLine(const char *user, const char *newLine) {
  data->AddLine("[%s]: %s\n", user, newLine);
}

void UIChat::Clear() {
  data->Clear();
}