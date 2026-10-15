import socket

# Server configuration
HOST = "127.0.0.1"
PORT = 5000

# Create TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client_socket.connect((HOST, PORT))

print("Connected to TCP Chat Server!")
print("Type 'exit' to close the chat.\n")

# Chat communication
while True:
    # Input message from user
    message = input("Client: ")

    # Send message to server
    client_socket.send(message.encode())

    if message.lower() == "exit":
        print("Chat ended.")
        break

    # Receive reply from server
    reply = client_socket.recv(1024).decode()

    if not reply:
        print("Server disconnected.")
        break

    print(f"Server: {reply}")

    if reply.lower() == "exit":
        print("Server ended the chat.")
        break

# Close client socket
client_socket.close()

print("Client socket closed.")
