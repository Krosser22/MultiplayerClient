/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __SERVER_H__
#define __SERVER_H__

#define SERVER_PORT 8080

class Server {
public:
  //Starts the Server
  void start();

  //Update the server every frame
  void update();

  //Finish the server
  void finish();

  //Send a msg to the server
  static void sendMsgToServer(const char *msg);

  static void Client();
};

#endif //__SERVER_H__