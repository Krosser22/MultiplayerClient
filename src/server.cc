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

struct ServerData {
  sf::TcpSocket tcpSocket;
  std::string data;
  //sf::Thread* thread;
  std::string tokenID;
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

bool connect() {
  sf::IpAddress ip("127.0.0.1");
  unsigned short port = 8080;
  return (serverData.tcpSocket.connect(ip, port) == sf::Socket::Done);
}

void disconnect() {
  serverData.tcpSocket.disconnect();
}

void sendTCPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  packetSend.clear();
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //packetSend.endOfPacket();
  //printf("%s\n", packetSend.getData());
  if (serverData.tcpSocket.send(packetSend) != sf::Socket::Done) {
    printf("Error sending data\n");
  }
}

void getTCPMsgFromServer() {
  static const int maxDataLength = 1024;
  char data[maxDataLength];
  for (unsigned int i = 0; i < maxDataLength; ++i) data[i] = '\0';
  std::size_t received = 0;
  if (serverData.tcpSocket.receive(data, 100, received) != sf::Socket::Done) {
    printf("Error receiving data\n");
  }
  //printf("Received %d bytes\n", received);
  printf("[Server]: %s\n", data);
  serverData.data = data;
}

void TCPConnection() {
  //Connect
  if (connect()) {
    //Send msg
    sendTCPMsgToServer(serverData.data.c_str());

    //Receive response
    getTCPMsgFromServer();

    //Disconnect
    disconnect();
  } else {
    printf("ERROR: Server Off\n");
  }
}

void Server::SendUDPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  //packetSend.clear();
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //printf("%s\n", packetSend.getData());
  serverData.tcpSocket.send(packetSend);
}

bool Server::Login(const char *user, const char *password) {
  //Msg to send
  std::string msg = "Login:";
  msg.append(user).append(":").append(password).append("\0");
  serverData.data = msg;

  //Receive a response from the server
  TCPConnection();

  if (serverData.data == "ERROR") {
    serverData.tokenID = "";
    return false;
  } else {
    serverData.tokenID = serverData.data;
    return true;
  }
}