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
  enum Status {
    Done = 0,
    Off,
    Error,
  };

  //Send a UPD msg to the server
  void SendUDPMsgToServer(const char *msg);

  //Login with the server
  bool Login(const char *nick, const char *password);

  //Send an email with the user and the password
  bool ForgotPassword(const char *email);

  //Create an account into the BD of the server
  bool CreateAccount(const char *email, const char *nick, const char *password);
};

#endif //__SERVER_H__