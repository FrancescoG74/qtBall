# qtBall Project

This project implements a Qt6 application that creates a window with 8 moving balls of different colors, sizes, and velocities. The balls bounce off the window boundaries and collide with each other with realistic physics simulation.

## Project Structure

```
qtBall
├── include/
│   ├── ball.h           # Definition of the Ball class
│   └── ballwindow.h     # Definition of the BallWindow class
├── source/
│   ├── main.cpp         # Entry point of the application
│   ├── ball.cpp         # Implementation of the Ball class methods
│   └── ballwindow.cpp   # Implementation of the BallWindow class methods
├── build/               # Build directory (generated, ignored by git)
├── CMakeLists.txt       # CMake configuration file
├── .gitignore          # Git ignore file
└── README.md           # Project documentation
```

## Building the Application

To build the application, ensure you have Qt6 installed and set up on your system. You can use the following commands:

1. Navigate to the project directory:
   ```
   cd qtBall
   ```

2. Create a build directory and navigate into it:
   ```
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```
   cmake ..
   ```

4. Build the project:
   ```
   cmake --build .
   ```

## Running the Application

After building the project, you can run the application using the following command:

```
./qtBall
```

## Features

- 8 balls with different colors (red, blue, green, magenta, cyan, yellow, gray, dark red)
- Each ball has different size, position, and velocity
- Realistic collision detection between balls with proper physics simulation
- Boundary collision detection - balls bounce off window edges
- Smooth animation at approximately 60 FPS
- Keyboard controls: Press 'Escape' or 'Q' to quit the application
- Anti-aliased rendering for smooth graphics

## Requirements

- Qt6 (QtWidgets module)
- CMake 3.16 or higher
- C++17 compatible compiler

## License

This project is licensed under the MIT License. See the LICENSE file for more details.