#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    const char* server_reply = "Message received by the server.";
    const char* client_message = "Hello from the client";

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Server: Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Server: Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket to localhost port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Server: Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Server: Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept connection from client
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Server: Accept failed");
        exit(EXIT_FAILURE);
    }

    // Server receives message from client
    valread = read(new_socket, buffer, 1024);
    std::cout << "Client: " << buffer << std::endl;

    // Server replies to client
    send(new_socket, server_reply, strlen(server_reply), 0);
    std::cout << "Server: Reply message sent" << std::endl;

    // Client part
    int client_fd;
    struct sockaddr_in serv_addr;

    // Create client socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Client: Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Client: Invalid address/ Address not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Client: Connection failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Client sends message to server
    send(client_fd, client_message, strlen(client_message), 0);
    std::cout << "Client: Message sent to server" << std::endl;

    // Client receives reply from server
    valread = read(client_fd, buffer, 1024);
    std::cout << "Server: " << buffer << std::endl;

    return 0;
}