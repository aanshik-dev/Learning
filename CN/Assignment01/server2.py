import socket
from multiprocessing import Process

HOST = "0.0.0.0"
PORT = 5555


# Function to handle one client
def handle_client(client, address):

    print("Connected:", address)

    while True:

        # Receive data
        data = client.recv(1024)

        # Exit if client disconnects
        if not data:
            break

        # Convert bytes to string
        message = data.decode()

        print("Client:", message)

        # Reverse the string
        reply = message[::-1]

        print("Sending:", reply)

        # Send reply
        client.send(reply.encode())

    # Close client socket
    client.close()

    print("Disconnected:", address)


# Create TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind socket
server.bind((HOST, PORT))

# Listen for clients
server.listen(5)

print(f"Server started on port {PORT}")

while True:

    # Accept new client
    client, address = server.accept()

    # Create a new process for every client
    process = Process(target=handle_client, args=(client, address))

    # Start the new process
    process.start()

    # Parent process closes its copy
    client.close()