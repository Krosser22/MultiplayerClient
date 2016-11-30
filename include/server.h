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

  //Connects with the server
  bool Connect();

  //Disconnect with the server
  void Disconnect();

  //Send a TCP msg to the server
  void SendTCPMsgToServer(const char *msg);

  //Get a TCP msg from the server
  char *GetTCPMsgFromServer();

  //Send a UPD msg to the server
  void SendUDPMsgToServer(const char *msg);

  //Login with the server
  void Login(const char *user, const char *password);
};

#endif //__SERVER_H__