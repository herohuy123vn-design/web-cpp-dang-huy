#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

class WebServer {
private:
    int server_fd;
    int port;
    
public:
    WebServer() : port(std::atoi(std::getenv("PORT") ? std::getenv("PORT") : "8080")), server_fd(-1) {}
    
    ~WebServer() {
        if (server_fd != -1) {
            close(server_fd);
        }
    }
    
    bool start() {
        // Tạo socket
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            std::cerr << "Không thể tạo socket" << std::endl;
            return false;
        }
        
        // Cấu hình socket
        int opt = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
            std::cerr << "Lỗi setsockopt" << std::endl;
            return false;
        }
        
        // Bind socket
        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            std::cerr << "Bind failed trên cổng " << port << std::endl;
            return false;
        }
        
        // Listen
        if (listen(server_fd, 10) < 0) {
            std::cerr << "Listen failed" << std::endl;
            return false;
        }
        
        std::cout << "Server đang chạy trên cổng " << port << std::endl;
        return true;
    }
    
    void handleRequests() {
        while (true) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
            
            if (client_socket < 0) {
                std::cerr << "Chấp nhận kết nối thất bại" << std::endl;
                continue;
            }
            
            // Đọc request
            char buffer[1024] = {0};
            read(client_socket, buffer, 1024);
            
            std::string request(buffer);
            std::string response;
            
            // Xử lý request
            if (request.find("GET / ") != std::string::npos || 
                request.find("GET /index.html") != std::string::npos) {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + generateHTML();
            } else {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + generateHTML();
            }
            
            // Gửi response
            send(client_socket, response.c_str(), response.length(), 0);
            close(client_socket);
        }
    }
    
    std::string generateHTML() {
        // Giữ nguyên nội dung HTML như trước
        return R"(<!DOCTYPE html><html>...</html>)";
    }
};

int main() {
    WebServer server;
    
    if (!server.start()) {
        std::cerr << "Không thể khởi động server" << std::endl;
        return 1;
    }
    
    std::cout << "Web server đang chạy" << std::endl;
    server.handleRequests();
    
    return 0;
}