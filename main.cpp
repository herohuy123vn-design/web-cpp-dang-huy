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
    WebServer() : port(10000), server_fd(-1) {}
    
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
            } else if (request.find("GET /style.css") != std::string::npos) {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n" + generateCSS();
            } else {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + generateHTML();
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
    <title>Vũ Trụ Văn Học - Không Gian Mặt Trăng</title>
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
                <span>9A2</span>
            </div>
            <nav class="menu">
                <div class="menu-section">
                    <h3>Môn học</h3>
                    <ul>
                        <li class="active" data-content="van-hoc">
                            <i class="icon">📚</i>
                            <span>Văn Học</span>
                        </li>
                    </ul>
                </div>
                
                <div class="sub-menu" id="van-hoc-submenu">
                    <h3>bài thuyết trình:</h3>
                    <ul>
                        <li data-content="phat-bieu-cam-nghi" class="active">Phát biểu cảm nghĩ</li>
                        <li data-content="bai-2">text</li>
                        <li data-content="bai-3">text</li>
                        <li data-content="bai-4">text</li>
                        <li data-content="bai-5">text</li>
                        <li data-content="bai-6">text</li>
                    </ul>
                </div>
            </nav>
        </aside>

        <main class="content">
            <div class="content-section active" id="van-hoc">
                <h1>Văn Học Việt Nam</h1>
                <div class="card-grid">
                    <div class="card">
                        <h3>chuyện người con gái nam xương</h3>
                        <p>Nguyễn Dữ - tác phẩm kinh điển</p>
                    </div>
                    <div class="card">
                        <h3>Dế chọi</h3>
                        <p>Bồ Tùng Linh - Hiện thực phê phán</p>
                    </div>
                    <div class="card">
                        <h3>Sơn Tinh - thủy tinh</h3>
                        <p>Nguyễn Nhược Pháp - Văn học hiện đại</p>
                    </div>
                </div>
            </div>

            <div class="content-section" id="phat-bieu-cam-nghi">
                <h1>Phát biểu cảm nghĩ</h1>
                <div class="presentation-content">
                    <div class="writing-part">
                        <h2><i class="part-icon">✨</i> Mở bài</h2>
                        <p>Giới thiệu về đối tượng và nêu cảm nghĩ chung. Phần mở bài cần tạo được ấn tượng và dẫn dắt người đọc vào nội dung.</p>
                        <div class="example">
                            <h3>Ví dụ:</h3>
                            <p>"Mỗi khi đọc lại những trang thơ của Xuân Diệu, lòng tôi lại dâng trào một cảm xúc khó tả. Nhà thơ của tình yêu và tuổi trẻ ấy đã để lại cho đời những vần thơ đẹp như những đóa hoa ngát hương..."</p>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">📖</i> Thân bài</h2>
                        <p>Triển khai các luận điểm về đối tượng, nêu cảm xúc, suy nghĩ chi tiết. Có thể sắp xếp theo trình tự từ khái quát đến cụ thể.</p>
                        <div class="example">
                            <h3>Bố cục thân bài:</h3>
                            <ul>
                                <li>Biểu cảm về ngoại hình, đặc điểm</li>
                                <li>Biểu cảm về tính cách, phẩm chất</li>
                                <li>Biểu cảm về kỷ niệm, tác động</li>
                                <li>Suy nghĩ, đánh giá về đối tượng</li>
                            </ul>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">🎯</i> Kết bài</h2>
                        <p>Khái quát lại cảm nghĩ và nêu những suy ngẫm, bài học rút ra. Phần kết bài nên để lại ấn tượng sâu sắc trong lòng người đọc.</p>
                        <div class="example">
                            <h3>Ví dụ:</h3>
                            <p>"Cảm ơn nhà thơ Xuân Diệu đã mang đến cho chúng ta một thế giới nghệ thuật đầy màu sắc. Những vần thơ ấy sẽ mãi đồng hành cùng bao thế hệ bạn đọc, khơi gợi trong họ tình yêu với cuộc sống và vẻ đẹp của ngôn từ..."</p>
                        </div>
                    </div>
                </div>
            </div>

            <div class="content-section" id="phan-tich-tac-pham">
                <h1>Phân tích tác phẩm</h1>
                <div class="presentation-content">
                    <div class="writing-part">
                        <h2><i class="part-icon">✨</i> Mở bài</h2>
                        <p>Giới thiệu tác giả, tác phẩm và vấn đề cần phân tích. Nêu khái quát giá trị và vị trí của tác phẩm trong nền văn học.</p>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">📖</i> Thân bài</h2>
                        <p>Phân tích các khía cạnh của tác phẩm: nội dung, nghệ thuật, giá trị tư tưởng, các biện pháp tu từ, hình tượng nghệ thuật...</p>
                        <div class="example">
                            <h3>Các bước phân tích:</h3>
                            <ul>
                                <li>Phân tích hình tượng nhân vật</li>
                                <li>Phân tích tình huống truyện</li>
                                <li>Phân tích giá trị nội dung</li>
                                <li>Phân tích giá trị nghệ thuật</li>
                                <li>Đánh giá ý nghĩa tư tưởng</li>
                            </ul>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">🎯</i> Kết bài</h2>
                        <p>Khẳng định lại giá trị của tác phẩm và ý nghĩa của việc phân tích. Nêu cảm nghĩ về tầm ảnh hưởng của tác phẩm.</p>
                    </div>
                </div>
            </div>

            <div class="content-section" id="nghi-luan-xa-hoi">
                <h1>Nghị luận xã hội</h1>
                <div class="presentation-content">
                    <div class="writing-part">
                        <h2><i class="part-icon">✨</i> Mở bài</h2>
                        <p>Dẫn dắt vào vấn đề xã hội cần nghị luận, nêu tính thời sự và tầm quan trọng của vấn đề.</p>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">📖</i> Thân bài</h2>
                        <p>Giải thích, phân tích, chứng minh và bàn luận về vấn đề xã hội. Đưa ra các dẫn chứng thuyết phục.</p>
                        <div class="example">
                            <h3>Các bước triển khai:</h3>
                            <ul>
                                <li>Giải thích khái niệm, thuật ngữ</li>
                                <li>Phân tích các khía cạnh của vấn đề</li>
                                <li>Bàn luận mở rộng vấn đề</li>
                                <li>Đưa ra dẫn chứng thực tế</li>
                                <li>Rút ra bài học nhận thức</li>
                            </ul>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">🎯</i> Kết bài</h2>
                        <p>Khẳng định lại ý nghĩa của vấn đề, nêu giải pháp và liên hệ bản thân.</p>
                    </div>
                </div>
            </div>

            <!-- Các phần khác tương tự -->

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
            width: 2px;
            height: 2px;
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

        h2 {
            font-size: 1.8rem;
            margin: 25px 0 15px;
            color: #b0b0ff;
            display: flex;
            align-items: center;
        }

        .part-icon {
            margin-right: 10px;
            font-size: 1.5rem;
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

        .writing-part {
            margin-bottom: 30px;
            padding-bottom: 20px;
            border-bottom: 1px solid rgba(100, 100, 255, 0.2);
        }

        .writing-part:last-child {
            border-bottom: none;
            margin-bottom: 0;
            padding-bottom: 0;
        }

        .presentation-content p {
            line-height: 1.6;
            font-size: 1.1rem;
            margin-bottom: 15px;
        }

        .example {
            background: rgba(30, 30, 60, 0.5);
            padding: 15px;
            border-radius: 10px;
            margin-top: 15px;
            border-left: 4px solid #8080ff;
        }

        .example h3 {
            color: #a0a0ff;
            margin-bottom: 10px;
            font-size: 1.1rem;
        }

        .example p, .example ul {
            color: #d0d0ff;
            font-size: 1rem;
        }

        .example ul {
            padding-left: 20px;
        }

        .example li {
            margin-bottom: 8px;
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
            
            h2 {
                font-size: 1.5rem;
            }
            
            .card-grid {
                grid-template-columns: 1fr;
            }
        }
        )";
    }
};

int main() {
    WebServer server;
    
    if (!server.start()) {
        return 1;
    }
    
    std::cout << "Web server môn Văn đang chạy tại http://localhost:10000" << std::endl;
    std::cout << "Nhấn Ctrl+C để dừng server" << std::endl;
    
    server.handleRequests();
    
    return 0;
}