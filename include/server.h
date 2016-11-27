/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __SERVER_H__
#define __SERVER_H__

class Server {
public:
  //Starts the Server
  //void start();

  //Finish the server
  //void finish();

  //Send a TCP msg to the server
  static void sendTCPMsgToServer(const char *msg);

  //Send a UPD msg to the server
  static void sendUDPMsgToServer(const char *msg);

  static void startClient();

  static void finishClient();
};

#endif //__SERVER_H__