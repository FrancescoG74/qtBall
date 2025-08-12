# qtBall Project

This project implements a simple Qt6 application that creates a window with two moving balls. The balls will change their direction upon colliding with each other.

## Project Structure

```
qtBall
├── src
│   ├── main.cpp          # Entry point of the application
│   ├── ball.h           # Definition of the Ball class
│   ├── ball.cpp         # Implementation of the Ball class methods
│   ├── ballwindow.h     # Definition of the BallWindow class
│   ├── ballwindow.cpp   # Implementation of the BallWindow class methods
└── README.md            # Project documentation
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

- Two balls that move around the window.
- Collision detection that inverts the velocity of the balls upon collision.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.