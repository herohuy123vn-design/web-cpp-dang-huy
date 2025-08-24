# Use a base image with Ubuntu
FROM ubuntu:22.04

# Install necessary tools: compiler and make
RUN apt-get update && \
    apt-get install -y g++ make

# Set the working directory inside the container
WORKDIR /app

# Copy all files from your machine to the container
COPY . .

# Compile the C++ code into an executable named 'server'
RUN g++ -std=c++17 -o server main.cpp -pthread

# Expose port 8080 for the web server
EXPOSE 8080

# Command to run when the container starts
CMD ["./server"]