#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

// g++ -std=c++17 -Wall -o multithreaded_udp multithreaded_udp.cpp -pthread

// compile:
// g++ -std=c++17 -Wall send_receieve-main.cpp -o send_receieve-main -pthread
// ./send_receieve-main
//

// ./send_receieve-main server

// ./send_receieve-main client


// --- Configuration ---
const int PORT = 50000;
const int BUFFER_SIZE = 1024;
const char* SERVER_HOST = "127.0.0.1";

// A thread-safe queue for sending messages
template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;

public:
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(value);
        cond_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]{ return !queue_.empty(); });
        T value = queue_.front();
        queue_.pop();
        return value;
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.empty();
    }
};

// --- Server Implementation ---
class Server {
private:
    int sock_fd;
    sockaddr_in server_addr;
    std::mutex clients_mutex;
    std::vector<sockaddr_in> clients;
    ThreadSafeQueue<std::string> send_queue;

public:
    Server(const char* host, int port) {
        // Create a UDP socket
        sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock_fd < 0) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        // Zero out the address structure and set family, address, and port
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        // Convert the string IP address to a network address
        if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            exit(EXIT_FAILURE);
        }

        // Bind the socket to the server address
        if (bind(sock_fd, (const sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        std::cout << "Server started on " << host << ":" << port << std::endl;
    }

    // Receiving thread for the server
    void receive_loop() {
        std::vector<char> buffer(BUFFER_SIZE);
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        while (true) {
            memset(&client_addr, 0, sizeof(client_addr));
            int n = recvfrom(sock_fd, buffer.data(), BUFFER_SIZE - 1, 0, (sockaddr *)&client_addr, &client_len);
            if (n < 0) {
                perror("recvfrom failed");
                continue;
            }

            buffer[n] = '\0'; // Null-terminate the received data
            std::string message(buffer.data());

            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
            int client_port = ntohs(client_addr.sin_port);

            std::cout << "Received from " << client_ip << ":" << client_port << ": " << message << std::endl;

            // Check if the client is new and add it to our list
            std::lock_guard<std::mutex> lock(clients_mutex);
            bool new_client = true;
            for (const auto& client : clients) {
                if (client.sin_addr.s_addr == client_addr.sin_addr.s_addr &&
                    client.sin_port == client_addr.sin_port) {
                    new_client = false;
                    break;
                }
            }
            if (new_client) {
                clients.push_back(client_addr);
                std::cout << "New client connected: " << client_ip << ":" << client_port << std::endl;
            }
        }
    }

    // Sending thread for the server
    void send_loop() {
        while (true) {
            std::string message = send_queue.pop(); // Blocks until a message is available
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (const auto& client_addr : clients) {
                sendto(sock_fd, message.c_str(), message.length(), 0, (const sockaddr *)&client_addr, sizeof(client_addr));
            }
        }
    }

    // Main thread loop for console input
    void console_input_loop() {
        std::string line;
        std::cout << "Server > ";
        while (std::getline(std::cin, line)) {
            send_queue.push("[Server]: " + line);
            std::cout << "Server > ";
        }
        std::cout << "Exiting console input loop." << std::endl;
    }

    void run() {
        // Start the receive and send threads
        std::thread recv_thread(&Server::receive_loop, this);
        std::thread send_thread(&Server::send_loop, this);

        // Run the main console input loop on the main thread
        console_input_loop();

        // Threads will run until the program is terminated
        recv_thread.join();
        send_thread.join();
    }
};

// --- Client Implementation ---
class Client {
private:
    int sock_fd;
    sockaddr_in server_addr;

public:
    Client(const char* host, int port) {
        // Create a UDP socket
        sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock_fd < 0) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        // Zero out the address structure and set family, address, and port
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        // Convert the string IP address to a network address
        if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            exit(EXIT_FAILURE);
        }

        std::cout << "Client started. Connecting to " << host << ":" << port << std::endl;
    }

    // Receiving thread for the client
    void receive_loop() {
        std::vector<char> buffer(BUFFER_SIZE);
        sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);

        while (true) {
            int n = recvfrom(sock_fd, buffer.data(), BUFFER_SIZE - 1, 0, (sockaddr *)&addr, &addr_len);
            if (n < 0) {
                perror("recvfrom failed");
                continue;
            }
            buffer[n] = '\0'; // Null-terminate the received data
            std::cout << "\n" << buffer.data() << "\n> " << std::flush;
        }
    }

    // Sending thread for the client
    void send_loop() {
        std::string line;
        std::cout << "> ";
        while (std::getline(std::cin, line)) {
            sendto(sock_fd, line.c_str(), line.length(), 0, (const sockaddr *)&server_addr, sizeof(server_addr));
            std::cout << "> ";
        }
        std::cout << "Exiting console input loop." << std::endl;
    }

    void run() {
        // Start the receive and send threads
        std::thread recv_thread(&Client::receive_loop, this);
        std::thread send_thread(&Client::send_loop, this);

        // Threads will run until the program is terminated
        recv_thread.join();
        send_thread.join();
    }
};

// --- Main script logic ---
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [server|client]" << std::endl;
        return 1;
    }

    std::string role = argv[1];

    if (role == "server") {
        Server server(SERVER_HOST, PORT);
        server.run();
    } else if (role == "client") {
        Client client(SERVER_HOST, PORT);
        client.run();
    } else {
        std::cerr << "Invalid role. Please specify 'server' or 'client'." << std::endl;
        return 1;
    }

    return 0;
}
