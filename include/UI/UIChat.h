/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __UI_CHAT_H__
#define __UI_CHAT_H__

namespace UIChat {
  //Init the Chat
  void Init();

  //Draw the char
  void Draw();

  //Add a new line to the chat
  void AddLine(const char *user, const char *newLine);

  //Clear the chat
  void Clear();
}

#endif //__UI_CHAT_H__