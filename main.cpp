// main.cpp
#include "crow.h"

int main()
{
    crow::SimpleApp app;

    // Định nghĩa route cho trang chủ
    CROW_ROUTE(app, "/")([](){
        auto page = R"(
            <!DOCTYPE html>
            <html>
            <head>
                <meta charset="UTF-8"> <!-- THÊM DÒNG NÀY -->
                <title>Web C++ của tôi</title>
                <style>
                    body { font-family: Arial; text-align: center; margin-top: 50px; }
                    h1 { color: blue; }
                </style>
            </head>
            <body>
                <h1>Xin chào từ Web Server viết bằng C++!</h1>
                <p>Đây là trang web đầu tiên của tôi.</p>
                <a href="/about">Về chúng tôi</a>
            </body>
            </html>
        )";
        return page;
    });

    // Thêm một route khác
    CROW_ROUTE(app, "/about")([](){
        return R"(
            <!DOCTYPE html>
            <html>
            <head>
                <meta charset="UTF-8"> <!-- THÊM DÒNG NÀY -->
                <title>Về chúng tôi</title>
            </head>
            <body>
                <h1>Trang Giới Thiệu</h1>
                <p>Web server được viết bằng C++ Crow framework.</p>
            </body>
            </html>
        )";
    });

    app.port(8080).multithreaded().run();
}