#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>
#include <signal.h>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage: ./server2 <Port>" << endl;
        return 1; 
    }

    // Cleanup zombie processes
    signal(SIGCHLD, SIG_IGN); 

    int port = atoi(argv[1]);
    
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address); 

    // Create the server socket (IPv4, TCP Connection)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cout << "Socket failed" << endl;
        return 1;
    }
    
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(port); // Convert port to network format

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        cout << "Bind failed" << endl;
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        cout << "Listen failed" << endl;
        return 1;
    }

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            cout << "Accept failed" << endl;
            continue;
        }

        cout << "Connected with client socket number " << new_socket << endl;

        pid_t pid = fork();
        
        if (pid < 0) {
            cout << "Fork failed" << endl;
            close(new_socket);
        } 
        else if (pid == 0) {
            
            // The child only handles this ONE specific client.
            // It doesn't need to listen for new clients, so we close the server listener here.
            close(server_fd); 
            char buffer[1024] = {0};
            
            // Loop to continuously chat with this client
            while (true) {
                memset(buffer, 0, sizeof(buffer)); // Clear the buffer
                
                // Read a message from the client
                int valread = read(new_socket, buffer, 1024);
                if (valread <= 0) { 
                    break; // If read is 0 or less, client disconnected. Break the loop.
                }
                
                // Make a C++ string from the received text
                string msg(buffer);
                cout << "Client socket " << new_socket << " sent message: " << msg << endl;
                
                // Reverse the text (e.g. "cat" becomes "tac")
                reverse(msg.begin(), msg.end());
                
                cout << "Sending reply: " << msg << endl;
                
                // Send the reversed text back to the client
                send(new_socket, msg.c_str(), msg.length(), 0);
            }
            
            // We finished chatting with this client. Close the connection.
            close(new_socket);
            
            // The child's job is done, so we completely exit this cloned process.
            exit(0); 
        } 
        else {
            // --- WE ARE INSIDE THE PARENT PROCESS! ---
            
            // The parent doesn't chat with the client; the child is busy doing that.
            // So the parent closes its copy of the client's socket.
            close(new_socket); 
            
            // The parent loops back around to accept() to wait for the NEXT client.
        }
    }

    return 0; // End of program
}
