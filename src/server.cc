/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "server.h"

#pragma comment(lib, "sfml-network.lib")

#include <stdio.h>
#include <SFML/Network.hpp>

static const sf::IpAddress ip("127.0.0.1");
#define SERVER_PORT 8080

struct ServerData {
  sf::TcpSocket tcpSocket;
  //sf::Thread* thread;
} serverData;

/*void update() {
  sf::Packet packetReceive;
  std::string msg;
  while (true) {
    //Receive a packet
    packetReceive.clear();
    serverData.socket.receive(packetReceive);
    packetReceive >> msg;
    if (!msg.empty()) {
      printf("%s\n", msg.c_str());

      //sf::Packet packetSend;
      //serverData.globalMutex.lock();
      //packetSend << msg;
      //serverData.globalMutex.unlock();
      //serverData.socket.send(packetSend);
    }
  }
}

void Server::Start() {
  sf::TcpListener listener;
  listener.listen(SERVER_PORT);
  listener.accept(serverData.socket);
  printf("New client connected : %s\n", serverData.socket.getRemoteAddress().toString().c_str());
  serverData.thread = new sf::Thread(&update);
  serverData.thread->launch();
}

void Server::Finish() {
  if (serverData.thread) {
    serverData.thread->wait();
    delete serverData.thread;
  }
}*/

void Server::SendTCPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  packetSend.clear();
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //printf("%s\n", packetSend.getData());
  serverData.tcpSocket.send(packetSend);
}

void Server::SendUDPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  packetSend.clear();
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //printf("%s\n", packetSend.getData());
  serverData.tcpSocket.send(packetSend);
}

void Server::StartClient() {
  if (serverData.tcpSocket.connect(ip, SERVER_PORT) == sf::Socket::Done) {
    printf("Connected\n");
  } else {
    printf("No Connected\n");
  }
}

void Server::FinishClient() {
  serverData.tcpSocket.disconnect();
}

void Server::Login(const char *user, const char *password) {
  std::string msg = "Login:";
  msg.append(user);
  msg.append(":");
  msg.append(password);
  SendTCPMsgToServer(msg.c_str());
}