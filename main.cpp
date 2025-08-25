#include "crow.h"

int main() {
    crow::SimpleApp app;

    // ==================== TRANG CHỦ ====================
    CROW_ROUTE(app, "/")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>8A2 - Bài Thuyết Trình</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }
        body { display: flex; min-height: 100vh; background: radial-gradient(circle at 85% 15%, rgba(224, 247, 255, 0.8) 0%, transparent 25%), radial-gradient(circle at 15% 85%, rgba(200, 230, 255, 0.4) 0%, transparent 25%), linear-gradient(135deg, #000000 0%, #0a0a2a 30%, #1a1a4a 70%, #2c2c6e 100%); position: relative; overflow-x: hidden; color: #e6e6ff; }
        .moon { position: fixed; top: 80px; right: 80px; width: 120px; height: 120px; background: radial-gradient(circle, #e6f0ff 0%, #b3d9ff 30%, #99ccff 70%); border-radius: 50%; box-shadow: 0 0 60px rgba(179, 217, 255, 0.8), 0 0 100px rgba(179, 217, 255, 0.4), 0 0 150px rgba(179, 217, 255, 0.2); z-index: 1; animation: glow 3s ease-in-out infinite alternate; }
        @keyframes glow { from { box-shadow: 0 0 60px rgba(179, 217, 255, 0.8); } to { box-shadow: 0 0 80px rgba(179, 217, 255, 1); } }
        .star { position: absolute; background: white; border-radius: 50%; animation: twinkle 5s infinite; }
        @keyframes twinkle { 0%, 100% { opacity: 0.3; } 50% { opacity: 1; } }
        .sidebar { width: 280px; background: rgba(10, 10, 30, 0.9); color: white; padding: 25px 15px; position: fixed; height: 100vh; overflow-y: auto; z-index: 2; border-right: 1px solid rgba(100, 150, 255, 0.2); backdrop-filter: blur(10px); box-shadow: 5px 0 15px rgba(0, 0, 0, 0.5); }
        .sidebar h2 { text-align: center; margin-bottom: 30px; color: #99ccff; text-shadow: 0 0 15px rgba(153, 204, 255, 0.7); font-size: 1.8rem; padding-bottom: 15px; border-bottom: 1px solid rgba(100, 150, 255, 0.3); }
        .subject-title { padding: 12px 15px; margin: 15px 0 5px 0; background: rgba(30, 50, 100, 0.5); border-radius: 8px; cursor: pointer; transition: all 0.3s ease; border-left: 4px solid #99ccff; font-weight: bold; color: #b3d9ff; display: flex; justify-content: space-between; align-items: center; }
        .subject-title:hover { background: rgba(50, 80, 150, 0.5); transform: translateX(5px); }
        .submenu { padding-left: 20px; max-height: 0; overflow: hidden; transition: max-height 0.5s ease; }
        .submenu.open { max-height: 500px; }
        .menu-item { padding: 12px 15px; margin: 8px 0; background: rgba(255, 255, 255, 0.1); border-radius: 6px; cursor: pointer; transition: all 0.3s ease; border: 1px solid rgba(255, 255, 255, 0.1); text-decoration: none; color: #ccddff; display: block; font-size: 0.95rem; }
        .menu-item:hover { background: rgba(153, 204, 255, 0.3); transform: translateX(5px); box-shadow: 0 0 15px rgba(153, 204, 255, 0.4); color: #e6f0ff; }
        .content { flex: 1; margin-left: 280px; padding: 40px; position: relative; z-index: 1; }
        .header { text-align: center; margin-bottom: 40px; }
        .header h1 { font-size: 2.5rem; color: #99ccff; text-shadow: 0 0 20px rgba(153, 204, 255, 0.7); margin-bottom: 15px; }
        .header p { font-size: 1.2rem; color: #ccddff; max-width: 800px; margin: 0 auto; }
        .grid-container { display: grid; grid-template-columns: repeat(auto-fit, minmax(320px, 1fr)); gap: 30px; padding: 20px; }
        .card { background: rgba(30, 30, 60, 0.7); padding: 25px; border-radius: 15px; box-shadow: 0 8px 25px rgba(0, 0, 0, 0.3); transition: all 0.5s ease; cursor: pointer; text-align: center; border: 1px solid rgba(100, 150, 255, 0.2); backdrop-filter: blur(10px); position: relative; overflow: hidden; }
        .card::before { content: ''; position: absolute; top: 0; left: 0; right: 0; height: 3px; background: linear-gradient(90deg, transparent, #99ccff, transparent); transform: translateX(-100%); transition: transform 0.5s ease; }
        .card:hover { transform: scale(1.08) translateY(-5px); box-shadow: 0 15px 40px rgba(0, 0, 0, 0.4), 0 0 30px rgba(153, 204, 255, 0.3); background: rgba(40, 40, 80, 0.9); }
        .card:hover::before { transform: translateX(100%); }
        .card-icon { font-size: 3rem; margin-bottom: 20px; color: #b3d9ff; text-shadow: 0 0 15px rgba(179, 217, 255, 0.5); }
        .card h3 { color: #b3d9ff; margin-bottom: 15px; font-size: 1.4rem; text-shadow: 0 0 10px rgba(179, 217, 255, 0.5); }
        .card p { color: #ccddff; line-height: 1.6; font-size: 1rem; }
        .card:nth-child(1) { transition-delay: 0.1s; }
        .card:nth-child(2) { transition-delay: 0.2s; }
        .card:nth-child(3) { transition-delay: 0.3s; }
        .card:nth-child(4) { transition-delay: 0.4s; }
        @media (max-width: 968px) { .sidebar { width: 220px; padding: 20px 10px; } .content { margin-left: 220px; padding: 30px; } }
        @media (max-width: 768px) { .sidebar { width: 100%; height: auto; position: relative; margin-bottom: 20px; max-height: 400px; overflow-y: auto; } .content { margin-left: 0; padding: 20px; } .moon { top: 20px; right: 20px; width: 80px; height: 80px; } .header h1 { font-size: 2rem; } .grid-container { grid-template-columns: 1fr; } }
    </style>
</head>
<body>
    <div class="moon"></div>
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
        document.addEventListener('DOMContentLoaded', function() {
            const subjectTitles = document.querySelectorAll('.subject-title');
            subjectTitles.forEach(title => {
                title.addEventListener('click', function() {
                    const submenu = this.nextElementSibling;
                    submenu.classList.toggle('open');
                    const icon = this.querySelector('span');
                    if (submenu.classList.contains('open')) {
                        icon.textContent = '▼';
                    } else {
                        icon.textContent = '►';
                    }
                });
            });
        });
    </script>

    <div class="sidebar">
        <h2>8A2 Presentation</h2>
        <div class="subject-title">Môn Toán <span>►</span></div>
        <div class="submenu">
            <a href="/toan-daiso" class="menu-item">Đại số - Phương trình bậc hai</a>
            <a href="/toan-hinhhoc" class="menu-item">Hình học - Định lý Pythagoras</a>
            <a href="/toan-thongke" class="menu-item">Thống kê - Phân tích dữ liệu</a>
        </div>
        <div class="subject-title">Môn Ngữ Văn <span>►</span></div>
        <div class="submenu">
            <a href="/nguvan-tacpham" class="menu-item">Phân tích tác phẩm văn học</a>
            <a href="/nguvan-tholucbat" class="menu-item">Thơ lục bát Việt Nam</a>
            <a href="/nguvan-vantuluan" class="menu-item">Kỹ năng viết văn tự sự</a>
        </div>
        <div class="subject-title">Môn Ngoại ngữ <span>►</span></div>
        <div class="submenu">
            <a href="/ngoaingu-nguphap" class="menu-item">Ngữ pháp - Thì hiện tại hoàn thành</a>
            <a href="/ngoaingu-giaotiep" class="menu-item">Giao tiếp hàng ngày</a>
            <a href="/ngoaingu-vietluan" class="menu-item">Kỹ năng viết luận</a>
        </div>
        <div class="subject-title">Môn Vật Lý <span>►</span></div>
        <div class="submenu">
            <a href="/vatly-cohoc" class="menu-item">Cơ học - Chuyển động</a>
            <a href="/vatly-quanghoc" class="menu-item">Quang học - Khúc xạ ánh sáng</a>
<a href="/vatly-dien" class="menu-item">Điện học - Mạch điện</a>
</div>
<div class="subject-title">Môn Hóa học <span>►</span></div>
<div class="submenu">
<a href="/hoahoc-voco" class="menu-item">Hóa vô cơ - Phản ứng oxi hóa khử</a>
<a href="/hoahoc-huuco" class="menu-item">Hóa hữu cơ - Hydrocarbon</a>
<a href="/hoahoc-phuongphap" class="menu-item">Phương pháp giải bài tập Hóa học</a>
</div>
<div class="subject-title">Môn Sinh học <span>►</span></div>
<div class="submenu">
<a href="/sinhhoc-tebao" class="menu-item">Tế bào - Cấu trúc và chức năng</a>
<a href="/sinhhoc-ditruyen" class="menu-item">Di truyền học - ADN và gen</a>
<a href="/sinhhoc-sinhthai" class="menu-item">Hệ sinh thái - Môi trường</a>
</div>
<div class="subject-title">Môn Lịch sử <span>►</span></div>
<div class="submenu">
<a href="/lichsu-vietnam" class="menu-item">Lịch sử Việt Nam thế kỷ 20</a>
<a href="/lichsu-thegioi" class="menu-item">Chiến tranh thế giới thứ hai</a>
<a href="/lichsu-vanhoadong" class="menu-item">Văn hóa Đông Sơn</a>
</div>
<div class="subject-title">Môn Địa lý <span>►</span></div>
<div class="submenu">
<a href="/dialy-diali" class="menu-item">Địa lý tự nhiên Việt Nam</a>
<a href="/dialy-dancu" class="menu-item">Địa lý dân cư và kinh tế</a>
<a href="/dialy-moitruong" class="menu-item">Địa lý môi trường và tài nguyên</a>
</div>
<div class="subject-title">Môn GDCD <span>►</span></div>
<div class="submenu">
<a href="/gdcd-daoduc" class="menu-item">Giáo dục đạo đức và nhân cách</a>
<a href="/gdcd-phapluat" class="menu-item">Hiến pháp và pháp luật Việt Nam</a>
<a href="/gdcd-congdan" class="menu-item">Quyền và nghĩa vụ công dân</a>
</div>
</div>
<div class="content">
    <div class="header">
        <h1>Chào mừng đến lớp 8A2</h1>
        <p>Hệ thống bài thuyết trình của lớp với giao diện không gian hiện đại</p>
    </div>
    
    <div class="grid-container">
        <div class="card">
            <div class="card-icon">📐</div>
            <h3>Môn Toán</h3>
            <p>Các bài thuyết trình về đại số, hình học và thống kê</p>
        </div>
        
        <div class="card">
            <div class="card-icon">📖</div>
            <h3>Môn Ngữ Văn</h3>
            <p>Phân tích tác phẩm văn học và kỹ năng viết luận</p>
        </div>
        
        <div class="card">
            <div class="card-icon">🌍</div>
            <h3>Môn Ngoại ngữ</h3>
            <p>Nâng cao kỹ năng ngôn ngữ toàn cầu</p>
        </div>
        
        <div class="card">
            <div class="card-icon">🔭</div>
            <h3>Môn Vật Lý</h3>
            <p>Khám phá các hiện tượng tự nhiên và định luật vật lý</p>
        </div>
        
        <div class="card">
            <div class="card-icon">🧪</div>
            <h3>Môn Hóa học</h3>
            <p>Thí nghiệm và phản ứng hóa học thú vị</p>
        </div>
        
        <div class="card">
            <div class="card-icon">🔬</div>
            <h3>Môn Sinh học</h3>
            <p>Tìm hiểu về thế giới sinh vật và cơ thể sống</p>
        </div>
        
        <div class="card">
            <div class="card-icon">📜</div>
            <h3>Môn Lịch sử</h3>
            <p>Hành trình qua các giai đoạn lịch sử quan trọng</p>
        </div>
        
        <div class="card">
            <div class="card-icon">🗺️</div>
            <h3>Môn Địa lý</h3>
            <p>Khám phá Trái Đất và các hiện tượng địa lý</p>
        </div>
        
        <div class="card">
            <div class="card-icon">⚖️</div>
            <h3>Môn GDCD</h3>
            <p>Giáo dục công dân và phát triển nhân cách</p>
        </div>
    </div>
</div>
</body> </html> )"; return page; });
// ==================== TRANG MÔN TOÁN ====================
CROW_ROUTE(app, "/toan-daiso")([](){
    auto page = R"(
<!DOCTYPE html><html lang="vi"> <head> <meta charset="UTF-8"> <meta name="viewport" content="width=device-width, initial-scale=1.0"> <title>Toán Đại Số - 8A2</title> <style> * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; } body { background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%); color: white; padding: 40px; min-height: 100vh; } .container { max-width: 1000px; margin: 0 auto; background: rgba(30, 30, 60, 0.8); padding: 40px; border-radius: 15px; border: 1px solid rgba(255, 255, 255, 0.1); backdrop-filter: blur(10px); } h1 { color: #99ccff; margin-bottom: 30px; text-align: center; text-shadow: 0 0 15px rgba(153, 204, 255, 0.7); } .back-btn { display: inline-block; background: rgba(153, 204, 255, 0.3); color: white; padding: 10px 20px; border-radius: 8px; text-decoration: none; margin-bottom: 20px; transition: all 0.3s ease; } .back-btn:hover { background: rgba(153, 204, 255, 0.5); transform: translateX(-5px); } .content-section { margin: 30px 0; padding: 20px; background: rgba(40, 40, 80, 0.5); border-radius: 10px; border-left: 4px solid #99ccff; } .content-section h2 { color: #b3d9ff; margin-bottom: 15px; } .content-section p { line-height: 1.6; color: #ccddff; } .content-section ul { padding-left: 20px; color: #ccddff; line-height: 1.6; } .content-section li { margin-bottom: 10px; } </style> </head> <body> <div class="container"> <a href="/" class="back-btn">← Quay lại Trang Chủ</a> <h1>Toán Đại Số - Phương trình bậc hai</h1>
 <div class="content-section">
        <h2>Giới thiệu chung</h2>
        <p>Phương trình bậc hai là phương trình có dạng ax² + bx + c = 0, trong đó x là ẩn số, a, b, c là các hệ số với a ≠ 0.</p>
    </div>
    
    <div class="content-section">
        <h2>Công thức nghiệm</h2>
        <p>Để giải phương trình bậc hai, chúng ta sử dụng công thức nghiệm: x = [-b ± √(b² - 4ac)] / (2a)</p>
        <p>Biệt thức Δ = b² - 4ac quyết định số nghiệm của phương trình:</p>
        <ul>
            <li>Δ > 0: Phương trình có 2 nghiệm phân biệt</li>
            <li>Δ = 0: Phương trình có nghiệm kép</li>
            <li>Δ < 0: Phương trình vô nghiệm</li>
        </ul>
    </div>
    
    <div class="content-section">
        <h2>Ứng dụng thực tế</h2>
        <p>Phương trình bậc hai được ứng dụng trong nhiều lĩnh vực như vật lý, kỹ thuật, kinh tế và khoa học máy tính.</p>
    </div>
    
    <div class="content-section">
        <h2>Ví dụ minh họa</h2>
        <p>Giải phương trình: x² - 5x + 6 = 0</p>
        <p>Ta có: a = 1, b = -5, c = 6</p>
        <p>Δ = b² - 4ac = (-5)² - 4×1×6 = 25 - 24 = 1 > 0</p>
        <p>Phương trình có 2 nghiệm phân biệt:</p>
        <p>x₁ = [5 + √1] / 2 = 3</p>
        <p>x₂ = [5 - √1] / 2 = 2</p>
    </div>
</div>
</body> </html> )"; return page; });
// ==================== TRANG MÔN NGỮ VĂN ====================
CROW_ROUTE(app, "/nguvan-tacpham")([](){
    auto page = R"(
<!DOCTYPE html><html lang="vi"> <head> <meta charset="UTF-8"> <meta name="viewport" content="width=device-width, initial-scale=1.0"> <title>Ngữ Văn - 8A2</title> <style> * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; } body { background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%); color: white; padding: 40px; min-height: 100vh; } .container { max-width: 1000px; margin: 0 auto; background: rgba(30, 30, 60, 0.8); padding: 40px; border-radius: 15px; border: 1
        .container { max-width: 1000px; margin: 0 auto; background: rgba(30, 30, 60, 0.8); padding: 40px; border-radius: 15px; border: 1px solid rgba(255, 255, 255, 0.1); backdrop-filter: blur(10px); }
        h1 { color: #99ccff; margin-bottom: 30px; text-align: center; text-shadow: 0 0 15px rgba(153, 204, 255, 0.7); }
        .back-btn { display: inline-block; background: rgba(153, 204, 255, 0.3); color: white; padding: 10px 20px; border-radius: 8px; text-decoration: none; margin-bottom: 20px; transition: all 0.3s ease; }
        .back-btn:hover { background: rgba(153, 204, 255, 0.5); transform: translateX(-5px); }
        .content-section { margin: 30px 0; padding: 20px; background: rgba(40, 40, 80, 0.5); border-radius: 10px; border-left: 4px solid #99ccff; }
        .content-section h2 { color: #b3d9ff; margin-bottom: 15px; }
        .content-section p { line-height: 1.6; color: #ccddff; }
        .content-section ul { padding-left: 20px; color: #ccddff; line-height: 1.6; }
        .content-section li { margin-bottom: 10px; }
        .quote { font-style: italic; padding: 15px; border-left: 3px solid #99ccff; margin: 15px 0; background: rgba(153, 204, 255, 0.1); border-radius: 0 8px 8px 0; }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Ngữ Văn - Phân tích tác phẩm văn học</h1>
        
        <div class="content-section">
            <h2>Giới thiệu chung</h2>
            <p>Phân tích tác phẩm văn học là quá trình tìm hiểu, đánh giá và cảm thụ các giá trị nội dung và nghệ thuật của tác phẩm.</p>
        </div>
        
        <div class="content-section">
            <h2>Phương pháp phân tích</h2>
            <p>Để phân tích tác phẩm văn học, cần chú ý đến:</p>
            <ul>
                <li>Hoàn cảnh sáng tác và bối cảnh lịch sử</li>
                <li>Nội dung tư tưởng và chủ đề tác phẩm</li>
                <li>Nghệ thuật xây dựng nhân vật và tình huống</li>
                <li>Giá trị nhân văn và thông điệp tác giả muốn truyền tải</li>
                <li>Ngôn ngữ và biện pháp tu từ được sử dụng</li>
            </ul>
        </div>
        
        <div class="content-section">
            <h2>Ví dụ minh họa: Phân tích tác phẩm "Lão Hạc" của Nam Cao</h2>
            <p>"Lão Hạc" là một trong những truyện ngắn xuất sắc của Nam Cao, viết về đề tài người nông dân Việt Nam trước Cách mạng tháng Tám.</p>
            
            <div class="quote">
                "Lão Hạc là một người cha hết lòng thương con, một người nông dân chất phác, giàu lòng tự trọng."
            </div>
            
            <p>Tác phẩm thể hiện:</p>
            <ul>
                <li>Tấn bi kịch của người nông dân nghèo trong xã hội cũ</li>
                <li>Vẻ đẹp tâm hồn và nhân cách cao quý của Lão Hạc</li>
                <li>Giá trị nhân đạo sâu sắc qua cách nhìn của tác giả</li>
            </ul>
        </div>
        
        <div class="content-section">
            <h2>Kết luận</h2>
            <p>Phân tích tác phẩm văn học giúp chúng ta hiểu sâu sắc hơn về giá trị của tác phẩm, đồng thời rèn luyện kỹ năng cảm thụ và phân tích văn học.</p>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== CÁC TRANG KHÁC ====================
    // (Thêm các route khác với cấu trúc tương tự cho các môn học còn lại)

    app.port(10000).multithreaded().run();
}