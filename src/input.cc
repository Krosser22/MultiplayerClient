/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <imgui.h>
#include <stdio.h>
#include "input.h"

ImGuiIO& io = ImGui::GetIO();
ImGuiIO ioFrameBefore;

void MYINPUT::Update() {
  ioFrameBefore = io;
}

bool MYINPUT::IsKeyDown(unsigned char key) {
  /*for (unsigned int i = 0; i < 512; ++i) {
    if (io.KeysDown[i]) {
      printf("YEAH: %d\n", i);
    }
  }*/
  return (io.KeysDown[(unsigned int)key - 97]);
}

bool MYINPUT::IsKeyPressed(unsigned char key) {
  bool before = ioFrameBefore.KeysDown[(unsigned int)key - 97];
  bool now = io.KeysDown[(unsigned int)key - 97];
  return (!before && now);
}

bool MYINPUT::IsKeyReleased(unsigned char key) {
  bool before = ioFrameBefore.KeysDown[(unsigned int)key - 97];
  bool now = io.KeysDown[(unsigned int)key - 97];
  return (before && !now);
}

bool MYINPUT::IsMouseDown(unsigned char button) {
  return (io.MouseDown[(unsigned int)button]);
}

bool MYINPUT::IsMousePressed(unsigned char button) {
  return (io.MouseClicked[(unsigned int)button]);
}

bool MYINPUT::IsMouseReleased(unsigned char button) {
  return (io.MouseReleased[(unsigned int)button]);
}

float MYINPUT::MouseWheel() {
  return (io.MouseWheel);
}

float MYINPUT::MousePositionX() {
  return (io.MousePos.x);
}

float MYINPUT::MousePositionY() {
  return (io.MousePos.y);
}