#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>
#include <thread>
#include <chrono>
#include <map>

// Hàm thực thi lệnh và trả về kết quả
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Hàm tạo trang HTML với giao diện không gian vũ trụ
std::string generateHTML() {
    return R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hệ Thống Thuyết Trình Học Tập</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        :root {
            --primary-color: #1a1a2e;
            --secondary-color: #16213e;
            --accent-color: #0f3460;
            --text-color: #f0f0f0;
            --highlight: #4cc9f0;
            --moon-color: #e6e6e6;
            --star-color: #ffffff;
        }

        body {
            background: linear-gradient(to bottom, #000428, #004e92);
            color: var(--text-color);
            min-height: 100vh;
            overflow-x: hidden;
            position: relative;
        }

        /* Background elements - stars and moon */
        .stars {
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            z-index: -1;
        }

        .star {
            position: absolute;
            background-color: var(--star-color);
            border-radius: 50%;
            animation: twinkle 5s infinite;
        }

        @keyframes twinkle {
            0%, 100% { opacity: 0.2; }
            50% { opacity: 1; }
        }

        .moon {
            position: fixed;
            top: 50px;
            right: 50px;
            width: 100px;
            height: 100px;
            border-radius: 50%;
            background: var(--moon-color);
            box-shadow: 0 0 40px 10px rgba(255, 255, 255, 0.6);
            z-index: -1;
        }

        /* Layout */
        .container {
            display: flex;
            min-height: 100vh;
        }

        /* Sidebar */
        .sidebar {
            width: 280px;
            background-color: rgba(26, 26, 46, 0.8);
            backdrop-filter: blur(10px);
            padding: 20px 0;
            border-right: 1px solid rgba(79, 129, 189, 0.3);
            overflow-y: auto;
            transition: all 0.3s ease;
            box-shadow: 0 0 15px rgba(0, 0, 0, 0.5);
        }

        .sidebar-header {
            text-align: center;
            padding: 0 20px 20px;
            border-bottom: 1px solid rgba(255, 255, 255, 0.1);
        }

        .sidebar-header h2 {
            color: var(--highlight);
            margin-bottom: 5px;
        }

        .sidebar-menu {
            list-style: none;
            padding: 10px 0;
        }

        .menu-item {
            border-bottom: 1px solid rgba(255, 255, 255, 0.05);
        }

        .menu-title {
            padding: 15px 20px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            cursor: pointer;
            transition: all 0.3s;
        }

        .menu-title:hover {
            background-color: rgba(15, 52, 96, 0.5);
        }

        .menu-title i {
            transition: transform 0.3s;
        }

        .submenu {
            list-style: none;
            max-height: 0;
            overflow: hidden;
            transition: max-height 0.3s ease;
            background-color: rgba(10, 15, 30, 0.5);
        }

        .submenu.open {
            max-height: 500px;
        }

        .submenu-item {
            padding: 12px 20px 12px 40px;
            cursor: pointer;
            transition: all 0.3s;
        }

        .submenu-item:hover {
            background-color: rgba(15, 52, 96, 0.3);
            color: var(--highlight);
        }

        /* Main content */
        .main-content {
            flex: 1;
            padding: 30px;
            display: flex;
            flex-direction: column;
        }

        .content-header {
            margin-bottom: 30px;
            text-align: center;
        }

        .content-header h1 {
            font-size: 2.5rem;
            margin-bottom: 10px;
            color: var(--highlight);
            text-shadow: 0 0 10px rgba(76, 201, 240, 0.5);
        }

        .content-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 25px;
            margin-top: 20px;
        }

        .card {
            background: rgba(26, 26, 46, 0.7);
            border-radius: 15px;
            overflow: hidden;
            transition: all 0.3s ease;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
            height: 250px;
            display: flex;
            flex-direction: column;
        }

        .card:hover {
            transform: translateY(-10px) scale(1.03);
            box-shadow: 0 15px 30px rgba(0, 0, 0, 0.4), 0 0 15px rgba(76, 201, 240, 0.4);
        }

        .card-header {
            background: var(--accent-color);
            padding: 15px;
            text-align: center;
        }

        .card-body {
            padding: 20px;
            flex: 1;
            display: flex;
            flex-direction: column;
            justify-content: space-between;
        }

        .card-content {
            margin-bottom: 15px;
        }

        .card-buttons {
            display: flex;
            justify-content: space-around;
        }

        .card-btn {
            padding: 8px 15px;
            background: var(--accent-color);
            border: none;
            border-radius: 5px;
            color: var(--text-color);
            cursor: pointer;
            transition: all 0.3s;
        }

        .card-btn:hover {
            background: var(--highlight);
            color: var(--primary-color);
        }

        /* Presentation content */
        .presentation-content {
            background: rgba(26, 26, 46, 0.8);
            border-radius: 15px;
            padding: 25px;
            margin-top: 30px;
            display: none;
        }

        .presentation-content.active {
            display: block;
            animation: fadeIn 0.5s;
        }

        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }

        .section-nav {
            display: flex;
            justify-content: center;
            margin-bottom: 20px;
        }

        .section-btn {
            padding: 10px 20px;
            margin: 0 10px;
            background: var(--accent-color);
            border: none;
            border-radius: 5px;
            color: var(--text-color);
            cursor: pointer;
            transition: all 0.3s;
        }

        .section-btn.active {
            background: var(--highlight);
            color: var(--primary-color);
        }

        .section-content {
            display: none;
            padding: 20px;
            background: rgba(15, 52, 96, 0.3);
            border-radius: 10px;
            min-height: 200px;
        }

        .section-content.active {
            display: block;
        }

        /* Responsive design */
        @media (max-width: 992px) {
            .container {
                flex-direction: column;
            }
            
            .sidebar {
                width: 100%;
                height: auto;
                max-height: 70vh;
            }
            
            .content-grid {
                grid-template-columns: repeat(auto-fill, minmax(250px, 1fr));
            }
        }

        @media (max-width: 576px) {
            .content-grid {
                grid-template-columns: 1fr;
            }
            
            .moon {
                width: 60px;
                height: 60px;
                right: 20px;
                top: 20px;
            }
            
            .main-content {
                padding: 15px;
            }
        }
    </style>
</head>
<body>
    <!-- Background elements -->
    <div class="stars" id="stars"></div>
    <div class="moon"></div>

    <div class="container">
        <!-- Sidebar với menu môn học -->
        <div class="sidebar">
            <div class="sidebar-header">
                <h2>Môn Học</h2>
                <p>Chọn môn để thuyết trình</p>
            </div>
            <ul class="sidebar-menu">
                <!-- Toán -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-calculator"></i> Toán học</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('toan', 'hinh-hoc')">Hình học</li>
                        <li class="submenu-item" onclick="showPresentation('toan', 'dai-so')">Đại số</li>
                        <li class="submenu-item" onclick="showPresentation('toan', 'thong-ke')">Thống kê</li>
                    </ul>
                </li>
                
                <!-- Ngữ văn -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-book"></i> Ngữ văn</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('van', 'van-hoc')">Văn học</li>
                        <li class="submenu-item" onclick="showPresentation('van', 'ngu-phap')">Ngữ pháp</li>
                        <li class="submenu-item" onclick="showPresentation('van', 'lam-van')">Làm văn</li>
                    </ul>
                </li>
                
                <!-- Ngoại ngữ -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-globe-americas"></i> Ngoại ngữ</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('ngoai-ngu', 'tu-vung')">Từ vựng</li>
                        <li class="submenu-item" onclick="showPresentation('ngoai-ngu', 'ngu-phap')">Ngữ pháp</li>
                        <li class="submenu-item" onclick="showPresentation('ngoai-ngu', 'giao-tiep')">Giao tiếp</li>
                    </ul>
                </li>
                
                <!-- Vật lý -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-atom"></i> Vật lý</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('vat-ly', 'co-hoc')">Cơ học</li>
                        <li class="submenu-item" onclick="showPresentation('vat-ly', 'quang-hoc')">Quang học</li>
                        <li class="submenu-item" onclick="showPresentation('vat-ly', 'dien-hoc')">Điện học</li>
                    </ul>
                </li>
                
                <!-- Sinh học -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-dna"></i> Sinh học</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('sinh-hoc', 'te-bao')">Tế bào</li>
                        <li class="submenu-item" onclick="showPresentation('sinh-hoc', 'di-truyen')">Di truyền</li>
                        <li class="submenu-item" onclick="showPresentation('sinh-hoc', 'sinh-thai')">Sinh thái</li>
                    </ul>
                </li>
                
                <!-- Lịch sử -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-landmark"></i> Lịch sử</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('lich-su', 'co-dai')">Cổ đại</li>
                        <li class="submenu-item" onclick="showPresentation('lich-su', 'trung-dai')">Trung đại</li>
                        <li class="submenu-item" onclick="showPresentation('lich-su', 'hien-dai')">Hiện đại</li>
                    </ul>
                </li>
                
                <!-- Địa lý -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-globe-asia"></i> Địa lý</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('dia-ly', 'tu-nhien')">Tự nhiên</li>
                        <li class="submenu-item" onclick="showPresentation('dia-ly', 'kinh-te')">Kinh tế</li>
                        <li class="submenu-item" onclick="showPresentation('dia-ly', 'dan-cu')">Dân cư</li>
                    </ul>
                </li>
                
                <!-- Hóa học -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-flask"></i> Hóa học</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('hoa-hoc', 'vo-co')">Hóa vô cơ</li>
                        <li class="submenu-item" onclick="showPresentation('hoa-hoc', 'huu-co')">Hóa hữu cơ</li>
                        <li class="submenu-item" onclick="showPresentation('hoa-hoc', 'phan-ung')">Phản ứng hóa học</li>
                    </ul>
                </li>
                
                <!-- Tin học -->
                <li class="menu-item">
                    <div class="menu-title" onclick="toggleSubmenu(this)">
                        <span><i class="fas fa-laptop-code"></i> Tin học</span>
                        <i class="fas fa-chevron-down"></i>
                    </div>
                    <ul class="submenu">
                        <li class="submenu-item" onclick="showPresentation('tin-hoc', 'lap-trinh')">Lập trình</li>
                        <li class="submenu-item" onclick="showPresentation('tin-hoc', 'csdl')">Cơ sở dữ liệu</li>
                        <li class="submenu-item" onclick="showPresentation('tin-hoc', 'mang-may-tinh')">Mạng máy tính</li>
                    </ul>
                </li>
            </ul>
        </div>

        <!-- Nội dung chính -->
        <div class="main-content">
            <div class="content-header">
                <h1>Hệ Thống Thuyết Trình Học Tập</h1>
                <p>Chọn môn học và chuyên đề từ menu bên trái để bắt đầu</p>
            </div>

            <!-- Grid card hiển thị nội dung -->
            <div class="content-grid">
                <div class="card">
                    <div class="card-header">
                        <h3>Toán - Hình học</h3>
                    </div>
                    <div class="card-body">
                        <div class="card-content">
                            <p>Khám phá thế giới hình học với các định lý và công thức tính toán thú vị.</p>
                        </div>
                        <div class="card-buttons">
                            <button class="card-btn" onclick="showPresentation('toan', 'hinh-hoc')">Xem bài</button>
                        </div>
                    </div>
                </div>

                <div class="card">
                    <div class="card-header">
                        <h3>Ngữ văn - Văn học</h3>
                    </div>
                    <div class="card-body">
                        <div class="card-content">
                            <p>Khám phá các tác phẩm văn học nổi tiếng và phân tích ý nghĩa sâu sắc.</p>
                        </div>
                        <div class="card-buttons">
                            <button class="card-btn" onclick="showPresentation('van', 'van-hoc')">Xem bài</button>
                        </div>
                    </div>
                </div>

                <div class="card">
                    <div class="card-header">
                        <h3>Vật lý - Cơ học</h3>
                    </div>
                    <div class="card-body">
                        <div class="card-content">
                            <p>Tìm hiểu các định luật về chuyển động và lực trong cơ học cổ điển.</p>
                        </div>
                        <div class="card-buttons">
                            <button class="card-btn" onclick="showPresentation('vat-ly', 'co-hoc')">Xem bài</button>
                        </div>
                    </div>
                </div>
            </div>

            <!-- Khu vực hiển thị nội dung thuyết trình -->
            <div id="presentation-area" class="presentation-content">
                <div class="section-nav">
                    <button class="section-btn active" onclick="showSection('mo-bai')">Mở bài</button>
                    <button class="section-btn" onclick="showSection('than-bai')">Thân bài</button>
                    <button class="section-btn" onclick="showSection('ket-bai')">Kết bài</button>
                </div>

                <div id="mo-bai" class="section-content active">
                    <h3>Phần mở bài</h3>
                    <p>Nội dung mở bài sẽ được hiển thị ở đây. Phần này giới thiệu tổng quan về chủ đề và mục tiêu của bài thuyết trình.</p>
                </div>

                <div id="than-bai" class="section-content">
                    <h3>Phần thân bài</h3>
                    <p>Nội dung thân bài sẽ được hiển thị ở đây. Phần này trình bày chi tiết các nội dung chính của bài thuyết trình, bao gồm các luận điểm và dẫn chứng.</p>
                </div>

                <div id="ket-bai" class="section-content">
                    <h3>Phần kết bài</h3>
                    <p>Nội dung kết bài sẽ được hiển thị ở đây. Phần này tóm tắt lại các điểm chính và đưa ra kết luận cho bài thuyết trình.</p>
                </div>
            </div>
        </div>
    </div>

    <script>
        // Tạo các ngôi sao
        function createStars() {
            const starsContainer = document.getElementById('stars');
            const starsCount = 150;
            
            for (let i = 0; i < starsCount; i++) {
                const star = document.createElement('div');
                star.classList.add('star');
                
                // Kích thước ngẫu nhiên
                const size = Math.random() * 3;
                star.style.width = `${size}px`;
                star.style.height = `${size}px`;
                
                // Vị trí ngẫu nhiên
                star.style.top = `${Math.random() * 100}%`;
                star.style.left = `${Math.random() * 100}%`;
                
                // Tốc độ nhấp nháy ngẫu nhiên
                star.style.animationDelay = `${Math.random() * 5}s`;
                
                starsContainer.appendChild(star);
            }
        }
        
        // Mở/đóng submenu
        function toggleSubmenu(element) {
            const submenu = element.nextElementSibling;
            const icon = element.querySelector('i.fa-chevron-down');
            
            if (submenu.classList.contains('open')) {
                submenu.classList.remove('open');
                icon.style.transform = 'rotate(0deg)';
            } else {
                // Đóng tất cả các submenu khác
                document.querySelectorAll('.submenu.open').forEach(item => {
                    if (item !== submenu) {
                        item.classList.remove('open');
                        item.previousElementSibling.querySelector('i.fa-chevron-down').style.transform = 'rotate(0deg)';
                    }
                });
                
                submenu.classList.add('open');
                icon.style.transform = 'rotate(180deg)';
            }
        }
        
        // Hiển thị bài thuyết trình
        function showPresentation(subject, topic) {
            const presentationArea = document.getElementById('presentation-area');
            presentationArea.classList.add('active');
            
            // Ẩn tất cả các section
            document.querySelectorAll('.section-content').forEach(section => {
                section.classList.remove('active');
            });
            
            // Hiển thị section đầu tiên
            document.getElementById('mo-bai').classList.add('active');
            
            // Reset các nút section
            document.querySelectorAll('.section-btn').forEach(btn => {
                btn.classList.remove('active');
            });
            document.querySelector('.section-btn').classList.add('active');
            
            // Cuộn đến khu vực thuyết trình
            presentationArea.scrollIntoView({ behavior: 'smooth' });
            
            // Cập nhật nội dung dựa trên môn và chủ đề
            updatePresentationContent(subject, topic);
        }
        
        // Hiển thị section cụ thể
        function showSection(sectionId) {
            // Ẩn tất cả các section
            document.querySelectorAll('.section-content').forEach(section => {
                section.classList.remove('active');
            });
            
            // Hiển thị section được chọn
            document.getElementById(sectionId).classList.add('active');
            
            // Cập nhật trạng thái nút
            document.querySelectorAll('.section-btn').forEach(btn => {
                btn.classList.remove('active');
            });
            event.target.classList.add('active');
        }
        
        // Cập nhật nội dung bài thuyết trình
        function updatePresentationContent(subject, topic) {
            // Đây là nơi bạn sẽ tải nội dung từ server hoặc từ một nguồn dữ liệu
            // Ở đây chúng ta chỉ cập nhật tiêu đề làm ví dụ
            const subjectNames = {
                'toan': 'Toán học',
                'van': 'Ngữ văn',
                'ngoai-ngu': 'Ngoại ngữ',
                'vat-ly': 'Vật lý',
                'sinh-hoc': 'Sinh học',
                'lich-su': 'Lịch sử',
                'dia-ly': 'Địa lý',
                'hoa-hoc': 'Hóa học',
                'tin-hoc': 'Tin học'
            };
            
            const topicNames = {
                'hinh-hoc': 'Hình học',
                'dai-so': 'Đại số',
                'thong-ke': 'Thống kê',
                'van-hoc': 'Văn học',
                'ngu-phap': 'Ngữ pháp',
                'lam-van': 'Làm văn',
                'tu-vung': 'Từ vựng',
                'giao-tiep': 'Giao tiếp',
                'co-hoc': 'Cơ học',
                'quang-hoc': 'Quang học',
                'dien-hoc': 'Điện học',
                'te-bao': 'Tế bào',
                'di-truyen': 'Di truyền',
                'sinh-thai': 'Sinh thái',
                'co-dai': 'Cổ đại',
                'trung-dai': 'Trung đại',
                'hien-dai': 'Hiện đại',
                'tu-nhien': 'Tự nhiên',
                'kinh-te': 'Kinh tế',
                'dan-cu': 'Dân cư',
                'vo-co': 'Hóa vô cơ',
                'huu-co': 'Hóa hữu cơ',
                'phan-ung': 'Phản ứng hóa học',
                'lap-trinh': 'Lập trình',
                'csdl': 'Cơ sở dữ liệu',
                'mang-may-tinh': 'Mạng máy tính'
            };
            
            const titles = {
                'mo-bai': `Mở bài: ${topicNames[topic]} trong ${subjectNames[subject]}`,
                'than-bai': `Thân bài: ${topicNames[topic]} trong ${subjectNames[subject]}`,
                'ket-bai': `Kết bài: ${topicNames[topic]} trong ${subjectNames[subject]}`
            };
            
            for (const section in titles) {
                const header = document.querySelector(`#${section} h3`);
                if (header) {
                    header.textContent = titles[section];
                }
            }
        }
        
        // Khởi tạo khi trang được tải
        window.onload = function() {
            createStars();
        };
    </script>
</body>
</html>
    )";
}

int main() {
    // Tạo file HTML
    std::ofstream htmlFile("index.html");
    if (htmlFile.is_open()) {
        htmlFile << generateHTML();
        htmlFile.close();
        std::cout << "File HTML đã được tạo thành công: index.html" << std::endl;
    } else {
        std::cerr << "Không thể tạo file HTML!" << std::endl;
        return 1;
    }

    // Mở file HTML trong trình duyệt mặc định
    #ifdef _WIN32
        system("start index.html");
    #elif __APPLE__
        system("open index.html");
    #else
        system("xdg-open index.html");
    #endif

    std::cout << "Trang web đang được mở trong trình duyệt..." << std::endl;

    return 0;
}