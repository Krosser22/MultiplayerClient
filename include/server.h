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
  //Send a UPD msg to the server
  void SendUDPMsgToServer(const char *msg);

  //Login with the server
  bool Login(const char *user, const char *password);
};

#endif //__SERVER_H__