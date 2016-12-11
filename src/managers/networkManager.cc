/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <stdio.h>
#include <deque>
#include <SFML/Network.hpp>
#include <sstream>
#include "managers/gameManager.h"
#include "managers/networkManager.h"

//#pragma comment(lib, "sfml-network.lib")

static const int kMaxLength = 1024;
#define IP "127.0.0.1"
std::string::size_type sz;   // alias of size_t

static struct ServerData {
  //SERVER
  sf::IpAddress ip;
  unsigned short TCPPort = 8080;
  unsigned short UDPPort = 2055;
  unsigned short UDPLocalPort = 0;
  bool conected = false;

  //TCP
  sf::TcpSocket tcpSocket;
  std::deque<std::string> msgTCPReceived;

  //UDP
  sf::UdpSocket udpSocket;
  std::deque<std::string> msgUDPReceived;

  //sf::Thread* thread;

  //Game
  SceneData *sceneData;
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

void NetworkManager::Start() {
  sf::TcpListener listener;
  listener.listen(SERVER_PORT);
  listener.accept(data.socket);
  printf("New client connected : %s\n", data.socket.getRemoteAddress().toString().c_str());
  data.thread = new sf::Thread(&update);
  data.thread->launch();
}

void NetworkManager::Finish() {
  if (data.thread) {
    data.thread->wait();
    delete data.thread;
  }
}*/

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

bool connect() {
  data.ip = IP;
  return (data.tcpSocket.connect(data.ip, data.TCPPort) == sf::Socket::Done);
}

void sendTCPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //printf("%s\n", msg);
  if (data.tcpSocket.send(packetSend) != sf::Socket::Done) {
    printf("Error sending data\n");
  }
}

std::string TCPContent;
std::string *getTCPMsgFromServer() {
  char content[kMaxLength];
  for (unsigned int i = 0; i < kMaxLength; ++i) content[i] = '\0';
  std::size_t received = 0;

  TCPContent = "";
  if (data.tcpSocket.receive(content, kMaxLength, received) == sf::Socket::Done) {
    TCPContent = content;
    if (TCPContent.size() > 0) {
      //printf("Received %d bytes\n", received);
      printf("[ServerTCP]: %s\n", TCPContent.c_str());
    }
  }
  return &TCPContent;
}

void processTCPMsg(std::string *content) {
  std::vector<std::string> commands = split(*content, '\n');

  for (unsigned int i = 0; i < commands.size(); ++i) {
    std::vector<std::string> command = split(commands.at(i), ':');

    if (command.size() > 0) {
      if (command.at(0) == "Login" && command.at(1) != "ERROR" && command.size() == 2) {
        data.sceneData->completed = true;
        data.sceneData->player.setID(&command.at(1));
      } else if (command.at(0) == "Create" && command.size() == 2) {
        data.sceneData->completed = (command.at(1) == "Done");
      } else if (command.at(0) == "Forgot" && command.size() == 2) {
        data.sceneData->completed = (command.at(1) == "Done");
      } else if (command.at(0) == "AddPlayer" && command.size() == 2) {
        Object *enemy = new Object();
        enemy->setID(&command.at(1));
        enemy->setTexture("enemy.png");
        enemy->setPosition(100, 100);
        data.sceneData->enemies.push_back(enemy);
        GameManager::AddObject(enemy);
      }
    }
  }
}

void processUDPMsg(std::string *content) {
  std::vector<std::string> elements = split(*content, ':');
  
  if (elements.size() > 0) {
    if (elements.at(0) == "Info") {
      if (elements.at(1) != data.sceneData->player.ID()) {
        for (unsigned int i = 0; i < data.sceneData->enemies.size(); ++i) {
          if (elements.at(1) == data.sceneData->enemies.at(i)->ID()) {
            float x = std::stof(elements.at(2), &sz);
            float y = std::stof(elements.at(3), &sz);
            data.sceneData->enemies.at(i)->setPosition(x, y);
          }
        }
      }
    }
  }
}

std::string UDPContent;
std::string *getUDPMsgFromServer() {
  char content[kMaxLength];
  sf::Packet packetReceived;
  unsigned short port = data.UDPLocalPort;
  for (unsigned int i = 0; i < kMaxLength; ++i) content[i] = '\0';
  std::size_t received = 0;

  UDPContent = "";
  port = data.UDPLocalPort;
  while (data.udpSocket.receive(content, kMaxLength, received, data.ip, port) == sf::Socket::Done) {
    UDPContent = content;
    if (UDPContent.size() > 0) {
      printf("[ServerUDP]: %s\n", UDPContent.c_str());
      processUDPMsg(&UDPContent);
    }
  }

  /*port = data.UDPLocalPort;
  if (data.udpSocket.receive(packetReceived, ip, port) == sf::Socket::Done) {
  if (packetReceived.getDataSize() > 0) {
  c = (char *)packetReceived.getData();
  printf("[Server2]: %s\n", c.c_str());
  }
  }*/

  return &UDPContent;
}

void NetworkManager::SetSceneData(SceneData *sceneData) {
  data.sceneData = sceneData;
  data.sceneData->completed = false;
  data.sceneData->playing = false;
}

void NetworkManager::Start() {
  static bool doOnce = false;
  if (!doOnce) {
    doOnce = true;

    data.ip = IP;

    //TCP
    data.conected = connect();
    data.tcpSocket.setBlocking(false);
    if (data.conected) {
      printf("Server ON\n");
    } else {
      printf("Server Off\n");
    }

    //UDP
    printf("Binding... ");
    data.udpSocket.setBlocking(false);
    if (data.udpSocket.bind(sf::Socket::AnyPort, data.ip) != sf::Socket::Done) {
      printf("ERROR: binding UDP port\n");
    } else {
      data.UDPLocalPort = data.udpSocket.getLocalPort();
      printf("UPD Socket bind to the port: %d\n", data.UDPLocalPort);
    }
  }
}

void NetworkManager::Finish() {
  //TCP
  data.tcpSocket.disconnect();

  //UDP
  data.udpSocket.unbind();
}

void NetworkManager::Update() {
  //Just in case something goes wrong on the server side
  if (!data.conected) {
    data.conected = connect();
    if (data.conected) {
      printf("Server ON\n");
    }
  }

  //Process new data
  processTCPMsg(getTCPMsgFromServer());
  processUDPMsg(getUDPMsgFromServer());

  //Update player
  static sf::Time startTime;
  static float timeToUpdate = 0.1f;
  if (data.sceneData->playing) {
    if (startTime.asSeconds() + timeToUpdate < GameManager::Time().asSeconds() || true) {
      startTime = GameManager::Time();
      Actor *player = &data.sceneData->player;
      std::string msg = "Info:";
      msg.append(player->ID()).append(":");
      msg.append(std::to_string(player->positionX())).append(":");
      msg.append(std::to_string(player->positionY()));
      SendUDPMsgToServer(msg.c_str());
    }
  }
}

void NetworkManager::SendUDPMsgToServer(const char *msg) {
  sf::Packet packetSend;
  packetSend.append(msg, strlen(msg));
  packetSend.append("\0", 1);
  //printf("Sending: %s\n", msg);
  data.udpSocket.send(packetSend, IP, data.UDPPort);
}

void NetworkManager::Login(const char *nick, const char *password) {
  std::string stringPassword = password;
  std::hash<std::string> hash;
  std::string msg = "Login:";
  msg.append(nick).append(":").append(std::to_string(hash(stringPassword))).append("\0");
  sendTCPMsgToServer(msg.c_str());
}

void NetworkManager::ForgotPassword(const char *email) {
  std::string msg = "Forgot:";
  msg.append(email).append("\0");
  sendTCPMsgToServer(msg.c_str());
}

void NetworkManager::CreateAccount(const char *email, const char *nick, const char *password) {
  std::string stringPassword = password;
  std::hash<std::string> hash;
  std::string msg = "Create:";
  msg.append(email).append(":").append(nick).append(":").append(std::to_string(hash(stringPassword))).append("\0");
  sendTCPMsgToServer(msg.c_str());
}