#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Format: ./server2 <Port>" << endl;
    return 1;
  }

  signal(SIGCHLD, SIG_IGN);

  int port = atoi(argv[1]);
  int server_fd;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    cout << "Socket failed" << endl;
    return 1;
  }

  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);

  memset(&address, 0, sizeof(address));
  
  address.sin_family = AF_INET;         // IPv4
  address.sin_addr.s_addr = INADDR_ANY; // Accept conn from any IP
  address.sin_port = htons(port);       // Convert port to network format

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    cout << "Bind failed" << endl;
    return 1;
  }

  if (listen(server_fd, 10) < 0) {
    cout << "Listen failed" << endl;
    return 1;
  }

  cout << "Server is listening on port " << port << endl;
  int new_socket;
  while (true) {
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0) {
      cout << "Accept failed" << endl;
      continue;
    }

    cout << "Connected with client socket number " << new_socket << endl;
    cout << "Client Port " << ntohs(address.sin_port) << endl;

    pid_t pid = fork();

    if (pid < 0) {
      cout << "Fork failed" << endl;
      close(new_socket);
    } else if (pid == 0) {
      // Child Process
      close(server_fd);
      char buffer[1024] = {0};

      while (true) {
        memset(buffer, 0, sizeof(buffer));

        int valread = read(new_socket, buffer, 1024);
        if (valread <= 0) {
          break;
        }
        string msg(buffer);
        cout << "Client socket " << new_socket << " sent message: " << msg << endl;

        reverse(msg.begin(), msg.end());
        cout << "Sending reply: " << msg << endl;

        send(new_socket, msg.c_str(), msg.length(), 0);
      }

      close(new_socket);

      exit(0);
    } else {
      // Parent Process
      close(new_socket);
    }
  }

  return 0;
}
