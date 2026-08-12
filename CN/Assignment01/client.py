import socket
import sys

# Read IP address from command line
HOST = sys.argv[1]

# Read port number from command line
PORT = int(sys.argv[2])

# Create TCP socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client.connect((HOST, PORT))

print("Connected to server")

try:

    while True:

        # Take input from user
        message = input("Enter message: ")

        # Send to server
        client.send(message.encode())

        # Receive reply
        reply = client.recv(1024)

        # Convert bytes to string
        print("Server reply:", reply.decode())

except KeyboardInterrupt:

    print("\nClosing connection...")

    # Close socket
    client.close()