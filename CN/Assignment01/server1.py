import socket

HOST = "0.0.0.0" #IP to listen from anywhere

PORT = 5555

# Create a TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind socket with IP and Port
server.bind((HOST, PORT))

# Start listening for incoming connections
# Only one client will be handled at a time
server.listen(1)

print(f"Server started on port {PORT}")

# Run forever
while True:

    # Wait until a client connects
    # client -> new socket for communication
    # address -> client's IP and port
    client, address = server.accept()

    print("Connected:", address)

    # Keep receiving messages from this client
    while True:

        # Receive maximum 1024 bytes
        data = client.recv(1024)

        # If client disconnects, exit loop
        if not data:
            break

        # Convert bytes into string
        message = data.decode()

        print("Client sent:", message)

        # Reverse the string using slicing
        reply = message[::-1]

        print("Sending reply:", reply)

        # Convert string back to bytes and send
        client.send(reply.encode())

    # Close client connection
    client.close()

    print("Client disconnected")