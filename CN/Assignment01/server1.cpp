#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h> // functions for internet operations like IP address conversion
#include <unistd.h> // POSIX API, close() and read()
#include <algorithm> // needed forreverse()
using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Port number not provided !!" << endl;
        cout << "Use: " << argv[0] << " <Port>" << endl;
        return 1;
    }

    int port = atoi(argv[1]);
    
    // Variables for the server socket and the new connection socket
    int server_fd, new_socket;
    
    // Structure to hold the server's address info
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address); // Size of the address structure

    // Create a socket. 
    // AF_INET = IPv4 (IP Addresses), SOCK_STREAM = TCP (Reliable Connection)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cout << "Socket failed" << endl;
        return 1;
    }
    
    memset(&address, 0, sizeof(address));
    
    address.sin_family = AF_INET; // Use IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP on this machine
    address.sin_port = htons(port); // Convert port number to network format

    // Bind the socket to the port and IP address we just set up
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        cout << "Bind failed" << endl;
        return 1;
    }

    // Tell the socket to listen for incoming connections. 
    // 3 is the backlog queue size (how many people can wait in line)
    if (listen(server_fd, 3) < 0) {
        cout << "Listen failed" << endl;
        return 1;
    }

    // Infinite loop (while true) so the server stays running forever
    cout << "Server is listening on port " << port << endl;
    while (true) {
        // Accept a new client connection. This blocks (waits) until a client connects.
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            cout << "Accept failed" << endl;
            return 1;
        }

        cout << "Connected with client socket number " << new_socket << endl;

        char buffer[1024] = {0}; // Buffer (storage) for reading messages
        
        // Loop to talk with this specific client until they disconnect
        while (true) {
            memset(buffer, 0, sizeof(buffer)); // Clear the buffer before reading
            
            // Read data from the client into the buffer
            int valread = read(new_socket, buffer, 1024);
            if (valread <= 0) {
                // valread is 0 if client disconnects voluntarily, or negative if an error occurs
                break; // Exit the inner loop to stop talking to this client
            }
            
            // Convert the C-string buffer into a C++ string for easy reversing
            string msg(buffer);
            cout << "Client socket " << new_socket << " sent message: " << msg << endl;
            
            // reverse() flips the string backwards (e.g., "abcd" becomes "dcba")
            reverse(msg.begin(), msg.end());
            
            cout << "Sending reply: " << msg << endl;
            
            // send() sends the reversed message back to the client
            send(new_socket, msg.c_str(), msg.length(), 0);
        }
        
        // Close the connection with this client when they are done
        close(new_socket);
        
        // After closing, the program loops back up to accept() to wait for the NEXT client.
    }

    return 0; // End of program
}
