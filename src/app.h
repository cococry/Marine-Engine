#include "defines.h"
#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow* glfwInstance;
    u32 width, height;
    const char* title;
} windowState;

typedef struct {
    bool running;
    bool suspended;
    windowState window;
    float deltaTime, lastTime;
} application;

typedef struct {
    application* app;
} globalState;

extern globalState gState;

application applicationCreate(const char* title, u32 width, u32 height);
                                            
void applicationRun(application* app);

void applicationTerminate(application* app);
