/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __SERVER_H__
#define __SERVER_H__

#include <deque>
#include "actor.h"

struct SceneData {
  Actor player;
  std::vector<Object> enemies;
  bool completed = false;
  bool playing = false;
};

namespace Server {
  //Set the scene data
  void SetSceneData(SceneData *sceneData);

  //Starts the server
  void Start();

  //Finish the server
  void Finish();

  //Update the server
  void Update();

  //Send a UPD msg to the server
  void SendUDPMsgToServer(const char *msg);

  //Login with the server
  void Login(const char *nick, const char *password);

  //Send an email with the user and the password
  void ForgotPassword(const char *email);

  //Create an account into the BD of the server
  void CreateAccount(const char *email, const char *nick, const char *password);
};

#endif //__SERVER_H__