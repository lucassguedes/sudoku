# Use official GCC image with CMake preinstalled
FROM gcc:latest

# Install CMake
RUN apt-get update && apt-get install -y cmake

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the entire project into the container
COPY . .

# Create a build directory inside the container
RUN mkdir -p build

# Set the working directory to build
WORKDIR /usr/src/app/build

# Run CMake and build the application
RUN cmake .. && make

# Define the default command to run your executable
CMD ["../bin/sudoku"]