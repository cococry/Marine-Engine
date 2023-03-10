#include "input.h"

typedef struct {
    keyboardData crntKeyboard, lastKeyboard;
    mouseData crntMouse, lastMouse;

    bool firstMouseMove;
    float mouseXDelta, mouseYDelta;
    float scrollXDelta, scrollYDelta;
} inputData;

static inputData sData;

void inputInit() {
    for(u32 i = 0; i < GLFW_KEY_LAST; i++) {
        sData.crntKeyboard.keys[i] = false;
        sData.lastKeyboard.keys[i] = false;
    }
    for(u32 i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
        sData.crntMouse.buttons[i] = false;
        sData.lastMouse.buttons[i] = false;
    }
    sData.firstMouseMove = true;
}

void inputGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)window;
    (void)scancode;
    (void)mods;

    if(action != GLFW_RELEASE) {
        if(!sData.crntKeyboard.keys[key]) 
            sData.crntKeyboard.keys[key] = true;
    } else {
        sData.crntKeyboard.keys[key] = false;
    }
}


void inputGLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    (void)window;
    (void)mods;

    if(action != GLFW_RELEASE) {
        if(!sData.crntMouse.buttons[button])
            sData.crntMouse.buttons[button] = true;
    } else {
        sData.crntMouse.buttons[button] = false;
    }
}


void inputGLFWMouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    (void)window;

    sData.crntMouse.xpos = xpos;
    sData.crntMouse.ypos = ypos;

    if(sData.firstMouseMove) {
        sData.lastMouse.xpos = xpos;
        sData.lastMouse.ypos = ypos;
        sData.firstMouseMove = false;
    }

    sData.mouseXDelta = sData.crntMouse.xpos - sData.lastMouse.xpos;
    sData.mouseYDelta = sData.crntMouse.ypos - sData.lastMouse.ypos;
    sData.lastMouse.xpos = xpos;
    sData.lastMouse.ypos = ypos;
}


void inputGLFWMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)window;

    sData.scrollXDelta = xoffset;
    sData.scrollYDelta = yoffset;
}
 

bool isKeyDown(u32 keycode) {
    return sData.crntKeyboard.keys[keycode];
}

bool keyWentDown(u32 keycode) {
    return keyChanged(keycode) && isKeyDown(keycode);
}

bool keyReleased(u32 keycode) {
    return keyChanged(keycode) && !isKeyDown(keycode);

}

bool keyChanged(u32 keycode) {
    return sData.crntKeyboard.keys[keycode] != sData.lastKeyboard.keys[keycode];
}

bool isMouseButtonDown(u32 buttoncode) {
    return sData.crntMouse.buttons[buttoncode];
}

bool mouseButtonWentDown(u32 buttoncode) {
    return mouseButtonChanged(buttoncode) && isMouseButtonDown(buttoncode); 
}

bool mouseButtonReleased(u32 buttoncode) {
    return mouseButtonChanged(buttoncode) && !isMouseButtonDown(buttoncode); 
}

bool mouseButtonChanged(u32 buttoncode) {
    return sData.crntMouse.buttons[buttoncode] != sData.lastMouse.buttons[buttoncode];
}

float getMouseX() {
    return sData.crntMouse.xpos;
}

float getMouseY() {
    return sData.crntMouse.ypos;
}

float getMouseXDelta() {
    return sData.mouseXDelta;
}

float getMouseYDelta() {
    return sData.mouseYDelta;
}

float getMouseXScrollDelta() {
    return sData.scrollXDelta;
}

float getMouseYScrollDelta() {
    return sData.scrollYDelta;
}
