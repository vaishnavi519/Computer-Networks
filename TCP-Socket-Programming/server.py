import socket

# Server configuration
HOST = "127.0.0.1"
PORT = 5000

# Create TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind socket to IP address and port
server_socket.bind((HOST, PORT))

# Listen for incoming connections
server_socket.listen(1)

print("TCP Chat Server Started")
print(f"Listening on {HOST}:{PORT}...")
print("Waiting for client connection...\n")

# Accept client connection
client_socket, client_address = server_socket.accept()

print(f"Connected to client: {client_address}")
print("Type 'exit' to close the chat.\n")

# Chat communication
while True:
    # Receive message from client
    message = client_socket.recv(1024).decode()

    if not message:
        print("Client disconnected.")
        break

    print(f"Client: {message}")

    if message.lower() == "exit":
        print("Client ended the chat.")
        break

    # Send reply to client
    reply = input("Server: ")
    client_socket.send(reply.encode())

    if reply.lower() == "exit":
        print("Server ended the chat.")
        break

# Close connections
client_socket.close()
server_socket.close()

print("\nServer closed successfully.")
