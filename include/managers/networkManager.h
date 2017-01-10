/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __NETWORK_MANAGER_H__
#define __NETWORK_MANAGER_H__

#include <deque>
#include "actor.h"

struct SceneData {
  //Gets an actor with the ID given as a parameter
  Actor *getActor(std::string *ID) {
    if (player.ID() == *ID) {
      return &player;
    } else {
      bool found = false;
      Actor *actorFound = nullptr;
      for (unsigned int i = 0; i < enemies.size() && !found; ++i) {
        if (enemies.at(i)->ID() == *ID) {
          found = true;
          actorFound = enemies.at(i);
        }
      }
      return actorFound;
    }
  }

  //Gets an enemy with the ID given as a parameter
  Actor *getEnemy(std::string *ID) {
    bool found = false;
    Actor *actorFound = nullptr;
    for (unsigned int i = 0; i < enemies.size() && !found; ++i) {
      if (enemies.at(i)->ID() == *ID) {
        found = true;
        actorFound = enemies.at(i);
      }
    }
    return actorFound;
  }

  //Gets a pickup with an ID given as a parameter
  /*Pickup *getPickup(std::string *ID) {
    bool found = false;
    Pickup *pickupFound = nullptr;
    for (unsigned int i = 0; i < pickups.size() && !found; ++i) {
      if (pickups.at(i)->ID() == *ID) {
        found = true;
        pickupFound = pickups.at(i);
      }
    }
    return pickupFound;
  }*/

  Actor player;

  std::vector<Actor *> enemies;

  std::vector<Bullet *> bullets;

  //std::vector<Pickup *> pickups;

  bool completed = false;
  bool playing = false;
};

namespace NetworkManager {
  //Set the scene data
  void SetSceneData(SceneData *sceneData);

  //Starts the server
  void Start();

  //Finish the server
  void Finish();

  //Update the server
  void Update();

  //Sends a TCP msg to the server
  void SendTCPMsgToServer(const char *msg);

  //Sends a UPD msg to the server
  void SendUDPMsgToServer(const char *msg);

  //Login on the server
  void Login(const char *nick, const char *password);

  //Logout
  void Logout();

  //Send an email with the user and the password
  void ForgotPassword(const char *email);

  //Create an account into the BD of the server
  void CreateAccount(const char *email, const char *nick, const char *password);

  //Send a msg on the chat
  void SendChatMsg(const char *newMsg);

  //Gets the latency in ms
  int getLatency();
};

#endif //__NETWORK_MANAGER_H__