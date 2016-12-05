/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <imgui.h>
#include <string>
#include <imgui-sfml.h>
#include "UI/UIChat.h"
#include "input.h"

static struct UIChatData {
  ImGuiWindowFlags window_flags = 0;

  bool opened = true;

  int nextPushID = 0;

  float windowWidth = 0.0f;
  float windowHeight = 0.0f;
} data;

void init() {
  data.window_flags |= ImGuiWindowFlags_NoResize;
  data.window_flags |= ImGuiWindowFlags_NoMove;
  data.window_flags |= ImGuiWindowFlags_NoCollapse;
  //data.window_flags |= ImGuiWindowFlags_ShowBorders;
  //data.window_flags |= ImGuiWindowFlags_NoTitleBar;
  //data.window_flags |= ImGuiWindowFlags_NoScrollbar;
  //data.window_flags |= ImGuiWindowFlags_MenuBar;
}

void UIChat::UIChat() {
  static bool initialized = false;
  if (!initialized) {
    initialized = true;
    init();
  }

  /*if (INPUT::IsKeyDown('c') || INPUT::IsKeyDown('C')) {
    data.opened = !data.opened;
    printf("%d\n\n\n", data.opened);
  } else {
    printf("H");
  }*/
  if (INPUT::IsKeyDown('j')) {
    printf("YEAH");
  }
}