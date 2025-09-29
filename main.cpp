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
    WebServer() {
        const char* env_port = std::getenv("PORT");
        port = env_port ? std::atoi(env_port) : 8080;
        server_fd = -1;
    }
    
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
    <title>Vũ Trụ Văn Học - Nghị Luận</title>
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
                    <h3>Kiểu bài Văn</h3>
                    <ul>
                        <li class="active" data-content="nghi-luan-xa-hoi">
                            <i class="icon">🏛️</i>
                            <span>Nghị luận xã hội</span>
                        </li>
                        <li data-content="nghi-luan-van-hoc">
                            <i class="icon">📚</i>
                            <span>Nghị luận văn học</span>
                        </li>
                    </ul>
                </div>
            </nav>
        </aside>

        <main class="content">
            <!-- Nghị luận xã hội -->
            <div class="content-section active" id="nghi-luan-xa-hoi">
                <h1>Nghị Luận Xã Hội</h1>
                <div class="presentation-content">
                    <div class="writing-part">
                        <h2><i class="part-icon">✨</i> Mở bài</h2>
                        <div class="writing-detail">
                            <h3>Mục đích:</h3>
                            <p>Dẫn dắt vào vấn đề xã hội cần nghị luận</p>
                            
                            <h3>Cách viết:</h3>
                            <ul>
                                <li>Giới thiệu vấn đề một cách tự nhiên</li>
                                <li>Nêu tính thời sự, ý nghĩa của vấn đề</li>
                                <li>Trích dẫn câu nói, nhận định (nếu có)</li>
                                <li>Dẫn dắt vào thân bài</li>
                            </ul>
                            
                            <div class="example">
                                <h3>Ví dụ mở bài:</h3>
                                <p>"Trong xã hội hiện đại ngày nay, vấn đề ô nhiễm môi trường đang trở thành mối quan tâm hàng đầu của toàn nhân loại. Sự phát triển kinh tế nhanh chóng đã kéo theo những hệ lụy nghiêm trọng về môi trường, đòi hỏi chúng ta phải có những hành động thiết thực để bảo vệ ngôi nhà chung của nhân loại."</p>
                            </div>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">📖</i> Thân bài</h2>
                        <div class="writing-detail">
                            <h3>Các bước triển khai:</h3>
                            <ol>
                                <li>
                                    <strong>Giải thích vấn đề:</strong>
                                    <ul>
                                        <li>Làm rõ các khái niệm, thuật ngữ</li>
                                        <li>Giải thích ý nghĩa của vấn đề</li>
                                        <li>Nêu biểu hiện cụ thể</li>
                                    </ul>
                                </li>
                                <li>
                                    <strong>Phân tích vấn đề:</strong>
                                    <ul>
                                        <li>Nguyên nhân, nguồn gốc phát sinh</li>
                                        <li>Tác động tích cực/tiêu cực</li>
                                        <li>Thực trạng hiện nay</li>
                                    </ul>
                                </li>
                                <li>
                                    <strong>Chứng minh:</strong>
                                    <ul>
                                        <li>Đưa dẫn chứng thuyết phục</li>
                                        <li>Số liệu, sự kiện cụ thể</li>
                                        <li>Ví dụ thực tế</li>
                                    </ul>
                                </li>
                                <li>
                                    <strong>Bàn luận mở rộng:</strong>
                                    <ul>
                                        <li>So sánh với vấn đề khác</li>
                                        <li>Đánh giá các quan điểm</li>
                                        <li>Phản đề (nếu cần)</li>
                                    </ul>
                                </li>
                                <li>
                                    <strong>Bài học nhận thức:</strong>
                                    <ul>
                                        <li>Rút ra bài học</li>
                                        <li>Đề xuất giải pháp</li>
                                        <li>Phương hướng hành động</li>
                                    </ul>
                                </li>
                            </ol>
                            
                            <div class="example">
                                <h3>Ví dụ phân tích:</h3>
                                <p>"Ô nhiễm môi trường bắt nguồn từ nhiều nguyên nhân: sự thiếu ý thức của con người, sự phát triển công nghiệp ồ ạt, hệ thống xử lý rác thải chưa hiệu quả... Theo thống kê, mỗi năm thế giới thải ra hơn 2 tỷ tấn rác thải, trong đó chỉ 16% được tái chế."</p>
                            </div>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">🎯</i> Kết bài</h2>
                        <div class="writing-detail">
                            <h3>Yêu cầu:</h3>
                            <ul>
                                <li>Khẳng định lại tầm quan trọng của vấn đề</li>
                                <li>Tóm tắt những ý chính đã trình bày</li>
                                <li>Nêu giải pháp, kiến nghị</li>
                                <li>Liên hệ bản thân và rút ra bài học</li>
                            </ul>
                            
                            <div class="example">
                                <h3>Ví dụ kết bài:</h3>
                                <p>"Như vậy, bảo vệ môi trường không chỉ là trách nhiệm của các tổ chức, chính phủ mà còn là nghĩa vụ của mỗi cá nhân. Bằng những hành động nhỏ nhất như phân loại rác, tiết kiệm điện nước, chúng ta đang góp phần xây dựng một tương lai xanh - sạch - đẹp cho thế hệ mai sau."</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>

            <!-- Nghị luận văn học -->
            <div class="content-section" id="nghi-luan-van-hoc">
                <h1>Nghị Luận Văn Học</h1>
                <div class="presentation-content">
                    <div class="writing-part">
                        <h2><i class="part-icon">✨</i> Mở bài</h2>
                        <div class="writing-detail">
                            <h3>Mục đích:</h3>
                            <p>Giới thiệu tác giả, tác phẩm và vấn đề nghị luận</p>
                            
                            <h3>Cách viết:</h3>
                            <ul>
                                <li>Giới thiệu tác giả và hoàn cảnh sáng tác</li>
                                <li>Nêu tên tác phẩm và vị trí trong sự nghiệp</li>
                                <li>Dẫn dắt vào vấn đề cần nghị luận</li>
                                <li>Trích dẫn nhận định (nếu có)</li>
                            </ul>
                            
                            <div class="example">
                                <h3>Ví dụ mở bài:</h3>
                                <p>"Nguyễn Du - đại thi hào của dân tộc Việt Nam, đã để lại cho kho tàng văn học nước nhà kiệt tác 'Truyện Kiều'. Tác phẩm không chỉ là bức tranh hiện thực về xã hội phong kiến mà còn là tiếng lòng thương cảm cho số phận người phụ nữ. Trong đó, nhân vật Thúy Kiều hiện lên như một biểu tượng của cái đẹp và nỗi đau."</p>
                            </div>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">📖</i> Thân bài</h2>
                        <div class="writing-detail">
                            <h3>Các hướng triển khai:</h3>
                            
                            <div class="method">
                                <h4>1. Phân tích nhân vật:</h4>
                                <ul>
                                    <li><strong>Ngoại hình:</strong> Miêu tả, so sánh</li>
                                    <li><strong>Tính cách:</strong> Phẩm chất, đức tính</li>
                                    <li><strong>Số phận:</strong> Bi kịch, thành công</li>
                                    <li><strong>Diễn biến tâm lý:</strong> Cảm xúc, suy nghĩ</li>
                                    <li><strong>Ý nghĩa nhân vật:</strong> Đại diện, biểu tượng</li>
                                </ul>
                            </div>
                            
                            <div class="method">
                                <h4>2. Phân tích đoạn trích/tác phẩm:</h4>
                                <ul>
                                    <li><strong>Nội dung:</strong> Chủ đề, tư tưởng</li>
                                    <li><strong>Nghệ thuật:</strong> Ngôn ngữ, hình ảnh</li>
                                    <li><strong>Biện pháp tu từ:</strong> So sánh, ẩn dụ, hoán dụ...</li>
                                    <li><strong>Kết cấu:</strong> Bố cục, trình tự</li>
                                    <li><strong>Giá trị:</strong> Nhân đạo, hiện thực</li>
                                </ul>
                            </div>
                            
                            <div class="method">
                                <h4>3. Phân tích giá trị tác phẩm:</h4>
                                <ul>
                                    <li><strong>Giá trị nhân đạo:</strong> Tình thương, lòng vị tha</li>
                                    <li><strong>Giá trị hiện thực:</strong> Bức tranh xã hội</li>
                                    <li><strong>Giá trị nghệ thuật:</strong> Ngôn ngữ, kết cấu</li>
                                    <li><strong>Thông điệp:</strong> Bài học, triết lý</li>
                                </ul>
                            </div>
                            
                            <div class="example">
                                <h3>Ví dụ phân tích nhân vật:</h3>
                                <p>"Thúy Kiều không chỉ đẹp về ngoại hình 'Làn thu thủy nét xuân sơn' mà còn đẹp về tâm hồn và tài năng. Nàng là hiện thân của cái đẹp toàn diện: 'Sắc đành đòi một tài đành họa hai'. Thế nhưng, chính vì sự toàn diện ấy mà nàng phải chịu số phận 'Hồng nhan bạc mệnh', trải qua mười lăm năm lưu lạc đầy đau khổ."</p>
                            </div>
                        </div>
                    </div>
                    
                    <div class="writing-part">
                        <h2><i class="part-icon">🎯</i> Kết bài</h2>
                        <div class="writing-detail">
                            <h3>Yêu cầu:</h3>
                            <ul>
                                <li>Khẳng định giá trị tác phẩm</li>
                                <li>Đánh giá ý nghĩa vấn đề nghị luận</li>
                                <li>Nêu cảm nghĩ, bài học rút ra</li>
                                <li>Liên hệ với hiện tại</li>
                            </ul>
                            
                            <div class="example">
                                <h3>Ví dụ kết bài:</h3>
                                <p>"Qua nhân vật Thúy Kiều, Nguyễn Du không chỉ khắc họa thành công số phận người phụ nữ trong xã hội phong kiến mà còn gửi gắm những giá trị nhân văn sâu sắc. Tác phẩm mãi mãi là viên ngọc quý trong kho tàng văn học dân tộc, để lại nhiều suy ngẫm về cuộc đời và con người cho hậu thế."</p>
                            </div>
                        </div>
                    </div>
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

        h3 {
            font-size: 1.3rem;
            margin: 15px 0 10px;
            color: #c0c0ff;
        }

        h4 {
            font-size: 1.1rem;
            margin: 12px 0 8px;
            color: #d0d0ff;
        }

        .part-icon {
            margin-right: 10px;
            font-size: 1.5rem;
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

        .writing-detail {
            background: rgba(30, 30, 60, 0.5);
            padding: 20px;
            border-radius: 10px;
            margin-top: 10px;
        }

        .writing-detail ul, .writing-detail ol {
            padding-left: 25px;
            margin: 10px 0;
        }

        .writing-detail li {
            margin-bottom: 8px;
            line-height: 1.5;
        }

        .writing-detail p {
            line-height: 1.6;
            margin: 10px 0;
        }

        .method {
            background: rgba(40, 40, 80, 0.4);
            padding: 15px;
            border-radius: 8px;
            margin: 10px 0;
            border-left: 3px solid #8080ff;
        }

        .example {
            background: rgba(50, 50, 100, 0.6);
            padding: 15px;
            border-radius: 8px;
            margin-top: 15px;
            border-left: 4px solid #a0a0ff;
        }

        .example h3 {
            color: #b0b0ff;
            margin-bottom: 10px;
            font-size: 1.1rem;
        }

        .example p {
            color: #e0e0ff;
            font-style: italic;
            line-height: 1.5;
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
            
            h3 {
                font-size: 1.1rem;
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
    
    std::cout << "Web server Nghị Luận Văn Học đang chạy tại http://localhost:" << port << std::endl;
    std::cout << "Nhấn Ctrl+C để dừng server" << std::endl;
    
    server.handleRequests();
    
    return 0;
}