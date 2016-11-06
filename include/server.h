/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __SERVER_H__
#define __SERVER_H__

#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

class Server {
public:
  //Starts the Server
  void start();

  void update();

  void finish();
private:
  //Utilizada para definir el tamaño de un array de caracteres --> char[max_line]
  static const int max_line = 2048;

  //Indica el puerto del servidor web
  unsigned int puerto = 8080;

  //Almacena los mensajes que lleguen al servidor
  char msg[max_line];

  //Socket del servidor y cliente
  SOCKET sock_s, sock_c;

  //IP del servidor y cliente
  struct sockaddr_in ip_s, ip_c;

  int size = 0;

  void sendError();

  void readWeb();
};

#endif //__SERVER_H__