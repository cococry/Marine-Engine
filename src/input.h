#include "defines.h"
#include <GLFW/glfw3.h>

typedef struct {
    bool keys[GLFW_KEY_LAST];
} keyboardData;

typedef struct {
    bool buttons[GLFW_MOUSE_BUTTON_LAST];
    float xpos, ypos;
} mouseData;

void inputInit();

void inputGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void inputGLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void inputGLFWMouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

void inputGLFWMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

bool isKeyDown(u32 keycode);

bool keyWentDown(u32 keycode);

bool keyReleased(u32 keycode);

bool keyChanged(u32 keycode);

bool isMouseButtonDown(u32 buttoncode);

bool mouseButtonWentDown(u32 buttoncode);

bool mouseButtonReleased(u32 buttoncode);

bool mouseButtonChanged(u32 buttoncode);

float getMouseX();

float getMouseY();

float getMouseXDelta();

float getMouseYDelta();

float getMouseXScrollDelta();

float getMouseYScrollDelta();


