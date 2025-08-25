#include "crow.h"
#include <vector>
#include <map>
#include <string>

int main() {
    crow::SimpleApp app;
        // ==================== TRANG CHỦ ====================
    CROW_ROUTE(app, "/")([]() {
        auto page = R"(...)"; // Giữ nguyên nội dung HTML của trang chủ
        return page;
    });
     // ==================== TRANG MÔN TOÁN ====================
    CROW_ROUTE(app, "/toan-daiso")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Toán Đại Số - 8A2</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }
        body { background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%); color: white; padding: 40px; min-height: 100vh; }
        .container { max-width: 1000px; margin: 0 auto; background: rgba(30, 30, 60, 0.8); padding: 40px; border-radius: 15px; border: 1px solid rgba(255, 255, 255, 0.1); backdrop-filter: blur(10px); }
        h1 { color: #99ccff; margin-bottom: 30px; text-align: center; text-shadow: 0 0 15px rgba(153, 204, 255, 0.7); }
        .back-btn { display: inline-block; background: rgba(153, 204, 255, 0.3); color: white; padding: 10px 20px; border-radius: 8px; text-decoration: none; margin-bottom: 20px; transition: all 0.3s ease; }
        .back-btn:hover { background: rgba(153, 204, 255, 0.5); transform: translateX(-5px); }
        .content-section { margin: 30px 0; padding: 20px; background: rgba(40, 40, 80, 0.5); border-radius: 10px; border-left: 4px solid #99ccff; }
        .content-section h2 { color: #b3d9ff; margin-bottom: 15px; }
        .content-section p { line-height: 1.6; color: #ccddff; }
        .content-section ul { padding-left: 20px; color: #ccddff; line-height: 1.6; }
        .content-section li { margin-bottom: 10px; }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Toán Đại Số - Phương trình bậc hai</h1>
        
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
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG MÔN NGỮ VĂN ====================
    CROW_ROUTE(app, "/nguvan-tacpham")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ngữ Văn - 8A2</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }
        body { background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%); color: white; padding: 40px; min-height: 100vh; }
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
                <li>Ngôn ngữ và biện pháp tu từ được sử</li>
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

    // ==================== TRANG MÔN VẬT LÝ ====================
    CROW_ROUTE(app, "/vatly-cohoc")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Vật Lý - 8A2</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }
        body { background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%); color: white; padding: 40px; min-height: 100vh; }
        .container { max-width: 1000px; margin: 0 auto; background: rgba(30, 30, 60, 0.8); padding: 40px; border-radius: 15px; border: 1px solid rgba(255, 255, 255, 0.1); backdrop-filter: blur(10px); }
        h1 { color: #99ccff; margin-bottom: 30px; text-align: center; text-shadow: 0 0 15px rgba(153, 204, 255, 0.7); }
        .back-btn { display: inline-block; background: rgba(153, 204, 255, 0.3); color: white; padding: 10px 20px; border-radius: 8px; text-decoration: none; margin-bottom: 20px; transition: all 0.3s ease; }
        .back-btn:hover { background: rgba(153, 204, 255, 0.5); transform: translateX(-5px); }
        .content-section { margin: 30px 0; padding: 20px; background: rgba(40, 40, 80, 0.5); border-radius: 10px; border-left: 4px solid #99ccff; }
        .content-section h2 { color: #b3d9ff; margin-bottom: 15px; }
        .content-section p { line-height: 1.6; color: #ccddff; }
        .content-section ul { padding-left: 20px; color: #ccddff; line-height: 1.6; }
        .content-section li { margin-bottom: 10px; }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Vật Lý - Cơ học Chuyển động</h1>
        
        <div class="content-section">
            <h2>Giới thiệu chung</h2>
            <p>Cơ học là ngành khoa học nghiên cứu về chuyển động của các vật thể và các lực tác động lên chúng.</p>
        </div>
        
        <div class="content-section">
            <h2>Các khái niệm cơ bản</h2>
            <ul>
                <li>Chuyển động thẳng đều</li>
                <li>Chuyển động thẳng biến đổi đều</li>
                <li>Lực và các định luật Newton</li>
                <li>Công và năng lượng</li>
            </ul>
        </div>
        
        <div class="content-section">
            <h2>Ứng dụng thực tế</h2>
            <p>Kiến thức về cơ học được ứng dụng trong nhiều lĩnh vực như xây dựng, giao thông vận tải, và công nghệ hàng không.</p>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG MÔN HÓA HỌC ====================
    CROW_ROUTE(app, "/hoahoc-voco")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hóa Học - 8A2</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }
        body { background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%); color: white; padding: 40px; min-height: 100vh; }
        .container { max-width: 1000px; margin: 0 auto; background: rgba(30, 30, 60, 0.8); padding: 40px; border-radius: 15px; border: 1px solid rgba(255, 255, 255, 0.1); backdrop-filter: blur(10px); }
        h1 { color: #99ccff; margin-bottom: 30px; text-align: center; text-shadow: 0 0 15px rgba(153, 204, 255, 0.7); }
        .back-btn { display: inline-block; background: rgba(153, 204, 255, 0.3); color: white; padding: 10px 20px; border-radius: 8px; text-decoration: none; margin-bottom: 20px; transition: all 0.3s ease; }
        .back-btn:hover { background: rgba(153, 204, 255, 0.5); transform: translateX(-5px); }
        .content-section { margin: 30px 0; padding: 20px; background: rgba(40, 40, 80, 0.5); border-radius: 10px; border-left: 4px solid #99ccff; }
        .content-section h2 { color: #b3d9ff; margin-bottom: 15px; }
        .content-section p { line-height: 1.6; color: #ccddff; }
        .content-section ul { padding-left: 20px; color: #ccddff; line-height: 1.6; }
        .content-section li { margin-bottom: 10px; }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Hóa Học - Hóa vô cơ và Phản ứng oxi hóa khử</h1>
        
        <div class="content-section">
            <h2>Giới thiệu chung</h2>
            <p>Hóa vô cơ là ngành hóa học nghiên cứu về các hợp chất vô cơ, không chứa nguyên tử carbon (trừ một số trường hợp ngoại lệ).</p>
        </div>
        
        <div class="content-section">
            <h2>Phản ứng oxi hóa khử</h2>
            <p>Phản ứng oxi hóa khử là phản ứng hóa học trong đó có sự chuyển dịch electron giữa các chất tham gia phản ứng.</p>
            <ul>
                <li>Chất khử: chất nhường electron</li>
                <li>Chất oxi hóa: chất nhận electron</li>
                <li>Sự oxi hóa: quá trình nhường electron</li>
                <li>Sự khử: quá trình nhận electron</li>
            </ul>
        </div>
        
        <div class="content-section">
            <h2>Ví dụ minh họa</h2>
            <p>Phản ứng giữa kẽm và axit clohidric:</p>
            <p>Zn + 2HCl → ZnCl₂ + H₂</p>
            <p>Trong phản ứng này, kẽm là chất khử và axit clohidric là chất oxi hóa.</p>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== CÁC TRANG KHÁC ====================
    // Tạo các route đơn giản cho các môn còn lại
    std::vector<std::string> subjects = {
        "toan-hinhhoc", "toan-thongke", "nguvan-tholucbat", "nguvan-vantuluan",
        "ngoaingu-nguphap", "ngoaingu-giaotiep", "ngoaingu-vietluan",
        "vatly-quanghoc", "vatly-dien", "hoahoc-huuco", "hoahoc-phuongphap",
        "sinhhoc-tebao", "sinhhoc-ditruyen", "sinhhoc-sinhthai",
        "lichsu-vietnam", "lichsu-thegioi", "lichsu-vanhoadong",
        "dialy-diali", "dialy-dancu", "dialy-moitruong",
        "gdcd-daoduc", "gdcd-phapluat", "gdcd-congdan"
    };

    for (const auto& subject : subjects) {
        CROW_ROUTE(app, "/" + subject)([]() {
            auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bài Thuyết Trình - 8A2</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; }
        body { background: linear-gradient(135deg, #000000 0%, #1a1a4a 100%); color: white; padding: 40px; min-height: 100vh; }
        .container { max-width: 1000px; margin: 0 auto; background: rgba(30, 30, 60, 0.8); padding: 40px; border-radius: 15px; border: 1px solid rgba(255, 255, 255, 0.1); backdrop-filter: blur(10px); }
        h1 { color: #99ccff; margin-bottom: 30px; text-align: center; text-shadow: 0 0 15px rgba(153, 204, 255, 0.7); }
        .back-btn { display: inline-block; background: rgba(153, 204, 255, 0.3); color: white; padding: 10px 20px; border-radius: 8px; text-decoration: none; margin-bottom: 20px; transition: all 0.3s ease; }
        .back-btn:hover { background: rgba(153, 204, 255, 0.5); transform: translateX(-5px); }
        .content-section { margin: 30px 0; padding: 20px; background: rgba(40, 40, 80, 0.5); border-radius: 10px; border-left: 4px solid #99ccff; }
        .content-section h2 { color: #b3d9ff; margin-bottom: 15px; }
        .content-section p { line-height: 1.6; color: #ccddff; }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Quay lại Trang Chủ</a>
        <h1>Bài Thuyết Trình 8A2</h1>
        
        <div class="content-section">
            <h2>Nội dung đang được cập nhật</h2>
            <p>Nội dung chi tiết cho bài thuyết trình này đang được hoàn thiện. Vui lòng quay lại sau.</p>
        </div>
        
        <div class="content-section">
            <h2>Thông tin chung</h2>
            <p>Đây là trang bài thuyết trình của lớp 8A2. Nội dung sẽ sớm được cập nhật đầy đủ.</p>
        </div>
    </div>
</body>
</html>
            )";
            return page;
        });
    }

    // ==================== CHẠY ỨNG DỤNG ====================
    app.port(10000).multithreaded().run();
}