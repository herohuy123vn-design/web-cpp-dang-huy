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

    // ==================== NHÓM MÔN TOÁN ====================
    // --- Đại số ---
    CROW_ROUTE(app, "/toan/daiso")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Toán Đại Số - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/toan" class="back-btn">← Môn Toán</a>
        <h1>Toán Đại Số</h1>
        <!-- Nội dung đại số -->
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Hình học ---
    CROW_ROUTE(app, "/toan/hinhhoc")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Toán Hình Học - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/toan" class="back-btn">← Môn Toán</a>
        <h1>Toán Hình Học</h1>
        
        <div class="content-section">
            <h2>Khái niệm cơ bản</h2>
            <p>Hình học là nhánh của toán học nghiên cứu về hình dạng, kích thước, vị trí tương đối của các hình khối và các tính chất của không gian.</p>
        </div>
        
        <div class="content-section">
            <h2>Các chủ đề chính</h2>
            <ul>
                <li>Hình học phẳng: tam giác, tứ giác, đường tròn</li>
                <li>Hình học không gian: hình chóp, hình lăng trụ, hình cầu</li>
                <li>Hình học giải tích: tọa độ, phương trình đường thẳng, đường tròn</li>
                <li>Lượng giác: tỉ số lượng giác, hệ thức lượng trong tam giác</li>
            </ul>
        </div>
        
        <div class="content-section">
            <h2>Định lý Pythagoras</h2>
            <p>Trong một tam giác vuông, bình phương cạnh huyền bằng tổng bình phương hai cạnh góc vuông.</p>
            <p>Công thức: c² = a² + b²</p>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Thống kê ---
    CROW_ROUTE(app, "/toan/thongke")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Toán Thống Kê - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/toan" class="back-btn">← Môn Toán</a>
        <h1>Toán Thống Kê</h1>
        
        <div class="content-section">
            <h2>Giới thiệu</h2>
            <p>Thống kê là ngành toán học ứng dụng liên quan đến việc thu thập, phân tích, diễn giải và trình bày dữ liệu.</p>
        </div>
        
        <div class="content-section">
            <h2>Các khái niệm cơ bản</h2>
            <ul>
                <li>Dữ liệu và các loại dữ liệu</li>
                <li>Tần số và bảng tần số</li>
                <li>Biểu đồ: biểu đồ cột, biểu đồ đường, biểu đồ tròn</li>
                <li>Các số đặc trưng: số trung bình, trung vị, mốt</li>
                <li>Phương sai và độ lệch chuẩn</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== NHÓM MÔN NGỮ VĂN ====================
    // --- Thơ lục bát ---
    CROW_ROUTE(app, "/nguvan/tholucbat")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Thơ Lục Bát - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/nguvan" class="back-btn">← Môn Ngữ Văn</a>
        <h1>Thơ Lục Bát</h1>
        
        <div class="content-section">
            <h2>Khái quát về thơ lục bát</h2>
            <p>Lục bát là thể thơ dân tộc của Việt Nam, kết cấu theo từng cặp: câu trên 6 tiếng (lục), câu dưới 8 tiếng (bát).</p>
        </div>
        
        <div class="content-section">
            <h2>Luật thơ lục bát</h2>
            <ul>
                <li>Luật bằng trắc: tiếng thứ 2 bằng, tiếng thứ 4 trắc, tiếng thứ 6 bằng, tiếng thứ 8 bằng</li>
                <li>Luật gieo vần: tiếng thứ 6 của câu lục vần với tiếng thứ 6 của câu bát</li>
                <li>Luật đối: không bắt buộc nhưng thường có đối ở các tiếng thứ 2-4-6</li>
            </ul>
        </div>
        
        <div class="content-section">
            <h2>Ví dụ minh họa</h2>
            <div class="quote">
                "Trăm năm trong cõi người ta<br>
                Chữ tài chữ mệnh khéo là ghét nhau<br>
                Trải qua một cuộc bể dâu<br>
                Những điều trông thấy mà đau đớn lòng"
            </div>
            <p>(Trích Truyện Kiều - Nguyễn Du)</p>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Văn tự luận ---
    CROW_ROUTE(app, "/nguvan/vantuluan")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Văn Tự Luận - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/nguvan" class="back-btn">← Môn Ngữ Văn</a>
        <h1>Văn Tự Luận</h1>
        
        <div class="content-section">
            <h2>Khái niệm văn tự luận</h2>
            <p>Văn tự luận là loại văn bản trình bày ý kiến, quan điểm của người viết về một vấn đề xã hội hoặc văn học, sử dụng lập luận và dẫn chứng để thuyết phục người đọc.</p>
        </div>
        
        <div class="content-section">
            <h2>Bố cục bài văn tự luận</h2>
            <ul>
                <li>Mở bài: Giới thiệu vấn đề và nêu ý kiến đánh giá</li>
                <li>Thân bài: Triển khai luận điểm, đưa dẫn chứng và lập luận</li>
                <li>Kết bài: Khẳng định lại quan điểm và mở rộng vấn đề</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== NHÓM MÔN NGOẠI NGỮ ====================
    // --- Ngữ pháp ---
    CROW_ROUTE(app, "/ngoaingu/nguphap")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ngữ Pháp - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/ngoaingu" class="back-btn">← Môn Ngoại Ngữ</a>
        <h1>Ngữ Pháp</h1>
        
        <div class="content-section">
            <h2>Khái niệm ngữ pháp</h2>
            <p>Ngữ pháp là hệ thống các quy tắc về cấu trúc và sử dụng ngôn ngữ, bao gồm các thành phần như từ loại, cấu trúc câu, thì, thể, v.v.</p>
        </div>
        
        <div class="content-section">
            <h2>Các thì cơ bản trong tiếng Anh</h2>
            <ul>
                <li>Hiện tại đơn: Diễn tả thói quen, sự thật hiển nhiên</li>
                <li>Hiện tại tiếp diễn: Diễn tả hành động đang xảy ra</li>
                <li>Quá khứ đơn: Diễn tả hành động đã xảy ra và kết thúc</li>
                <li>Quá khứ tiếp diễn: Diễn tả hành động đang xảy ra tại thời điểm trong quá khứ</li>
                <li>Tương lai đơn: Diễn tả hành động sẽ xảy ra</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Giao tiếp ---
    CROW_ROUTE(app, "/ngoaingu/giaotiep")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Giao Tiếp - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/ngoaingu" class="back-btn">← Môn Ngoại Ngữ</a>
        <h1>Giao Tiếp</h1>
        
        <div class="content-section">
            <h2>Kỹ năng giao tiếp</h2>
            <p>Giao tiếp là quá trình trao đổi thông tin, ý tưởng, cảm xúc giữa người với người thông qua ngôn ngữ nói, viết hoặc cử chỉ.</p>
        </div>
        
        <div class="content-section">
            <h2>Các tình huống giao tiếp thông dụng</h2>
            <ul>
                <li>Chào hỏi và giới thiệu bản thân</li>
                <li>Hỏi đường và chỉ đường</li>
                <li>Mua sắm và trả giá</li>
                <li>Đặt phòng khách sạn và đặt món ăn</li>
                <li>Thảo luận về sở thích và kế hoạch</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Viết luận ---
    CROW_ROUTE(app, "/ngoaingu/vietluan")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Viết Luận - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/ngoaingu" class="back-btn">← Môn Ngoại Ngữ</a>
        <h1>Viết Luận</h1>
        
        <div class="content-section">
            <h2>Kỹ năng viết luận</h2>
            <p>Viết luận là kỹ năng trình bày ý kiến, quan điểm về một chủ đề nhất định một cách logic và thuyết phục bằng văn bản.</p>
        </div>
        
        <div class="content-section">
            <h2>Cấu trúc bài luận cơ bản</h2>
            <ul>
                <li>Mở bài: Giới thiệu chủ đề và nêu luận điểm chính</li>
                <li>Thân bài: Phát triển các luận điểm hỗ trợ với dẫn chứng</li>
                <li>Kết bài: Tóm tắt ý chính và đưa ra kết luận</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== NHÓM MÔN VẬT LÝ ====================
    // --- Quang học ---
    CROW_ROUTE(app, "/vatly/quanghoc")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Quang Học - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/vatly" class="back-btn">← Môn Vật Lý</a>
        <h1>Quang Học</h1>
        
        <div class="content-section">
            <h2>Khái niệm quang học</h2>
            <p>Quang học là ngành vật lý nghiên cứu về ánh sáng, các tính chất của ánh sáng và tương tác của ánh sáng với vật chất.</p>
        </div>
        
        <div class="content-section">
            <h2>Các hiện tượng quang học cơ bản</h2>
            <ul>
                <li>Khúc xạ ánh sáng</li>
                <li>Phản xạ ánh sáng</li>
                <li>Khúc xạ và phản xạ toàn phần</li>
                <li>Giao thoa ánh sáng</li>
                <li>Nhiễu xạ ánh sáng</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Điện học ---
    CROW_ROUTE(app, "/vatly/dien")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Điện Học - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/vatly" class="back-btn">← Môn Vật Lý</a>
        <h1>Điện Học</h1>
        
        <div class="content-section">
            <h2>Khái niệm điện học</h2>
            <p>Điện học là ngành vật lý nghiên cứu về các hiện tượng liên quan đến điện tích, dòng điện, điện trường và từ trường.</p>
        </div>
        
        <div class="content-section">
            <h2>Các khái niệm cơ bản</h2>
            <ul>
                <li>Điện tích và định luật Coulomb</li>
                <li>Dòng điện và cường độ dòng điện</li>
                <li>Điện trở và định luật Ohm</li>
                <li>Điện năng và công suất điện</li>
                <li>Từ trường và cảm ứng điện từ</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== NHÓM MÔN SINH HỌC ====================
    // --- Tế bào ---
    CROW_ROUTE(app, "/sinhhoc/tebao")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Tế Bào - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/sinhhoc" class="back-btn">← Môn Sinh Học</a>
        <h1>Tế Bào</h1>
        
        <div class="content-section">
            <h2>Khái niệm tế bào</h2>
            <p>Tế bào là đơn vị cấu trúc và chức năng cơ bản của mọi sinh vật. Mọi cơ thể sống đều được cấu tạo từ một hoặc nhiều tế bào.</p>
        </div>
        
        <div class="content-section">
            <h2>Cấu trúc tế bào</h2>
            <ul>
                <li>Màng tế bào: Bao bọc và bảo vệ tế bào</li>
                <li>Tế bào chất: Chứa các bào quan và là nơi diễn ra các phản ứng hóa học</li>
                <li>Nhân tế bào: Chứa vật chất di truyền (DNA)</li>
                <li>Các bào quan: Ti thể, lưới nội chất, bộ máy Golgi, ribosome, lysosome</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Di truyền ---
    CROW_ROUTE(app, "/sinhhoc/ditruyen")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Di Truyền - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/sinhhoc" class="back-btn">← Môn Sinh Học</a>
        <h1>Di Truyền</h1>
        
        <div class="content-section">
            <h2>Khái niệm di truyền</h2>
            <p>Di truyền là hiện tượng truyền đạt các tính trạng của bố mẹ cho con cái thông qua vật chất di truyền (DNA).</p>
        </div>
        
        <div class="content-section">
            <h2>Các quy luật di truyền</h2>
            <ul>
                <li>Quy luật phân li của Mendel</li>
                <li>Quy luật phân li độc lập</li>
                <li>Quy luật di truyền liên kết với giới tính</li>
                <li>Quy luật di truyền ngoài nhân</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Sinh thái ---
    CROW_ROUTE(app, "/sinhhoc/sinhthai")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sinh Thái - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/sinhhoc" class="back-btn">← Môn Sinh Học</a>
        <h1>Sinh Thái</h1>
        
        <div class="content-section">
            <h2>Khái niệm sinh thái</h2>
            <p>Sinh thái học là ngành khoa học nghiên cứu mối quan hệ giữa sinh vật với nhau và với môi trường xung quanh.</p>
        </div>
        
        <div class="content-section">
            <h2>Các cấp độ tổ chức sinh thái</h2>
            <ul>
                <li>Cá thể</li>
                <li>Quần thể</li>
                <li>Quần xã</li>
                <li>Hệ sinh thái</li>
                <li>Sinh quyển</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== NHÓM MÔN LỊCH SỬ ====================
    // --- Lịch sử Việt Nam ---
    CROW_ROUTE(app, "/lichsu/vietnam")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Lịch Sử Việt Nam - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/lichsu" class="back-btn">← Môn Lịch Sử</a>
        <h1>Lịch Sử Việt Nam</h1>
        
        <div class="content-section">
            <h2>Các thời kỳ lịch sử Việt Nam</h2>
            <ul>
                <li>Thời kỳ dựng nước: Văn Lang - Âu Lạc</li>
                <li>Thời kỳ Bắc thuộc và chống Bắc thuộc</li>
                <li>Thời kỳ phong kiến độc lập: Đinh, Tiền Lê, Lý, Trần, Hồ, Lê, Nguyễn</li>
                <li>Thời kỳ Pháp thuộc và đấu tranh giành độc lập</li>
                <li>Thời kỳ hiện đại: từ 1945 đến nay</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Lịch sử thế giới ---
    CROW_ROUTE(app, "/lichsu/thegioi")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Lịch Sử Thế Giới - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/lichsu" class="back-btn">← Môn Lịch Sử</a>
        <h1>Lịch Sử Thế Giới</h1>
        
        <div class="content-section">
            <h2>Các thời kỳ lịch sử thế giới</h2>
            <ul>
                <li>Thời kỳ cổ đại: Các nền văn minh sông Nile, Lưỡng Hà, Ấn Độ, Trung Hoa</li>
                <li>Thời kỳ trung đại: Chế độ phong kiến, các đế quốc</li>
                <li>Thời kỳ cận đại: Cách mạng công nghiệp, cách mạng tư sản</li>
                <li>Thời kỳ hiện đại: Chiến tranh thế giới, chiến tranh lạnh, toàn cầu hóa</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Văn hóa Đông Sơn ---
    CROW_ROUTE(app, "/lichsu/vanhoadong")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Văn Hóa Đông Sơn - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/lichsu" class="back-btn">← Môn Lịch Sử</a>
        <h1>Văn Hóa Đông Sơn</h1>
        
        <div class="content-section">
            <h2>Khái quát về văn hóa Đông Sơn</h2>
            <p>Văn hóa Đông Sơn là nền văn hóa khảo cổ học ở Việt Nam, tồn tại từ thế kỷ 7 TCN đến thế kỷ 1-2 SCN, gắn liền với thời kỳ dựng nước Văn Lang - Âu Lạc.</p>
        </div>
        
        <div class="content-section">
            <h2>Đặc trưng văn hóa Đông Sơn</h2>
            <ul>
                <li>Kỹ thuật đúc đồng đỉnh cao với trống đồng Đông Sơn</li>
                <li>Nông nghiệp trồng lúa nước phát triển</li>
                <li>Xã hội có sự phân hóa giàu nghèo</li>
                <li>Tín ngưỡng đa thần, thờ cúng tổ tiên</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== NHÓM MÔN ĐỊA LÝ ====================
    // --- Địa lý tự nhiên ---
    CROW_ROUTE(app, "/dialy/diali")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Địa Lý Tự Nhiên - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/dialy" class="back-btn">← Môn Địa Lý</a>
        <h1>Địa Lý Tự Nhiên</h1>
        
        <div class="content-section">
            <h2>Khái niệm địa lý tự nhiên</h2>
            <p>Địa lý tự nhiên là ngành khoa học nghiên cứu các thành phần tự nhiên của Trái Đất và mối quan hệ giữa chúng.</p>
        </div>
        
        <div class="content-section">
            <h2>Các thành phần tự nhiên</h2>
            <ul>
                <li>Địa hình: núi, đồi, đồng bằng, cao nguyên</li>
                <li>Khí hậu: nhiệt độ, lượng mưa, gió, áp suất</li>
                <li>Thủy văn: sông, hồ, biển, đại dương</li>
                <li>Thổ nhưỡng: các loại đất và tính chất</li>
                <li>Sinh vật: thực vật và động vật</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Dân cư ---
    CROW_ROUTE(app, "/dialy/dancu")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dân Cư - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/dialy" class="back-btn">← Môn Địa Lý</a>
        <h1>Dân Cư</h1>
        
        <div class="content-section">
            <h2>Khái niệm dân cư</h2>
            <p>Dân cư là toàn bộ những người sinh sống trên một lãnh thổ nhất định, được nghiên cứu về quy mô, cơ cấu, phân bố và chất lượng.</p>
        </div>
        
        <div class="content-section">
            <h2>Các chỉ số về dân cư</h2>
            <ul>
                <li>Mật độ dân số: số người trên một đơn vị diện tích</li>
                <li>Tỷ lệ gia tăng dân số: tỷ lệ sinh, tử, nhập cư</li>
                <li>Cơ cấu dân số: theo độ tuổi, giới tính, nghề nghiệp</li>
                <li>Chất lượng dân số: trình độ học vấn, thu nhập, tuổi thọ</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // --- Môi trường ---
    CROW_ROUTE(app, "/dialy/moitruong")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Môi Trường - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <a href="/dialy" class="back-btn">← Môn Địa Lý</a>
        <h1>Môi Trường</h1>
        
        <div class="content-section">
            <h2>Khái niệm môi trường</h2>
            <p>Môi trường là toàn bộ các yếu tố tự nhiên và vật chất nhân tạo bao quanh con người, có ảnh hưởng đến đời sống, sản xuất, sự tồn tại và phát triển của con người và sinh vật.</p>
        </div>
        
        <div class="content-section">
            <h2>Các vấn đề môi trường toàn cầu</h2>
            <ul>
                <li>Biến đổi khí hậu và hiệu ứng nhà kính</li>
                <li>Ô nhiễm không khí, nước và đất</li>
                <li>Suy thoái tầng ozone</li>
                <li>Suy giảm đa dạng sinh học</li>
                <li>Sa mạc hóa và suy thoái đất</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // ==================== TRANG TỔNG QUAN MÔN HỌC ====================
    // --- Trang tổng quan môn Toán ---
    CROW_ROUTE(app, "/toan")([]() {
        auto page = R"(
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Môn Toán - 9A2</title>
    <style>...</style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-btn">← Trang Chủ</a>
        <h1>Môn Toán</h1>
        
        <div class="content-section">
            <h2>Giới thiệu môn Toán</h2>
            <p>Toán học là môn khoa học nghiên cứu về các con số, cấu trúc, không gian và các phép biến đổi. Toán học có ứng dụng rộng rãi trong nhiều lĩnh vực của đời sống và khoa học.</p>
        </div>
        
        <div class="content-section">
            <h2>Các chuyên môn trong môn Toán</h2>
            <ul>
                <li><a href="/toan/daiso">Đại số</a> - Nghiên cứu về các phép toán và phương trình</li>
                <li><a href="/toan/hinhhoc">Hình học</a> - Nghiên cứu về hình dạng và không gian</li>
                <li><a href="/toan/thongke">Thống kê</a> - Nghiên cứu về thu thập và phân tích dữ liệu</li>
            </ul>
        </div>
    </div>
</body>
</html>
        )";
        return page;
    });

    // Tạo các trang tổng quan tương tự cho các môn học khác
    // (Ngữ văn, Ngoại ngữ, Vật lý, Sinh học, Lịch sử, Địa lý)

    // ==================== CHẠY ỨNG DỤNG ====================
    app.port(8080).multithreaded().run();
}