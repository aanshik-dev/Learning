#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Insufficient arguments !!" << endl;
    cout << "Format: ./client <IP> <Port>" << endl;
    return 1;
  }

  const char *server_ip = argv[1];
  int server_port = atoi(argv[2]);

  // AF_INET = IPv4. SOCK_STREAM = TCP. 0 = default protocol.
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    cout << "Socket creation error" << endl;
    return 1;
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(server_port);

  // converts text IP to binary & stores in serv_addr
  if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
    cout << "Invalid address" << endl;
    return 1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    cout << "Connection Failed" << endl;
    return 1;
  }

  cout << "Connected to server" << endl;

  char buffer[1024] = {0};
  string input;

  while (true) {
    cout << "Please enter the message to the server:\n";

    if (!getline(cin, input)) {
      break;
    }
    if (input.empty())
      continue;

    if (send(sock, input.c_str(), input.length(), 0) < 0) {
      cout << "Send failed" << endl;
      break;
    }

    memset(buffer, 0, sizeof(buffer));

    int valread = read(sock, buffer, 1024);
    if (valread <= 0) {
      cout << "Server disconnected" << endl;
      break;
    }
    cout << "Server reply: " << buffer << endl;
  }

  close(sock);
  return 0;
}
