#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>

class WebServer {
private:
    int server_fd;
    int port;
    
    std::string readFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found";
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    
    std::string getContentType(const std::string& path) {
        if (path.find(".css") != std::string::npos) return "text/css";
        if (path.find(".js") != std::string::npos) return "application/javascript";
        if (path.find(".png") != std::string::npos) return "image/png";
        if (path.find(".jpg") != std::string::npos) return "image/jpeg";
        if (path.find(".ico") != std::string::npos) return "image/x-icon";
        return "text/html";
    }

public:
    WebServer(int port = 8080) : port(port), server_fd(-1) {}
    
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
            std::cerr << "Bind failed" << std::endl;
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
            } else if (request.find("GET /style.css") != std::string::npos) {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n" + generateCSS();
            } else {
                response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found";
            }
            
            // Gửi response
            send(client_socket, response.c_str(), response.length(), 0);
            close(client_socket);
        }
    }
    
    std::string generateHTML() {
        return R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Không Gian Mặt Trăng - Trình Bày Môn Văn</title>
    <style>
        )" + generateCSS() + R"(
    </style>
</head>
<body>
    <div id="stars"></div>
    <div id="moon"></div>

    <div class="container">
        <aside class="sidebar">
            <div class="logo">
                <i class="moon-icon">🌙</i>
                <span>Vũ Trụ Văn Học</span>
            </div>
            <nav class="menu">
                <div class="menu-section">
                    <h3>Môn học</h3>
                    <ul>
                        <li class="active" data-content="van-hoc">
                            <i class="icon">📚</i>
                            <span>Văn Học</span>
                        </li>
                        <li data-content="toan-hoc">
                            <i class="icon">🧮</i>
                            <span>Toán Học</span>
                        </li>
                        <li data-content="lich-su">
                            <i class="icon">🏛️</i>
                            <span>Lịch Sử</span>
                        </li>
                    </ul>
                </div>
                
                <div class="sub-menu" id="van-hoc-submenu">
                    <h3>Bài tập Văn Học</h3>
                    <ul>
                        <li data-content="mo-bai">Mở bài</li>
                        <li data-content="than-bai">Thân bài</li>
                        <li data-content="ket-bai">Kết bài</li>
                    </ul>
                </div>
            </nav>
        </aside>

        <main class="content">
            <div class="content-section active" id="van-hoc">
                <h1>Văn Học Việt Nam</h1>
                <div class="card-grid">
                    <div class="card">
                        <h3>Truyện Kiều</h3>
                        <p>Nguyễn Du</p>
                    </div>
                    <div class="card">
                        <h3>Chí Phèo</h3>
                        <p>Nam Cao</p>
                    </div>
                    <div class="card">
                        <h3>Vợ Nhặt</h3>
                        <p>Kim Lân</p>
                    </div>
                </div>
            </div>

            <div class="content-section" id="mo-bai">
                <h1>Mở Bài</h1>
                <div class="presentation-content">
                    <p>Phần mở bài giới thiệu tổng quan về tác phẩm, tác giả và vấn đề cần phân tích.</p>
                </div>
            </div>

            <div class="content-section" id="than-bai">
                <h1>Thân Bài</h1>
                <div class="presentation-content">
                    <p>Phần thân bài triển khai các luận điểm, phân tích chi tiết tác phẩm.</p>
                </div>
            </div>

            <div class="content-section" id="ket-bai">
                <h1>Kết Bài</h1>
                <div class="presentation-content">
                    <p>Phần kết bài tổng kết lại vấn đề và nêu cảm nghĩ về tác phẩm.</p>
                </div>
            </div>
        </main>
    </div>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            // Xử lý chuyển đổi menu
            const menuItems = document.querySelectorAll('.menu li');
            const contentSections = document.querySelectorAll('.content-section');
            
            menuItems.forEach(item => {
                item.addEventListener('click', function() {
                    const contentId = this.getAttribute('data-content');
                    
                    // Ẩn tất cả nội dung
                    contentSections.forEach(section => {
                        section.classList.remove('active');
                    });
                    
                    // Hiển thị nội dung được chọn
                    document.getElementById(contentId).classList.add('active');
                    
                    // Cập nhật menu active
                    menuItems.forEach(i => i.classList.remove('active'));
                    this.classList.add('active');
                    
                    // Hiển thị submenu nếu là môn Văn
                    if (contentId === 'van-hoc') {
                        document.getElementById('van-hoc-submenu').style.display = 'block';
                    } else {
                        document.getElementById('van-hoc-submenu').style.display = 'none';
                    }
                });
            });
            
            // Tạo hiệu ứng sao
            const stars = document.getElementById('stars');
            for (let i = 0; i < 100; i++) {
                const star = document.createElement('div');
                star.className = 'star';
                star.style.top = Math.random() * 100 + 'vh';
                star.style.left = Math.random() * 100 + 'vw';
                star.style.animationDelay = Math.random() * 5 + 's';
                stars.appendChild(star);
            }
        });
    </script>
</body>
</html>
        )";
    }
    
    std::string generateCSS() {
        return R"(
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #0a0a2a, #1a1a40, #0a0a2a);
            color: #e0e0ff;
            min-height: 100vh;
            overflow-x: hidden;
            position: relative;
        }

        #stars {
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            z-index: -1;
        }

        .star {
            position: absolute;
            background-color: white;
            border-radius: 50%;
            animation: twinkle 5s infinite;
        }

        @keyframes twinkle {
            0%, 100% { opacity: 0.2; }
            50% { opacity: 1; }
        }

        #moon {
            position: fixed;
            top: 50px;
            right: 50px;
            width: 100px;
            height: 100px;
            background: radial-gradient(circle, #f0f0ff 10%, #a0a0c0 60%);
            border-radius: 50%;
            box-shadow: 0 0 50px #f0f0ff, 0 0 100px #a0a0c0;
            z-index: -1;
            animation: float 10s ease-in-out infinite;
        }

        @keyframes float {
            0%, 100% { transform: translateY(0) rotate(0deg); }
            50% { transform: translateY(-20px) rotate(5deg); }
        }

        .container {
            display: flex;
            min-height: 100vh;
        }

        .sidebar {
            width: 280px;
            background: rgba(10, 10, 40, 0.8);
            backdrop-filter: blur(10px);
            padding: 20px;
            border-right: 1px solid rgba(100, 100, 255, 0.2);
            display: flex;
            flex-direction: column;
        }

        .logo {
            display: flex;
            align-items: center;
            margin-bottom: 30px;
            font-size: 1.5rem;
            font-weight: bold;
            color: #a0a0ff;
        }

        .moon-icon {
            font-size: 2rem;
            margin-right: 10px;
        }

        .menu-section {
            margin-bottom: 30px;
        }

        .menu-section h3 {
            color: #8080ff;
            margin-bottom: 15px;
            font-size: 1rem;
            text-transform: uppercase;
            letter-spacing: 1px;
        }

        .menu ul {
            list-style: none;
        }

        .menu li {
            padding: 12px 15px;
            margin-bottom: 8px;
            border-radius: 8px;
            cursor: pointer;
            transition: all 0.3s ease;
            display: flex;
            align-items: center;
        }

        .menu li:hover {
            background: rgba(100, 100, 255, 0.2);
            transform: translateX(5px);
        }

        .menu li.active {
            background: rgba(100, 100, 255, 0.3);
            box-shadow: 0 0 15px rgba(100, 100, 255, 0.5);
        }

        .icon {
            margin-right: 10px;
            font-size: 1.2rem;
        }

        .sub-menu {
            display: block;
            margin-top: 20px;
        }

        .sub-menu li {
            padding-left: 40px;
            font-size: 0.9rem;
        }

        .content {
            flex: 1;
            padding: 30px;
            overflow-y: auto;
        }

        .content-section {
            display: none;
            animation: fadeIn 0.5s ease;
        }

        .content-section.active {
            display: block;
        }

        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(20px); }
            to { opacity: 1; transform: translateY(0); }
        }

        h1 {
            font-size: 2.5rem;
            margin-bottom: 30px;
            color: #a0a0ff;
            text-shadow: 0 0 10px rgba(160, 160, 255, 0.5);
        }

        .card-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(250px, 1fr));
            gap: 20px;
            margin-top: 20px;
        }

        .card {
            background: rgba(20, 20, 50, 0.7);
            border-radius: 15px;
            padding: 20px;
            transition: all 0.3s ease;
            border: 1px solid rgba(100, 100, 255, 0.2);
            cursor: pointer;
        }

        .card:hover {
            transform: scale(1.05);
            box-shadow: 0 0 20px rgba(100, 100, 255, 0.5);
            background: rgba(30, 30, 70, 0.8);
        }

        .card h3 {
            color: #c0c0ff;
            margin-bottom: 10px;
        }

        .card p {
            color: #a0a0c0;
            font-size: 0.9rem;
        }

        .presentation-content {
            background: rgba(20, 20, 50, 0.7);
            border-radius: 15px;
            padding: 30px;
            margin-top: 20px;
            border: 1px solid rgba(100, 100, 255, 0.2);
        }

        .presentation-content p {
            line-height: 1.6;
            font-size: 1.1rem;
        }

        /* Responsive design */
        @media (max-width: 768px) {
            .container {
                flex-direction: column;
            }
            
            .sidebar {
                width: 100%;
                border-right: none;
                border-bottom: 1px solid rgba(100, 100, 255, 0.2);
            }
            
            #moon {
                top: 20px;
                right: 20px;
                width: 60px;
                height: 60px;
            }
            
            h1 {
                font-size: 2rem;
            }
            
            .card-grid {
                grid-template-columns: 1fr;
            }
        }
        )";
    }
};

int main() {
    WebServer server(8080);
    
    if (!server.start()) {
        return 1;
    }
    
    std::cout << "Web server đang chạy tại http://localhost:8080" << std::endl;
    std::cout << "Nhấn Ctrl+C để dừng server" << std::endl;
    
    server.handleRequests();
    
    return 0;
}