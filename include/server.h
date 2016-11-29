/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __SERVER_H__
#define __SERVER_H__

namespace Server {
  //Starts the Server
  //void Start();

  //Finish the server
  //void Finish();

  //Send a TCP msg to the server
  void SendTCPMsgToServer(const char *msg);

  //Get a TCP msg from the server
  void GetTCPMsgFromServer();

  //Send a UPD msg to the server
  void SendUDPMsgToServer(const char *msg);

  //Starts the client
  void StartClient();

  //Finish the client
  void FinishClient();

  //Login with the server
  void Login(const char *user, const char *password);
};

#endif //__SERVER_H__