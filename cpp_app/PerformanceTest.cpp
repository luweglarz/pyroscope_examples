#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cmath>
#include <thread>

void crazy_for_loop(double sum){
        for (int i = 0; i < 100000; ++i) {
            sum += std::sqrt(i);
        }
}

void imABottleNeck(){
    auto startTime = std::chrono::steady_clock::now();

    while (true) {
        double sum = 0.0;
        crazy_for_loop(sum);
        
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        if (elapsedTime.count() >= 20) {
            break;
        }
    }
}

void processRequest(bool isBottleNeck){
    if (isBottleNeck == true){
        imABottleNeck();
    }
    else{
        double sum = 0.0;
        for (int i = 0; i < 1000; ++i) {
            sum += std::sqrt(i);
        }
    }
}

void handleRequest(int clientSocket) {
    const char* response_post =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "POST request";
    const char* response_get =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "GET request";

    const int bufferSize = 1024;
    char buffer[bufferSize];
    memset(buffer, 0, bufferSize);
    recv(clientSocket, buffer, bufferSize, 0);

    std::string request(buffer);
    if (request.find("POST") != std::string::npos) {
        processRequest(true);
    } else {
        processRequest(false);
    }

    close(clientSocket);
}

void startServer() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Failed to create socket\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Failed to bind\n";
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error: Failed to listen\n";
        close(serverSocket);
        return;
    }

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Error: Failed to accept connection\n";
            continue;
        }
        handleRequest(clientSocket);
    }

    close(serverSocket);
}

int main() {
    std::thread server(startServer);

    server.join();
    return 0;
}
