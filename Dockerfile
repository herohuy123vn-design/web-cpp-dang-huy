# Use a base image with Ubuntu
FROM ubuntu:22.04

# Install necessary tools: compiler, make, and ASIO library
RUN apt-get update && \
    apt-get install -y g++ make libasio-dev

# Set the working directory inside the container
WORKDIR /app

# Copy all files from your machine to the container
COPY . .

# Compile the C++ code into an executable named 'server'
RUN g++ -std=c++17 -o server main.cpp -pthread

# Expose port 10000 for the web server (Render yêu cầu port 10000)
EXPOSE 10000

# Command to run when the container starts
CMD ["./server"]