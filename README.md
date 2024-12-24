# Computer Graphics Homework 5

## Overview
This repository contains Homework 5 for my Computer Graphics course (CSCI B365). The assignment involves creating an animation of the Doraemon character with user interactions. The animation can be controlled using the 's' key, left mouse button, and right mouse button. The code is written in C++ using OpenGL.

## Prerequisites
- C++ compiler
- OpenGL setup

## Installation
1. Ensure you have a C++ compiler and OpenGL set up in your environment.
2. Copy the code from `HW05.cpp` and paste it into your IDE.
3. Compile and run the code.

## Usage
- **Start/Stop Animation**: Press the 's' key or left mouse button.
- **Show Menu**: Right mouse button.

## Features
- Animation of the Doraemon character.
- User interactions via keyboard and mouse.
- Audio-visual animation created by merging the animation with the Doraemon Hindi version track using Microsoft Clipchamp.

## Tools Used
- Visual Studio Community 2022
- Microsoft Clipchamp

## Code Structure

### Function Prototypes
- `void Init();`: Initializes the display window.
- `void Instructions();`: Prints instructions for user interactions.
- Callback Functions:
  - `void myDisplay();`: Defines the image to be displayed.
  - `void myReshape(int newWidth, int newHeight);`: Handles window resizing.
  - `void keyboard(unsigned char key, int x, int y);`: Handles keyboard input.
  - `void mouse(int button, int state, int x, int y);`: Handles mouse input.
- Drawing Functions:
  - `void drawText(const char* text, float x, float y);`: Draws text on the screen.
  - `void createMenu();`: Creates the right-click context menu.
  - `void menu(int item);`: Handles menu item selection.
  - `void drawEllipse(float xCenter, float yCenter, float xRadius, float yRadius, float red, float green, float blue);`: Draws an ellipse.
  - `void drawArc(float xCenter, float yCenter, float xRadius, float yRadius, float startAngle, float endAngle, float red, float green, float blue);`: Draws an arc.
  - `void drawFilledArc(float xCenter, float yCenter, float radiusX, float radiusY, float startAngle, float endAngle, float red, float green, float blue);`: Draws a filled arc.
  - `void drawLine(float x1, float y1, float x2, float y2, float red, float green, float blue);`: Draws a line.
  - `void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b);`: Draws a rectangle.
  - `void drawDoraemon();`: Draws the Doraemon character.
  - `void drawBambooCopter();`: Draws the bamboo copter on Doraemon's head.
  - `void drawBalloons();`: Draws the balloons in the scene.
- Animation Function:
  - `void update(int value);`: Updates the animation parameters.

### Global Variables
- `int windowPositionX, windowPositionY;`: Position of the window.
- `int windowWidth, windowHeight;`: Size of the window.
- `float angle, angularSpeed;`: Angle and speed of rotation for the bamboo copter.
- `float scaleCharacter, scaleSpeedCharacter;`: Scale and speed of scaling for the character.
- `float scaleRightLeg, scaleLeftLeg;`: Scale for the right and left legs.
- `float balloonAngle, balloonDirection;`: Angle and direction of movement for the balloons.
- `float balloonColor[];`: Color of the balloons.
- `bool displayFigureName, animationRunning;`: Flags to control the display of the figure name and animation state.

### Main Function
1. **Initialize GLUT**: `glutInit(&argc, argv);`
2. **Set Display Mode**: `glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);`
3. **Set Window Position**: `glutInitWindowPosition(windowPositionX, windowPositionY);`
4. **Set Window Size**: `glutInitWindowSize(windowWidth, windowHeight);`
5. **Create Window**: `glutCreateWindow("Doraemon");`
6. **Initialize and Display Instructions**: `Init(); Instructions();`
7. **Register Callback Functions**:
   - `glutDisplayFunc(myDisplay);`
   - `glutReshapeFunc(myReshape);`
   - `glutTimerFunc(80, update, 0);`
   - `glutKeyboardFunc(keyboard);`
   - `glutMouseFunc(mouse);`
8. **Start Event Processing Loop**: `glutMainLoop();`

### Function Implementations
- **Instructions**: Prints instructions for user interactions.
- **Init**: Sets the background color of the display window.
- **myReshape**: Handles window resizing and sets up the viewport and projection matrix.
- **myDisplay**: Clears the display window, creates the menu, draws the Doraemon character, bamboo copter, and balloons, and flushes the buffer to display the image.
- **keyboard**: Handles keyboard input to start/stop the animation.
- **mouse**: Handles mouse input to start/stop the animation.
- **update**: Updates the animation parameters and redisplays the window.
- **drawText**: Draws text on the screen.
- **menu**: Handles menu item selection to change balloon color or toggle figure name display.
- **createMenu**: Creates a right-click context menu with options to change balloon color and toggle figure name display.

### Shape Drawing Functions
- **drawEllipse**: Draws a filled ellipse with the specified color and outlines it in black.
- **drawArc**: Draws an arc from the start angle to the end angle with the specified color.
- **drawFilledArc**: Draws a filled arc from the start angle to the end angle with the specified color.
- **drawLine**: Draws a line from the start coordinates to the end coordinates with the specified color.
- **drawRectangle**: Draws a filled rectangle with the specified color and outlines it in black.

### Object Drawing Functions
- **drawBambooCopter**: Draws a Bamboo Copter using various shapes like lines and ellipses.
- **drawBalloons**: Draws two balloons with threads and applies rotation to them.
- **drawDoraemon**: Draws a Doraemon character using various shapes like ellipses, arcs, lines, and rectangles.
