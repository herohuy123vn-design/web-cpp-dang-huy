# Sử dụng một image Linux có sẵn
FROM ubuntu:22.04

# Cài đặt các công cụ cần thiết: compiler, cmake
RUN apt-get update && \
    apt-get install -y g++ cmake make

# Đặt thư mục làm việc trong container
WORKDIR /app

# Copy toàn bộ code từ máy bạn vào container
COPY . .

# Biên dịch code C++ thành file thực thi 'server'
# Lệnh này giống hệt lệnh bạn chạy trong MSYS2
RUN g++ -std=c++17 -o server main.cpp -pthread

# Mở port 8080 để web server chạy
EXPOSE 8080

# Lệnh chạy khi container khởi động
CMD ["./server"]
