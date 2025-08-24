#include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Server C++ by Huy</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            display: flex;
            min-height: 100vh;
            background: 
                radial-gradient(circle at 85% 15%, rgba(224, 247, 255, 0.8) 0%, transparent 25%),
                radial-gradient(circle at 15% 85%, rgba(200, 230, 255, 0.4) 0%, transparent 25%),
                linear-gradient(135deg, #000000 0%, #0a0a2a 30%, #1a1a4a 70%, #2c2c6e 100%);
            position: relative;
            overflow-x: hidden;
        }

        /* Hiệu ứng mặt trăng */
        .moon {
            position: fixed;
            top: 80px;
            right: 80px;
            width: 120px;
            height: 120px;
            background: radial-gradient(circle, #e6f0ff 0%, #b3d9ff 30%, #99ccff 70%);
            border-radius: 50%;
            box-shadow: 
                0 0 60px rgba(179, 217, 255, 0.8),
                0 0 100px rgba(179, 217, 255, 0.4),
                0 0 150px rgba(179, 217, 255, 0.2);
            z-index: 1;
            animation: glow 3s ease-in-out infinite alternate;
        }

        @keyframes glow {
            from { box-shadow: 0 0 60px rgba(179, 217, 255, 0.8); }
            to { box-shadow: 0 0 80px rgba(179, 217, 255, 1); }
        }

        /* Hiệu ứng ngôi sao */
        .star {
            position: absolute;
            background: white;
            border-radius: 50%;
            animation: twinkle 5s infinite;
        }

        @keyframes twinkle {
            0%, 100% { opacity: 0.3; }
            50% { opacity: 1; }
        }

        /* Sidebar Menu */
        .sidebar {
            width: 250px;
            background: rgba(0, 0, 0, 0.9);
            color: white;
            padding: 20px;
            position: fixed;
            height: 100vh;
            overflow-y: auto;
            z-index: 2;
            border-right: 1px solid rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
        }
        
        .sidebar h2 {
            text-align: center;
            margin-bottom: 30px;
            color: #99ccff;
            text-shadow: 0 0 10px rgba(153, 204, 255, 0.7);
            font-size: 1.5rem;
        }
        
        .menu-item {
            padding: 15px;
            margin: 10px 0;
            background: rgba(255, 255, 255, 0.1);
            border-radius: 8px;
            cursor: pointer;
            transition: all 0.3s ease;
            border: 1px solid rgba(255, 255, 255, 0.1);
        }
        
        .menu-item:hover {
            background: rgba(153, 204, 255, 0.3);
            transform: translateX(5px);
            box-shadow: 0 0 15px rgba(153, 204, 255, 0.4);
            color: #e6f0ff;
        }
        
        /* Main Content */
        .content {
            flex: 1;
            margin-left: 250px;
            padding: 40px;
            position: relative;
            z-index: 1;
        }
        
        .grid-container {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 30px;
            padding: 20px;
        }
        
        .card {
            background: rgba(30, 30, 60, 0.7);
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 8px 25px rgba(0, 0, 0, 0.3);
            transition: all 0.5s ease;
            cursor: pointer;
            text-align: center;
            border: 1px solid rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
            position: relative;
            overflow: hidden;
        }
        
        .card::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            right: 0;
            height: 3px;
            background: linear-gradient(90deg, transparent, #99ccff, transparent);
            transform: translateX(-100%);
            transition: transform 0.5s ease;
        }
        
        .card:hover {
            transform: scale(1.08) translateY(-5px);
            box-shadow: 
                0 15px 40px rgba(0, 0, 0, 0.4),
                0 0 30px rgba(153, 204, 255, 0.3);
            background: rgba(40, 40, 80, 0.9);
        }
        
        .card:hover::before {
            transform: translateX(100%);
        }
        
        .card h3 {
            color: #b3d9ff;
            margin-bottom: 15px;
            font-size: 1.4rem;
            text-shadow: 0 0 10px rgba(179, 217, 255, 0.5);
        }
        
        .card p {
            color: #ccddff;
            line-height: 1.6;
            font-size: 1rem;
        }
        
        /* Hiệu ứng khoảng cách với mặt trăng */
        .card:nth-child(1) { transition-delay: 0.1s; }
        .card:nth-child(2) { transition-delay: 0.2s; }
        .card:nth-child(3) { transition-delay: 0.3s; }
        .card:nth-child(4) { transition-delay: 0.4s; }
        .card:nth-child(5) { transition-delay: 0.5s; }
        .card:nth-child(6) { transition-delay: 0.6s; }
        
        /* Responsive */
        @media (max-width: 968px) {
            .grid-container {
                grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
                gap: 20px;
            }
        }
        
        @media (max-width: 768px) {
            .sidebar {
                width: 100%;
                height: auto;
                position: relative;
                margin-bottom: 20px;
            }
            
            .content {
                margin-left: 0;
                padding: 20px;
            }
            
            .moon {
                top: 20px;
                right: 20px;
                width: 80px;
                height: 80px;
            }
        }
    </style>
</head>
<body>
    <!-- Hiệu ứng mặt trăng -->
    <div class="moon"></div>
    
    <!-- Hiệu ứng ngôi sao -->
    <script>
        // Tạo ngôi sao ngẫu nhiên
        for (let i = 0; i < 50; i++) {
            const star = document.createElement('div');
            star.className = 'star';
            star.style.width = Math.random() * 3 + 'px';
            star.style.height = star.style.width;
            star.style.left = Math.random() * 100 + '%';
            star.style.top = Math.random() * 100 + '%';
            star.style.animationDelay = Math.random() * 5 + 's';
            document.body.appendChild(star);
        }
    </script>

    <!-- Sidebar Menu -->
    <div class="sidebar">
        <h2>🌙 Menu Chính</h2>
        <div class="menu-item">🚀 Trang Chủ</div>
        <div class="menu-item">⭐ Dịch Vụ</div>
        <div class="menu-item">✨ Sản Phẩm</div>
        <div class="menu-item">🌌 Giới Thiệu</div>
        <div class="menu-item">📞 Liên Hệ</div>
    </div>

    <!-- Main Content -->
    <div class="content">
        <div class="grid-container">
            <!-- Card 1 -->
            <div class="card">
                <h3>Mục 1</h3>
                <p>Nội dung mô tả cho mục thứ nhất. Đây là nội dung chi tiết về sản phẩm/dịch vụ.</p>
            </div>
            
            <!-- Card 2 -->
            <div class="card">
                <h3>Mục 2</h3>
                <p>Nội dung mô tả cho mục thứ hai. Đây là nội dung chi tiết về sản phẩm/dịch vụ.</p>
            </div>
            
            <!-- Card 3 -->
            <div class="card">
                <h3>Mục 3</h3>
                <p>Nội dung mô tả cho mục thứ ba. Đây là nội dung chi tiết về sản phẩm/dịch vụ.</p>
            </div>
            
            <!-- Card 4 -->
            <div class="card">
                <h3>Mục 4</h3>
                <p>Nội dung mô tả cho mục thứ tư. Đây là nội dung chi tiết về sản phẩm/dịch vụ.</p>
            </div>

            <!-- Card 5 -->
            <div class="card">
                <h3>Mục 5</h3>
                <p>Nội dung mô tả cho mục thứ năm. Đây là nội dung chi tiết về sản phẩm/dịch vụ.</p>
            </div>
            
            <!-- Card 6 -->
            <div class="card">
                <h3>Mục 6</h3>
                <p>Nội dung mô tả cho mục thứ sáu. Đây là nội dung chi tiết về sản phẩm/dịch vụ.</p>
            </div>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // Chạy server trên port 10000
    app.port(10000).multithreaded().run();
}