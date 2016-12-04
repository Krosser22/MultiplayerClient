/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "server.h"

//#pragma comment(lib, "sfml-network.lib")

#include <stdio.h>
#include <SFML/Network.hpp>

static struct ServerData {
  sf::TcpSocket tcpSocket;
  std::string content;
  //sf::Thread* thread;
  std::string tokenID;
} data;

/*void update() {
  sf::Packet packetReceive;
  std::string msg;
  while (true) {
    //Receive a packet
    packetReceive.clear();
    data.socket.receive(packetReceive);
    packetReceive >> msg;
    if (!msg.empty()) {
      printf("%s\n", msg.c_str());

      //sf::Packet packetSend;
      //data.globalMutex.lock();
      //packetSend << msg;
      //data.globalMutex.unlock();
      //data.socket.send(packetSend);
    }
  }
}

void Server::Start() {
  sf::TcpListener listener;
  listener.listen(SERVER_PORT);
  listener.accept(data.socket);
  printf("New client connected : %s\n", data.socket.getRemoteAddress().toString().c_str());
  data.thread = new sf::Thread(&update);
  data.thread->launch();
}

void Server::Finish() {
  if (data.thread) {
    data.thread->wait();
    delete data.thread;
  }
}*/

bool connect() {
  sf::IpAddress ip("127.0.0.1");
  unsigned short port = 8080;
  return (data.tcpSocket.connect(ip, port) == sf::Socket::Done);
}

void disconnect() {
  data.tcpSocket.disconnect();
}

void sendTCPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //packetSend.endOfPacket();
  //printf("%s\n", packetSend.getData());
  if (data.tcpSocket.send(packetSend) != sf::Socket::Done) {
    printf("Error sending data\n");
  }
}

void getTCPMsgFromServer() {
  static const int maxContentLength = 1024;
  char content[maxContentLength];
  for (unsigned int i = 0; i < maxContentLength; ++i) content[i] = '\0';
  std::size_t received = 0;
  if (data.tcpSocket.receive(content, maxContentLength, received) != sf::Socket::Done) {
    printf("Error receiving data\n");
  }
  //printf("Received %d bytes\n", received);
  printf("[Server]: %s\n", content);
  data.content = content;
}

void TCPConnection() {
  //Connect
  if (connect()) {
    //Send msg
    sendTCPMsgToServer(data.content.c_str());

    //Receive response
    getTCPMsgFromServer();

    //Disconnect
    disconnect();
  } else {
    printf("ERROR: Server Off\n");
    data.content = "ERROR";
  }
}

void Server::SendUDPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  //packetSend.clear();
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //printf("%s\n", packetSend.getData());
  data.tcpSocket.send(packetSend);
}

bool Server::Login(const char *user, const char *password) {
  //Msg to send
  std::string msg = "Login:";
  msg.append(user).append(":").append(password).append("\0");
  data.content = msg;

  //Receive a response from the server
  TCPConnection();

  if (data.content == "ERROR") {
    data.tokenID = "";
    return false;
  } else {
    data.tokenID = data.content;
    return true;
  }
}