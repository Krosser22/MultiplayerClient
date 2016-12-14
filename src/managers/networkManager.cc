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
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include "managers/gameManager.h"
#include "managers/networkManager.h"

//#pragma comment(lib, "sfml-network.lib")

#define IP "127.0.0.1"
static const unsigned short TCPPort = 8080;
static const unsigned short UDPPort = 2055;
static const int kMaxLength = 1024;

static struct ServerData {
  unsigned short UDPLocalPort = 0;

  sf::IpAddress ip;
  sf::TcpSocket tcpSocket;
  sf::UdpSocket udpSocket;

  bool conected = false;
  std::string SPK = "";

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

int padding = 1;

RSA *createRSA(unsigned char *key, bool isPublic)
{
  RSA *rsa = nullptr;
  BIO *keybio;
  keybio = BIO_new_mem_buf(key, -1);
  if (keybio == nullptr) {
    printf("Failed to create key BIO");
    return 0;
  }
  if (isPublic) rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, nullptr, nullptr);
  else rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, nullptr, nullptr);

  if (rsa == nullptr) {
    printf("Failed to create RSA");
  }

  return rsa;
}

int public_encrypt(unsigned char *data, int data_len, unsigned char *key, unsigned char *encrypted) {
  RSA *rsa = createRSA(key, true);
  int result = RSA_public_encrypt(data_len, data, encrypted, rsa, padding);
  return result;
}

int private_decrypt(unsigned char *enc_data, int data_len, unsigned char *key, unsigned char *decrypted) {
  RSA *rsa = createRSA(key, false);
  int result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
  return result;
}

int private_encrypt(unsigned char *data, int data_len, unsigned char *key, unsigned char *encrypted) {
  RSA *rsa = createRSA(key, false);
  int result = RSA_private_encrypt(data_len, data, encrypted, rsa, padding);
  return result;
}

int public_decrypt(unsigned char *enc_data, int data_len, unsigned char *key, unsigned char *decrypted) {
  RSA *rsa = createRSA(key, true);
  int result = RSA_public_decrypt(data_len, enc_data, decrypted, rsa, padding);
  return result;
}

void main2() {
  char plainText[2048 / 8] = "Hello this is Ravi"; //key length : 2048

  char publicKey[] = "-----BEGIN PUBLIC KEY-----\n"\
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAy8Dbv8prpJ/0kKhlGeJY\n"\
    "ozo2t60EG8L0561g13R29LvMR5hyvGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+\n"\
    "vw1HocOAZtWK0z3r26uA8kQYOKX9Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQAp\n"\
    "fc9jB9nTzphOgM4JiEYvlV8FLhg9yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68\n"\
    "i6T4nNq7NWC+UNVjQHxNQMQMzU6lWCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoV\n"\
    "PpY72+eVthKzpMeyHkBn7ciumk5qgLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUy\n"\
    "wQIDAQAB\n"\
    "-----END PUBLIC KEY-----\n";

  char privateKey[] = "-----BEGIN RSA PRIVATE KEY-----\n"\
    "MIIEowIBAAKCAQEAy8Dbv8prpJ/0kKhlGeJYozo2t60EG8L0561g13R29LvMR5hy\n"\
    "vGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+vw1HocOAZtWK0z3r26uA8kQYOKX9\n"\
    "Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQApfc9jB9nTzphOgM4JiEYvlV8FLhg9\n"\
    "yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68i6T4nNq7NWC+UNVjQHxNQMQMzU6l\n"\
    "WCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoVPpY72+eVthKzpMeyHkBn7ciumk5q\n"\
    "gLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUywQIDAQABAoIBADhg1u1Mv1hAAlX8\n"\
    "omz1Gn2f4AAW2aos2cM5UDCNw1SYmj+9SRIkaxjRsE/C4o9sw1oxrg1/z6kajV0e\n"\
    "N/t008FdlVKHXAIYWF93JMoVvIpMmT8jft6AN/y3NMpivgt2inmmEJZYNioFJKZG\n"\
    "X+/vKYvsVISZm2fw8NfnKvAQK55yu+GRWBZGOeS9K+LbYvOwcrjKhHz66m4bedKd\n"\
    "gVAix6NE5iwmjNXktSQlJMCjbtdNXg/xo1/G4kG2p/MO1HLcKfe1N5FgBiXj3Qjl\n"\
    "vgvjJZkh1as2KTgaPOBqZaP03738VnYg23ISyvfT/teArVGtxrmFP7939EvJFKpF\n"\
    "1wTxuDkCgYEA7t0DR37zt+dEJy+5vm7zSmN97VenwQJFWMiulkHGa0yU3lLasxxu\n"\
    "m0oUtndIjenIvSx6t3Y+agK2F3EPbb0AZ5wZ1p1IXs4vktgeQwSSBdqcM8LZFDvZ\n"\
    "uPboQnJoRdIkd62XnP5ekIEIBAfOp8v2wFpSfE7nNH2u4CpAXNSF9HsCgYEA2l8D\n"\
    "JrDE5m9Kkn+J4l+AdGfeBL1igPF3DnuPoV67BpgiaAgI4h25UJzXiDKKoa706S0D\n"\
    "4XB74zOLX11MaGPMIdhlG+SgeQfNoC5lE4ZWXNyESJH1SVgRGT9nBC2vtL6bxCVV\n"\
    "WBkTeC5D6c/QXcai6yw6OYyNNdp0uznKURe1xvMCgYBVYYcEjWqMuAvyferFGV+5\n"\
    "nWqr5gM+yJMFM2bEqupD/HHSLoeiMm2O8KIKvwSeRYzNohKTdZ7FwgZYxr8fGMoG\n"\
    "PxQ1VK9DxCvZL4tRpVaU5Rmknud9hg9DQG6xIbgIDR+f79sb8QjYWmcFGc1SyWOA\n"\
    "SkjlykZ2yt4xnqi3BfiD9QKBgGqLgRYXmXp1QoVIBRaWUi55nzHg1XbkWZqPXvz1\n"\
    "I3uMLv1jLjJlHk3euKqTPmC05HoApKwSHeA0/gOBmg404xyAYJTDcCidTg6hlF96\n"\
    "ZBja3xApZuxqM62F6dV4FQqzFX0WWhWp5n301N33r0qR6FumMKJzmVJ1TA8tmzEF\n"\
    "yINRAoGBAJqioYs8rK6eXzA8ywYLjqTLu/yQSLBn/4ta36K8DyCoLNlNxSuox+A5\n"\
    "w6z2vEfRVQDq4Hm4vBzjdi3QfYLNkTiTqLcvgWZ+eX44ogXtdTDO7c+GeMKWz4XX\n"\
    "uJSUVL5+CVjKLjZEJ6Qc2WZLl94xSwL71E41H4YciVnSCQxVc4Jw\n"\
    "-----END RSA PRIVATE KEY-----\n";

  unsigned char encrypted[4098] = {};
  unsigned char decrypted[4098] = {};

  printf("\n\n");

  //Client get the SPK
  //Client encrypt with the SPK
  printf("Public Encrypting...\n");
  int encrypted_length = public_encrypt((unsigned char *)plainText, strlen(plainText), (unsigned char *)publicKey, encrypted);
  if (encrypted_length == -1) {
    printf("Public Encrypt failed\n");
  }
  //printf("Decrypted Text =%s\n", encrypted);
  printf("Encrypted length =%d\n", encrypted_length);


  printf("Private Decrypting...\n");
  int decrypted_length = private_decrypt(encrypted, encrypted_length, (unsigned char *)privateKey, decrypted);
  if (decrypted_length == -1) {
    printf("Private Decrypt failed\n");
  }
  printf("Decrypted Text =%s\n", decrypted);
  printf("Decrypted Length =%d\n", decrypted_length);

  printf("Private Encrypting...\n");
  encrypted_length = private_encrypt((unsigned char *)plainText, strlen(plainText), (unsigned char *)privateKey, encrypted);
  if (encrypted_length == -1) {
    printf("Private Encrypt failed\n");
  }
  //printf("Decrypted Text =%s\n", encrypted);
  printf("Encrypted length =%d\n", encrypted_length);

  printf("Private Decrypting\n");
  decrypted_length = public_decrypt(encrypted, encrypted_length, (unsigned char *)publicKey, decrypted);
  if (decrypted_length == -1) {
    printf("Public Decrypt failed\n");
  }
  printf("Decrypted Text =%s\n", decrypted);
  printf("Decrypted Length =%d\n", decrypted_length);
}

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

void getSPK(std::string *msg) {
  data.SPK = "-----BEGIN PUBLIC KEY-----\n";

  std::string SPK = msg->substr(msg->find("<RSAKeyValue><Modulus>") + 1);
  SPK = SPK.substr(0, SPK.find("</Modulus>"));

  data.SPK += SPK + "\n";
  data.SPK += "-----END PUBLIC KEY-----\n";
  printf("[SSL protection ON]\n");
}

void decryptMsg(std::string *msg, std::string *decryptedMsg) {
  //TODO - this function must use the ServerPublicKey to decrypt the incoming msg
  *decryptedMsg = *msg;
}

bool connect() {
  data.ip = IP;
  return (data.tcpSocket.connect(data.ip, TCPPort) == sf::Socket::Done);
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
  if (content->size() > 0) {
    std::string decryptedMsg = "";

    //If the Server Public Key is empty the msg must be it
    if (data.SPK == "") {
      //Get the public key from the server
      getSPK(content);
    } else {
      //Decrypt the msg from the server
      decryptMsg(content, &decryptedMsg);

      //Get the commands from the msg
      std::vector<std::string> commands = split(decryptedMsg, '\n');

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
            Actor *enemy = new Actor();
            enemy->setID(&command.at(1));
            enemy->setTexture("enemy.png");
            enemy->setPosition(100, 100);
            data.sceneData->enemies.push_back(enemy);
            GameManager::AddObject(enemy);
          }
        }
      }
    }
  }
}

void processUDPMsg(std::string *content) {
  static std::string::size_type sz; //Alias of size_t
  std::vector<std::string> elements = split(*content, ':');

  std::string command = elements.at(0);
  std::string ID = elements.at(1);

  if (elements.size() > 0) {
    if (command == "Info") {
      Actor *actor = data.sceneData->getEnemy(&ID);
      float x = std::stof(elements.at(2), &sz);
      float y = std::stof(elements.at(3), &sz);
      if (actor) actor->setPosition(x, y);
    } else if (command == "Shoot") {
      std::string pickupID = elements.at(2);
      Actor *actor = data.sceneData->getActor(&ID);
      if (actor) actor->getPickup(pickup);
    }
  }
}

void getUDPMsgFromServer() {
  std::string UDPContent = "";
  char content[kMaxLength];
  unsigned short port = data.UDPLocalPort;
  std::size_t received = 0;
  for (unsigned int i = 0; i < kMaxLength; ++i) content[i] = '\0';

  while (data.udpSocket.receive(content, kMaxLength, received, data.ip, port) == sf::Socket::Done) {
    UDPContent = content;
    if (UDPContent.size() > 0) {
      //printf("[ServerUDP]: %s\n", UDPContent.c_str());
      processUDPMsg(&UDPContent);
    }
  }
}

void NetworkManager::SetSceneData(SceneData *sceneData) {
  data.sceneData = sceneData;
  data.sceneData->completed = false;
  data.sceneData->playing = false;
}

void NetworkManager::Start() {
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
    printf("UPD Socket binded to the port: %d\n", data.UDPLocalPort);
  }

  //OpenSSL
  SSL_load_error_strings();
  ERR_load_BIO_strings();
  OpenSSL_add_all_algorithms();
  //main2();
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
  getUDPMsgFromServer();

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
  data.udpSocket.send(packetSend, IP, UDPPort);
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