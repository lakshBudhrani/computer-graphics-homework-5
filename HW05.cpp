
// **********************************************************************************
// ******************* 1. Documentation *******************
// **********************************************************************************
// Project name: Doraemon Animation
// Project goal: To create an interactive animation of the character Doraemon using OpenGL. The animation includes various movements of Doraemon and other elements in the scene, controlled by keyboard and mouse inputs.
// Author's name: Budhrani, Laksh Anil
// Date: 04/05/24


// **********************************************************************************
// ********* 2. Library and Header files ******************
// **********************************************************************************
#include <iostream>
#include <cmath>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cmath>

using namespace std;

#define PI 3.14159265358979323846


// **********************************************************************************
// *********** 3. Function prototypes **************
// **********************************************************************************
void Init();
void Instructions();

//Below are some callback functions
void myDisplay();	                                  // call back function for image definition                               
void myReshape(int newWidth, int newHeight);          // call back function when the size of display window is changed.
void keyboard(unsigned char key, int x, int y);       // call back function for keyboard input
void mouse(int button, int state, int x, int y);      // call back function for mouse input

// Draws the specified text at the given position
void drawText(const char* text, float x, float y); 
// Creates the right-click context menu
void createMenu(); 
// Handles the menu item selection
void menu(int item); 

// Function to draw an ellipse
void drawEllipse(float xCenter, float yCenter, float xRadius, float yRadius, float red, float green, float blue);
// Function to draw an arc
void drawArc(float xCenter, float yCenter, float xRadius, float yRadius, float startAngle, float endAngle, float red, float green, float blue);
// Function to draw a filled arc
void drawFilledArc(float xCenter, float yCenter, float radiusX, float radiusY, float startAngle, float endAngle, float red, float green, float blue);
// Function to draw a line
void drawLine(float x1, float y1, float x2, float y2, float red, float green, float blue);
// Function to draw a rectangle
void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b);
// Function to draw a Doraemon character
void drawDoraemon(); // Draws the Doraemon character
// Draws the bamboo copter on Doraemon's head
void drawBambooCopter(); 
// Draws the balloons in the scene
void drawBalloons(); 

// Updates the animation parameters
void update(int value);


//Some global variables
int windowPositionX = 500, windowPositionY = 100; // Position of the window
int windowWidth = 800, windowHeight = 600; // Size of the window
float angle = 0.0f; // Angle for the bamboo copter
float angularSpeed = 0.1f; // Speed of rotation for the bamboo copter
float scaleCharacter = 0.5; // Scale of the character
float scaleSpeedCharacter = 0.01; // Speed of scaling for the character
float scaleRightLeg = 1.0; // Scale for the right leg
float scaleLeftLeg = 1.0; // Scale for the left leg
float balloonAngle = 0.0f; // Angle for the balloons
float balloonDirection = 2.0f; // Direction of movement for the balloons
float balloonColor[] = { 0.8, 0.6, 1.0 }; // Color of the balloons
bool displayFigureName = true; // Flag to display the figure name
bool animationRunning = false; // Flag to control the animation


// **********************************************************************************
// ******* 4. The main function *******************
// **********************************************************************************
int main(int argc, char** argv)
{
    // 1. Initialize GLUT.
    glutInit(&argc, argv);

    // 2. Initialize display mode to specify single/double buffer and RGB/index.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Use "GLUT_SINGLE" if single buffer is used

    // 3. Set up the initial position (X,Y) of the display window
    glutInitWindowPosition(windowPositionX, windowPositionY);

    // 4. Set up the initial size (width, height) of the display window
    glutInitWindowSize(windowWidth, windowHeight);

    // 5. Create the display window with the title "Doraemon"
    glutCreateWindow("Doraemon");

    // 6. Call user defined functions such as functions to display instructions and
    //    functions to execute one time jobs
    Init();         // Execute initialization procedure (one time jobs)
    Instructions(); // Display instructions to the user

    // 7. Register callback functions to be called by GLUT event processing loop
    glutDisplayFunc(myDisplay);	 // Register a display callback function for window repaint event
    glutReshapeFunc(myReshape);  // Register a reshape callback function for window resize event
    glutTimerFunc(80, update, 0); // Register a timer callback function to be triggered after a specified time

    glutKeyboardFunc(keyboard); // Register a keyboard callback function for keyboard event
    glutMouseFunc(mouse); // Register a mouse callback function for mouse event

    // 8. Start the GLUT event processing loop
    glutMainLoop();

    // 9. We will never reach here as the GLUT event processing loop never returns.
    //    Return statement can be omitted.
    return 0;
}



// **************************************************************************
// ******* 5. Function implementations *************
// ***************************************************************************

// Input:  Nothing
// Output: Nothing
// Actions: Print instructions in the standard output window
void Instructions() {
    cout << "Instructions for user interactions:" << std::endl;
    cout << "1. Press 's' to start/stop the animation." << std::endl;
    cout << "2. Left click to start/stop the animation." << std::endl;
    cout << "3. Right click to open the menu. You can change the color of the balloons and toggle the figure name." << std::endl;
}

// What: A function to do some one-time jobs
// Input: None
// Output: None
// Actions: Perform some one-time jobs, e.g., initializations, such as:
//          1. Set the background color of the display window;
void Init()
{
    cout << "Funciton Init() is called.\n";
    double colorRed = 1.0, colorGreen = 1.0, colorBlue = 0.8, alphaValue = 0.0;

    // 1. Set the background color of the display window
    glClearColor(colorRed, colorGreen, colorBlue, alphaValue);
}


// What: A call-back function specifies the actions that will be taken when the display window is created or its size is changed.
// Input: 
//			1. w - Current display window's width (in pixels)
//			2. h - Current display window's height (in pixels)
// Output: None
// Actions: Perform some one-time jobs, e.g., initializations, such as:
//			1. Set up the viewport (whole or part of the display window)
//          2. Select and initialize the projection matrix stack used for projections;
//          3. Set up projection matrix, i.e., the viewing volume that has 6 clipping planes;
//          4. Select and initialize the model-view matrix stack used for geometric transformations;
//          5. Other possible one time jobs.
void myReshape(int w, int h)
{
    cout << "Function myReshapeFunc() is called.\n";
    double clippingPlanLeft = -1.2, clippingPlanRight = 1.2;
    double clippingPlanBottom = -0.6, clippingPlanTop = 2.0;

    // 1. Set up the viewport(whole or part of the display window)
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // 2. Select and initialize the projection matrix stack used for projections
    glMatrixMode(GL_PROJECTION); // Select the projection matrix stack
    glLoadIdentity();            // Initialize the stack with the identity matrix

    // 3. Set up projection matrix, i.e., the viewing volume that has 6 clipping planes.
    gluOrtho2D(clippingPlanLeft, clippingPlanRight, clippingPlanBottom, clippingPlanTop);

    // 4. Select and initialize the model-view matrix stack used for geometric transformations
    glMatrixMode(GL_MODELVIEW); // Select the model-view matrix stack for transformations.
    glLoadIdentity();           // Initialize the stack with the identity matrix
}

// What: A display call-back function that defines the picture that will be displayed.
// Action: 
//			1. Clear and then display the background color of the display window;
//			2. ... (Something specific to this program such as picture definitions);
//			3. Flush the buffer to display the image into the display window, i.e., show the image.
// Input: None
// Output: None
void myDisplay() {
    //1. Clear the background color of the display window and be ready to color the display window
    //   with the color defined by "glClearColor()" function.
    glClear(GL_COLOR_BUFFER_BIT);
    createMenu(); // Create the menu

    // If the displayFigureName flag is true, draw the text "Doraemon" at the specified coordinates
    if (displayFigureName) {
        drawText("Doraemon", -0.2, 1.8);
    }

    glLoadIdentity(); // Reset the current matrix to the identity matrix

    // Translate to the current y position
    glPushMatrix(); // Save the current matrix
    glScalef(scaleCharacter, scaleCharacter, 1.0); // Scale the character

    // Draw the Doraemon character, a Bamboo Copter, and balloons
    drawDoraemon();
    drawBambooCopter();
    drawBalloons();

    glPopMatrix(); // Restore the saved matrix


    // 3. Flush the buffer to display the image into the display window, i.e., show the image
    glFlush();  // When single buffer is used.
}


// What: Callback function to handle keyboard input
// Input: The key pressed and the mouse coordinates at the time of the key press
// Output: None
// Action: The function handles the keyboard input and performs actions based on the key pressed.
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 's': // Press 's' to start/stop the animation
        animationRunning = !animationRunning;
        break;
    }
}

// What: Callback function handling mouse input
// Input: button - one the three mouse buttons (Left, middle, and right)
//       state - press (GLUT_DOWN) or release (GLUT_UP) action of a mouse button
//       x, y - the window relative coordinates when the mouse button state changed
// Output: None
// Actions: Start or stop the animation by clicking on left button;
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Left click to start/stop the animation
        animationRunning = !animationRunning;
    }
}


// What: Function to update the animation parameters
// Input: An integer value that is not used
// Output: None
// Action: The function updates the animation parameters such as the angle of rotation, scale of the character, and direction of movement. It also controls the animation of the bamboo copter and the balloons.
// Caller: glutTimerFunc(80, update, 0)
void update(int value) {
    // Check if the animation is running
    if (animationRunning) {
        // Update the angle for the bamboo copter
        angle += angularSpeed;
        if (angle > 360.f) {
            angle -= 360.f;  // Wrap around if the angle exceeds 360
        }

        // Define the parameters for the leg movement
        const float maxScale = 1.8; // Maximum scale value
        const float legScaleSpeed = 0.05; // Speed of leg movement
        const float minLegScale = 0.8; // Minimum leg scale
        const float maxLegScale = 1.2; // Maximum leg scale
        const float frequencyFactor = 3.5; // Increase this to make the leg movement faster

        // Update the scale and leg movement
        if (scaleCharacter < maxScale) {
            scaleCharacter += scaleSpeedCharacter; // Increase the scale
            // Alternate the scale of the legs
            scaleRightLeg = minLegScale + (maxLegScale - minLegScale) * (sin(frequencyFactor * angle) + 1) / 2;
            scaleLeftLeg = maxLegScale - (maxLegScale - minLegScale) * (sin(frequencyFactor * angle) + 1) / 2;
        }
        else {
            // Stop the leg movement when maximum scale is reached
            scaleRightLeg = 1.0;
            scaleLeftLeg = 1.0;
        }

        // Update the balloon angle
        balloonAngle += balloonDirection;

        // Change the direction of the balloon movement if it exceeds the limits
        if (balloonAngle > 25.0f || balloonAngle < -25.0f) {
            balloonDirection *= -1; // Change direction
        }
    }

    // Redisplay the window and set the timer for the next update
    glutPostRedisplay();
    glutTimerFunc(80, update, 0);
}


// What: Function to draw text on the screen
//       This function uses GLUT's bitmap character rendering function to draw text.
// Input: const char* text - The text to be drawn
//        float x, y - The coordinates where the text should be drawn
// Output: None
// Action: The function sets the color and position for the text, and then iterates over each character in the text string, drawing it on the screen.
// Caller: myDisplay()
void drawText(const char* text, float x, float y) {
    glColor3f(0.0, 0.0, 0.0); // Set the color of the text to black
    glRasterPos2f(x, y); // Set the position where the text will start
    while (*text) { // Iterate over each character in the text string
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++); // Draw the current character and move to the next one
    }
}


// What: Function to handle menu actions
// Input: item (integer representing the menu item selected by the user)
// Output: None
// Action: The function changes the balloon color or toggles the figure name display based on the menu item selected.
// Caller: createMenu()
void menu(int item) {
    switch (item) {
    case 1: // Red
        balloonColor[0] = 1.0;
        balloonColor[1] = 0.0;
        balloonColor[2] = 0.0;
        break;
    case 2: // Green
        balloonColor[0] = 0.0;
        balloonColor[1] = 1.0;
        balloonColor[2] = 0.0;
        break;
    case 3: // Blue
        balloonColor[0] = 0.0;
        balloonColor[1] = 0.0;
        balloonColor[2] = 1.0;
        break;
    case 4: // Toggle figure name
        displayFigureName = !displayFigureName;
        break;
    }

    glutPostRedisplay();
}

// What: Function to create a menu
// Input: None
// Output: None
// Action: The function creates a new pop-up menu, adds menu entries to it, and attaches the menu to the right mouse button.
// Caller: myDisplay()
void createMenu() {
    // Step 1: Create a new pop-up menu
    // Step 2: Create the callback function “menu (int item)”
    glutCreateMenu(menu);

    // Step 4: Add menu entries or sub-menu(s) to the menu
    glutAddMenuEntry("Red Balloons", 1);
    glutAddMenuEntry("Green Balloons", 2);
    glutAddMenuEntry("Blue Balloons", 3);
    glutAddMenuEntry("Toggle Figure Name", 4);

    // Step 3: Attach the menu to a mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// Below are implementations of creating shapes

// What: Function to draw an ellipse
// Input: center coordinates (xCenter, yCenter), radii (xRadius, yRadius), color (red, green, blue)
// Output: None
// Action: The function first draws a filled ellipse with the specified color, then outlines it in black.
// Caller: drawDoraemon(), drawBambooCopter() and drawBalloons()
void drawEllipse(float xCenter, float yCenter, float xRadius, float yRadius, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 300; i++) {
        double angle = 2 * PI * i / 300;
        double x = xRadius * cos(angle) + xCenter;
        double y = yRadius * sin(angle) + yCenter;
        glVertex2d(x, y);
    }
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 300; i++) {
        double angle = 2 * PI * i / 300;
        double x = xRadius * cos(angle) + xCenter;
        double y = yRadius * sin(angle) + yCenter;
        glVertex2d(x, y);
    }
    glEnd();
}

// What: Function to draw an arc
//       An arc is a portion of the circumference of an ellipse, which is defined by the start and end angles
// Input: center coordinates (xCenter, yCenter), radii (xRadius, yRadius), start and end angles (startAngle, endAngle), color (red, green, blue)
// Output: None
// Action: The function draws an arc from the start angle to the end angle with the specified color.
// Caller: drawDoraemon()
void drawArc(float xCenter, float yCenter, float xRadius, float yRadius, float startAngle, float endAngle, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_LINE_STRIP);
    if (startAngle <= endAngle) {
        for (int i = startAngle; i <= endAngle; i++) {
            double angle = 2 * PI * i / 360;
            double x = xRadius * cos(angle) + xCenter;
            double y = yRadius * sin(angle) + yCenter;
            glVertex2d(x, y);
        }
    }
    else {
        for (int i = startAngle; i >= endAngle; i--) {
            double angle = 2 * PI * i / 360;
            double x = xRadius * cos(angle) + xCenter;
            double y = yRadius * sin(angle) + yCenter;
            glVertex2d(x, y);
        }
    }
    glEnd();
}

// What: Function to draw a filled arc
//       An arc is a portion of the circumference of an ellipse, which is defined by the start and end angles
// Input: center coordinates (xCenter, yCenter), radii (radiusX, radiusY), start and end angles (startAngle, endAngle), color (red, green, blue)
// Output: None
// Action: The function draws a filled arc from the start angle to the end angle with the specified color.
// Caller: drawDoraemon()
void drawFilledArc(float xCenter, float yCenter, float radiusX, float radiusY, float startAngle, float endAngle, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(xCenter, yCenter);
    if (startAngle <= endAngle) {
        for (int i = startAngle; i <= endAngle; i++) {
            double angle = 2 * PI * i / 360;
            double x = radiusX * cos(angle) + xCenter;
            double y = radiusY * sin(angle) + yCenter;
            glVertex2d(x, y);
        }
    }
    else {
        for (int i = startAngle; i >= endAngle; i--) {
            double angle = 2 * PI * i / 360;
            double x = radiusX * cos(angle) + xCenter;
            double y = radiusY * sin(angle) + yCenter;
            glVertex2d(x, y);
        }
    }
    glEnd();
}

// What: Function to draw a line
// Input: start and end coordinates (x1, y1, x2, y2), color (red, green, blue)
// Output: None
// Action: The function draws a line from the start coordinates to the end coordinates with the specified color.
// Caller: drawDoraemon(), drawBambooCopter() and drawBalloons()
void drawLine(float x1, float y1, float x2, float y2, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

// What: Function to draw a rectangle
// Input: corner coordinates (x1, y1, x2, y2), color (r, g, b)
// Output: None
// Action: The function first draws a filled rectangle with the specified color, then outlines it in black.
//         The corner coordinates (x1, y1) and (x2, y2) represent the bottom-left and top-right OR 
//         bottom-right and top-left corners of the rectangle, respectively
// Caller: drawDoraemon()
void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}


// Below are implementation of some objects

// What: Function to draw a Bamboo Copter
//       This function uses various shapes like lines and ellipses to draw a Bamboo Copter.
// Input: None
// Output: None
// Action: The function draws a Bamboo Copter with a surface, an attacher, and three fans.
// Caller: myDisplay()
void drawBambooCopter() {
    drawEllipse(0.0, 0.8, 0.1, 0.04, 1.0, 1.0, 0.8); // Draw the surface of the copter
    drawLine(0.0, 0.7, 0.0, 0.8, 0.0, 0.0, 0.0); // Draw the attacher of the copter
    drawLine(0.0, 0.8, 0.0 + 0.1 * cos(angle), 0.8 + 0.04 * sin(angle), 0.0, 0.0, 0.0); // Draw the first fan of the copter
    drawLine(0.0, 0.8, 0.0 + 0.1 * cos(120 + angle), 0.8 + 0.04 * sin(120 + angle), 0.0, 0.0, 0.0); // Draw the second fan of the copter
    drawLine(0.0, 0.8, 0.0 + 0.1 * cos(240 + angle), 0.8 + 0.04 * sin(240 + angle), 0.0, 0.0, 0.0); // Draw the third fan of the copter
}

// What: Function to draw balloons
//       This function uses various shapes like lines and ellipses to draw balloons.
// Input: None
// Output: None
// Action: The function draws two balloons with threads and applies rotation to them.
// Caller: myDisplay()
void drawBalloons() {
    glColor3fv(balloonColor);
    // Draw the thread
    drawLine(0.35, 0.3, 0.45, 0.63, 0.0, 0.0, 0.0); // Right balloon thread
    drawLine(-0.35, 0.3, -0.45, 0.63, 0.0, 0.0, 0.0); // Left balloon thread

    // Draw the balloon with rotation
    glPushMatrix();
    glTranslatef(0.45, 0.63, 0.0); // Move to the rotation point of the right balloon
    glRotatef(balloonAngle, 0.0, 0.0, 1.0); // Rotate the right balloon around the Z-axis
    glTranslatef(-0.45, -0.63, 0.0); // Move back
    drawEllipse(0.45, 0.83, 0.1, 0.2, balloonColor[0], balloonColor[1], balloonColor[2]); // Draw the right balloon
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.45, 0.63, 0.0); // Move to the rotation point of the left balloon
    glRotatef(balloonAngle, 0.0, 0.0, 1.0); // Rotate the left balloon around the Z-axis
    glTranslatef(0.45, -0.63, 0.0); // Move back
    drawEllipse(-0.45, 0.83, 0.1, 0.2, balloonColor[0], balloonColor[1], balloonColor[2]); // Draw the left balloon
    glPopMatrix();
}

// What: Function to draw a Doraemon character
//       Doraemon is a popular Japanese manga series character
//       This function uses various shapes like ellipses, arcs, lines, and rectangles to draw Doraemon.
// Input: None
// Output: None
// Action: The function draws a Doraemon character by calling other functions to draw its 
//         face, eyes, nose, mustache, smile, hands, fists, stomach, neck band, bell, and legs.
// Caller: myDisplay()
void drawDoraemon() {
    // Draw the face and its features
    drawEllipse(0.0, 0.5, 0.25, 0.2, 0.6, 0.8, 1.0); // Face
    drawEllipse(0.0, 0.44, 0.22, 0.133, 1.0, 1.0, 1.0); // Face patch
    drawEllipse(-0.04, 0.54, 0.04, 0.065, 1.0, 1.0, 1.0); // Left eye
    drawEllipse(0.04, 0.54, 0.04, 0.065, 1.0, 1.0, 1.0); // Right eye
    drawArc(-0.032, 0.51, 0.018, 0.025, 40, 180, 0.0, 0.0, 0.0); // Left pupil
    drawArc(0.04, 0.51, 0.018, 0.025, 40, 180, 0.0, 0.0, 0.0); // Right pupil
    drawEllipse(0.0, 0.461, 0.025, 0.025, 1.0, 0.0, 0.0); // Nose
    drawLine(0.00, 0.436, 0.0, 0.411, 0.0, 0.0, 0.0); // Face-nose line

    // Draw the mustache
    drawLine(0.12, 0.44, 0.2, 0.47, 0.0, 0.0, 0.0); // Right upper
    drawLine(0.12, 0.40, 0.2, 0.40, 0.0, 0.0, 0.0); // Right middle
    drawLine(0.12, 0.36, 0.2, 0.33, 0.0, 0.0, 0.0); // Right lower
    drawLine(-0.12, 0.44, -0.2, 0.47, 0.0, 0.0, 0.0); // Left upper
    drawLine(-0.12, 0.40, -0.2, 0.40, 0.0, 0.0, 0.0); // Left middle
    drawLine(-0.12, 0.36, -0.2, 0.33, 0.0, 0.0, 0.0); // Left lower

    // Draw the smile
    drawFilledArc(0.0, 0.413, 0.065, 0.065, 0, -180, 0.98, 0.012, 0.337);

    // Draw the hands and fists
    drawRectangle(-0.35, 0.28, -0.12, 0.21, 0.6, 0.8, 1.0); // Left hand
    drawRectangle(0.35, 0.28, 0.12, 0.21, 0.6, 0.8, 1.0); // Right hand
    drawEllipse(-0.35, 0.25, 0.05, 0.05, 1.0, 1.0, 1.0); // Left fist
    drawEllipse(0.35, 0.25, 0.05, 0.05, 1.0, 1.0, 1.0); // Right fist

    // Draw the stomach and its features
    drawRectangle(-0.15, 0.28, 0.15, -0.03, 0.6, 0.8, 1.0); // Stomach
    drawFilledArc(0, 0.275, 0.13, 0.22, 0, -180, 1.0, 1.0, 1.0); // White strip on stomach
    drawArc(0, 0.16, 0.06, 0.06, 0, -180, 0.0, 0.0, 0.0); // Pocket
    drawLine(-0.06, 0.16, 0.06, 0.16, 0.0, 0.0, 0.0); // Pocket line

    // Draw the neck band and bell
    drawRectangle(-0.12, 0.324, 0.12, 0.28, 1.0, 0.0, 0.0); // Neck band
    drawEllipse(0.0, 0.275, 0.035, 0.035, 1.0, 0.6667, 0.1137); // Bell

    // Draw the legs
    glPushMatrix(); // Save the current matrix
    glScalef(1.0, scaleLeftLeg, 1.0); // Scale the left leg
    drawEllipse(-0.1, -0.08, 0.09, 0.05, 1.0, 1.0, 1.0); // Draw the left leg
    glPopMatrix(); // Restore the saved matrix

    glPushMatrix(); // Save the current matrix
    glScalef(1.0, scaleRightLeg, 1.0); // Scale the right leg
    drawEllipse(0.1, -0.08, 0.09, 0.05, 1.0, 1.0, 1.0); // Draw the right leg
    glPopMatrix(); // Restore the saved matrix

    drawLine(0, -0.035, 0, 0.03, 0.0, 0.0, 0.0); // Leg line
}