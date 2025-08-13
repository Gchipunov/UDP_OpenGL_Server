#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// compile:
// g++ server_one_client-main.cpp -o server_one_client-main  
//run:
// ./server_one_client-main

// test client:
// echo "Hello from client" | nc -6 -u ::1 54321

// Define the port the server will listen on
#define PORT 54321
// Define the size of the buffer for incoming messages
#define BUFFER_SIZE 1024

int main() {
    int server_sock_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in6 server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 1. Create a UDP IPv6 socket.
    // AF_INET6 for IPv6, SOCK_DGRAM for UDP, 0 for default protocol.
    if ((server_sock_fd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Prepare the server address structure.
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;        // Specify IPv6
    server_addr.sin6_port = htons(PORT);       // Port number in network byte order
    server_addr.sin6_addr = in6addr_any;       // Listen on all available IPv6 addresses

    // 3. Bind the socket to the specified address and port.
    if (bind(server_sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Socket binding failed");
        close(server_sock_fd);
        return 1;
    }

    std::cout << "UDP IPv6 server is listening on port " << PORT << "...\n";

    // 4. Main server loop: listen for incoming messages.
    while (true) {
        // Clear the client address structure and buffer for each new message.
        memset(&client_addr, 0, client_addr_len);
        memset(buffer, 0, BUFFER_SIZE);

        // Receive a datagram from a client.
        // The call will block until a message is received.
        int n = recvfrom(server_sock_fd, buffer, BUFFER_SIZE, 0, 
                         (struct sockaddr *)&client_addr, &client_addr_len);

        if (n < 0) {
            perror("recvfrom failed");
            continue; // Continue to the next iteration of the loop
        }
        
        // Null-terminate the received data to treat it as a C-style string.
        buffer[n] = '\0';
        
        // Convert the client's IPv6 address to a human-readable string.
        char client_ip_str[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip_str, INET6_ADDRSTRLEN);

        std::cout << "Received " << n << " bytes from "
                  << client_ip_str << ":" << ntohs(client_addr.sin6_port) << ": "
                  << buffer << "\n";
        
        // Prepare a response message to send back to the client.
        const char* response = "Server received your message!";
        
        // Send a response back to the client that just sent a message.
        sendto(server_sock_fd, response, strlen(response), 0, 
               (const struct sockaddr *)&client_addr, client_addr_len);
    }

    // 5. Close the socket (this part of the code is unreachable in the current loop).
    close(server_sock_fd);

    return 0;
}