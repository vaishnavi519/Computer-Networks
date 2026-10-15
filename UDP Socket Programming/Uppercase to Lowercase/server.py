import socket

# Server configuration
HOST = "127.0.0.1"
PORT = 5001

# Create UDP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind socket to IP address and port
server_socket.bind((HOST, PORT))

print("UDP Lowercase Conversion Server Started")
print(f"Listening on {HOST}:{PORT}...")
print("Waiting for client message...\n")

# Receive message from client
data, client_address = server_socket.recvfrom(1024)

message = data.decode("utf-8")

print(f"Client Address: {client_address}")
print(f"Received Message: {message}")

# Convert uppercase to lowercase
result = message.lower()

print(f"Converted Message: {result}")

# Send result to client
server_socket.sendto(result.encode("utf-8"), client_address)

print("\nResponse sent successfully.")

# Close server socket
server_socket.close()

print("Server closed.")
