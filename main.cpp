#include "crow.h"

int main()
{
    crow::SimpleApp app;

    // ==================== TRANG CHỦ ====================
    CROW_ROUTE(app, "/")([](){
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bài Thuyết Trình - Web C++</title>
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
            text-decoration: none;
            color: white;
            display: block;
            text-align: center;
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
        
        /* Responsive */
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
        <h2>🌙 Bài Thuyết Trình</h2>
        <a href="/" class="menu-item">🏠 Trang Chủ</a>
        <a href="/phan1" class="menu-item">📊 Phần 1: Giới Thiệu</a>
        <a href="/phan2" class="menu-item">🔧 Phần 2: Công Nghệ</a>
        <a href="/phan3" class="menu-item">🚀 Phần 3: Demo</a>
        <a href="/phan4" class="menu-item">🎯 Phần 4: Kết Luận</a>
        <a href="/lienhe" class="menu-item">📞 Liên Hệ</a>
    </div>

    <!-- Main Content -->
    <div class="content">
        <div class="grid-container">
            <div class="card">
                <h3>Chào mừng đến Bài Thuyết Trình</h3>
                <p>Ứng dụng web server viết bằng C++ với Crow framework</p>
            </div>
            
            <div class="card">
                <h3>Mục Tiêu</h3>
                <p>Trình bày về khả năng lập trình web bằng ngôn ngữ C++</p>
            </div>
            
            <div class="card">
                <h3>Công Nghệ</h3>
                <p>Sử dụng Crow framework, Docker, và Render để deploy</p>
            </div>
            
            <div class="card">
                <h3>Đặc Điểm</h3>
                <p>Hiệu suất cao, giao diện hiện đại, responsive design</p>
            </div>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG PHẦN 1 ====================
    CROW_ROUTE(app, "/phan1")([](){
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Phần 1: Giới Thiệu</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%);
            color: white;
            padding: 40px;
            min-height: 100vh;
        }
        
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: rgba(30, 30, 60, 0.8);
            padding: 40px;
            border-radius: 15px;
            border: 1px solid rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
        }
        
        h1 {
            color: #99ccff;
            margin-bottom: 30px;
            text-align: center;
        }
        
        .back-btn {
            display: inline-block;
            background: rgba(153, 204, 255, 0.3);
            color: white;
            padding: 10px 20px;
            border-radius: 8px;
            text-decoration: none;
            margin-bottom: 20px;
            transition: all 0.3s ease;
        }
        
        .back-btn:hover {
            background: rgba(153, 204, 255, 0.5);
            transform: translateX(-5px);
        }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Phần 1: Giới Thiệu</h1>
        <p>Nội dung chi tiết cho phần giới thiệu bài thuyết trình...</p>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG PHẦN 2 ====================
    CROW_ROUTE(app, "/phan2")([](){
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Phần 2: Công Nghệ</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%);
            color: white;
            padding: 40px;
            min-height: 100vh;
        }
        
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: rgba(30, 30, 60, 0.8);
            padding: 40px;
            border-radius: 15px;
            border: 1px solid rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
        }
        
        h1 {
            color: #99ccff;
            margin-bottom: 30px;
            text-align: center;
        }
        
        .back-btn {
            display: inline-block;
            background: rgba(153, 204, 255, 0.3);
            color: white;
            padding: 10px 20px;
            border-radius: 8px;
            text-decoration: none;
            margin-bottom: 20px;
            transition: all 0.3s ease;
        }
        
        .back-btn:hover {
            background: rgba(153, 204, 255, 0.5);
            transform: translateX(-5px);
        }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Phần 2: Công Nghệ</h1>
        <p>Nội dung về các công nghệ sử dụng trong dự án...</p>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG PHẦN 3 ====================
    CROW_ROUTE(app, "/phan3")([](){
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Phần 3: Demo</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%);
            color: white;
            padding: 40px;
            min-height: 100vh;
        }
        
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: rgba(30, 30, 60, 0.8);
            padding: 40px;
            border-radius: 15px;
            border: 1px solid rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
        }
        
        h1 {
            color: #99ccff;
            margin-bottom: 30px;
            text-align: center;
        }
        
        .back-btn {
            display: inline-block;
            background: rgba(153, 204, 255, 0.3);
            color: white;
            padding: 10px 20px;
            border-radius: 8px;
            text-decoration: none;
            margin-bottom: 20px;
            transition: all 0.3s ease;
        }
        
        .back-btn:hover {
            background: rgba(153, 204, 255, 0.5);
            transform: translateX(-5px);
        }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Phần 3: Demo</h1>
        <p>Demo trực tiếp ứng dụng web server C++...</p>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG PHẦN 4 ====================
    CROW_ROUTE(app, "/phan4")([](){
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Phần 4: Kết Luận</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%);
            color: white;
            padding: 40px;
            min-height: 100vh;
        }
        
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: rgba(30, 30, 60, 0.8);
            padding: 40px;
            border-radius: 15px;
            border: 1px solid rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
        }
        
        h1 {
            color: #99ccff;
            margin-bottom: 30px;
            text-align: center;
        }
        
        .back-btn {
            display: inline-block;
            background: rgba(153, 204, 255, 0.3);
            color: white;
            padding: 10px 20px;
            border-radius: 8px;
            text-decoration: none;
            margin-bottom: 20px;
            transition: all 0.3s ease;
        }
        
        .back-btn:hover {
            background: rgba(153, 204, 255, 0.5);
            transform: translateX(-5px);
        }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Phần 4: Kết Luận</h1>
        <p>Kết luận và hướng phát triển tương lai...</p>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG LIÊN HỆ ====================
    CROW_ROUTE(app, "/lienhe")([](){
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Liên Hệ</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%);
            color: white;
            padding: 40px;
            min-height: 100vh;
        }
        
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: rgba(30, 30, 60, 0.8);
            padding: 40px;
            border-radius: 15px;
            border: 1px solid rgba(255, 255, 255, 0.1);
            backdrop-filter: blur(10px);
        }
        
        h1 {
            color: #99ccff;
            margin-bottom: 30px;
            text-align: center;
        }
        
        .back-btn {
            display: inline-block;
            background: rgba(153, 204, 255, 0.3);
            color: white;
            padding: 10px 20px;
            border-radius: 8px;
            text-decoration: none;
            margin-bottom: 20px;
            transition: all 0.3s ease;
        }
        
        .back-btn:hover {
            background: rgba(153, 204, 255, 0.5);
            transform: translateX(-5px);
        }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Liên Hệ</h1>
        <p>Thông tin liên hệ và hỗ trợ...</p>
    </div>
</body>
</html>
        )";
        return page;
    });

    app.port(10000).multithreaded().run();
}