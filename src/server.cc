/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "server.h"

void Server::start() {
  WSADATA wsa;
  memset(msg, 0, max_line);
  WSAStartup(MAKEWORD(2, 0), &wsa);
  sock_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ip_s.sin_family = AF_INET;
  //ip_s.sin_addr.s_addr = inet_addr("0.0.0.0"); // Ponemos esa ip para que sea cualquiera de las que tenemos
  InetPton(AF_INET, "0.0.0.0", &ip_s);
  ip_s.sin_port = htons(puerto);
  bind(sock_s, (SOCKADDR*)&ip_s, sizeof(ip_s));
  listen(sock_s, SOMAXCONN);
  size = sizeof(ip_s);
}

void Server::update() {
  sock_c = accept(sock_s, (SOCKADDR*)&ip_c, &size);
  if (sock_c != INVALID_SOCKET) {
    readWeb();
  }
  closesocket(sock_c);
}

void Server::finish() {
  closesocket(sock_s);
  WSACleanup();
  system("pause");
}

void Server::sendError() {
  memset(msg, 0, max_line);
  strcpy(msg, "HTTP / 1.1 404 Not Found\nKeep - Alive : timeout = 5, max = 100\nConnection : Keep - Alive\nContent - Type : text / html;\n");
  if (send(sock_c, msg, sizeof(msg), 0) == SOCKET_ERROR) {
    printf("Error de envio\n");
    //wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
  }
  memset(msg, 0, max_line);
}

void Server::readWeb() {
  memset(msg, '\0', max_line);
  if (recv(sock_c, msg, sizeof(msg), 0) > 0) {
    //printf("\n\n\nRECEIVING\n[%s]\n\n", msg);
    //printf("Processing the message from [%s]\n", inet_ntoa(ip_c.sin_addr));
    char *c_get = strtok(msg, " ");
    char *c_path = strtok(NULL, " ");
    strtok(NULL, "\n");
    strtok(NULL, " ");
    char *c_domain = strtok(NULL, ":");

    if (c_path != NULL) {
      printf("REQUEST: [%s:%d%s]\n", c_domain, puerto, c_path);
      char new_path[max_line];

      if (strcmp(c_domain, "127.0.0.1") == 0) {
        strcpy(c_domain, "localhost");
        strcpy(new_path, "webs/localhost");
      } else {
        strcpy(new_path, "webs/www.google.com");
      }

      if (strcmp(c_path, "/") == 0) {
        strcat(new_path, "/index.html");
      } else {
        strcat(new_path, c_path);
      }

      char header[max_line];
      memset(header, '\0', max_line);
      strcpy(header, "HTTP/1.1 200 OK\nContent-Type: ");
      char *type_extension = strtok(c_path, ".");
      type_extension = strtok(NULL, "");
      if (type_extension == NULL) {
        type_extension = "text/html";
      } else if (strcmp(type_extension, "htm") == 0 || strcmp(type_extension, "html") == 0) {
        strcpy(type_extension, "text/html");
      } else if (strcmp(type_extension, "jpg") == 0 || strcmp(type_extension, "jpeg") == 0 || strcmp(type_extension, "gif") == 0 || strcmp(type_extension, "png") == 0) {
        strcpy(type_extension, "image/*");
      } else if (strcmp(type_extension, "css") == 0) {
        strcpy(type_extension, "text/css");
      } else if (strcmp(type_extension, "js") == 0) {
        strcpy(type_extension, "application/javascript");
      }
      strcat(header, type_extension);
      strcat(header, "\naccept - ranges: bytes\nContent - Lenght: ");
      char c_length[8];

      FILE *file = fopen(new_path, "rb");
      if (file == NULL && strcmp(type_extension, "text/html") != 0) {
        printf("NOT FOUND FILE: [%s:%d/%s]\n", c_domain, puerto, new_path);
        sendError();
      } else if (file == NULL && strcmp(type_extension, "text/html") == 0) {
        printf("NOT FOUND PAGE: [%s:%d/%s]\n", c_domain, puerto, new_path);
        char path_404[max_line] = "webs/";
        strcat(path_404, c_domain);
        strcat(path_404, "/404/404.htm");
        file = fopen(path_404, "rb");
        if (file == NULL) {
          sendError();
        } else {
          strcpy(new_path, path_404);
        }
      }

      if (file != NULL) {
        printf("SENDING: [%s:%d/%s]\n\n", c_domain, puerto, new_path);

        fseek(file, 0L, SEEK_END);
        unsigned int file_length = ftell(file);
        _itoa_s(file_length, c_length, sizeof(c_length), 10);
        strcat(header, c_length);
        strcat(header, "\nConnection: Keep - Alive\n\n");

        unsigned int header_length = strlen(header);
        unsigned int new_msg_length = file_length + header_length + 1;

        char *new_msg = new char[max_line];
        memset(new_msg, '\0', max_line);
        strcpy(new_msg, header);
        fseek(file, 0L, SEEK_SET);

        char *message = new char[file_length + header_length + 1];
        strcpy(message, header);
        for (unsigned int i = 0; i < file_length; i++) {
          message[i + header_length] = fgetc(file);
        }
        fclose(file);
        message[file_length + header_length] = '\0';
        //printf("%s\n", message);
        if (send(sock_c, message, file_length + header_length, 0) == SOCKET_ERROR) {
          printf("Error de envio\n");
          //wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        }
      }
    }
  }
}