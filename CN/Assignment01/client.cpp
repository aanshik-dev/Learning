#include <iostream> 
#include <cstring> // C-style strings and memory (like memset)
#include <sys/socket.h> // functions needed for network sockets
#include <arpa/inet.h> // internet operations,converting IP
#include <unistd.h> // POSIX OS API, like close() and read()
using namespace std; 

int main(int argc, char *argv[]) {
    // Check if the user provided exactly 3 arguments (program name, IP, and Port)
    if (argc != 3) {
        cout << "Insufficient arguments !!" << endl;
        cout << "Usage: ./client <IP> <Port>" << endl;
        return 1;
    }

    const char* server_ip = argv[1];
    int server_port = atoi(argv[2]);

    // Create a socket. 
    // AF_INET means IPv4. SOCK_STREAM means TCP connection. 0 is the default protocol.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "Socket creation error" << endl;
        return 1;
    }

    struct sockaddr_in serv_addr;
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    // Set address family to IPv4
    serv_addr.sin_family = AF_INET;
    
    // htons converts the port number to network byte order (which computers use to communicate)
    serv_addr.sin_port = htons(server_port);

    // inet_pton converts the text IP address into binary format and stores it in serv_addr
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        cout << "Invalid address" << endl;
        return 1;
    }

    // connect() tries to establish a connection to the server using our socket and server details
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Connection Failed" << endl;
        return 1;
    }

    cout << "Connected to server" << endl;

    // Buffer is a temporary storage area to hold data sent and received
    char buffer[1024] = {0}; 
    string input;
    

    while (true) {
        cout << "Please enter the message to the server:\n";
        
        if (!getline(cin, input)) {
            break;
        }
        
        if (input.empty()) continue;

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
        
        // Print the reversed reply from the server
        cout << "Server reply: " << buffer << endl;
    }

    // close() closes the socket when we are done
    close(sock);
    return 0; // Program finished successfully (0 means success)
}
