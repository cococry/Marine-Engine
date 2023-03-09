#include "app.h"
#include <glad/glad.h>

globalState gState;

static void applicationOnResize(GLFWwindow* window, i32 width, i32 height) {
    (void)window;
    gState.app->window.width = width;
    gState.app->window.height = height;
    if(width <= 0 || height <= 0) {
        gState.app->suspended = true;
    } else {
        gState.app->suspended = false;
    }
    glViewport(0, 0, width, height);
}
application applicationCreate(const char* title, u32 width, u32 height) {
    application app;

    app.running = true;
    app.suspended = false;
    app.deltaTime = 0.0f;
    app.lastTime = 0.0f;

    app.window.title = title;
    app.window.width = width;
    app.window.height = height;

    ASSERT(glfwInit(), "Failed to initialize GLFW.");

    app.window.glfwInstance = glfwCreateWindow(width, height, title, NULL, NULL);
    
    ASSERT(app.window.glfwInstance, "Failed to create GLFW window."); 

    LOG_INFO("Created application window '%s' (%ix%i).", 
            app.window.title, app.window.width, app.window.height);

    glfwMakeContextCurrent(app.window.glfwInstance);
    
    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad.");

    glfwSetFramebufferSizeCallback(app.window.glfwInstance, applicationOnResize);
    
    glfwSwapInterval(true); 
    gState.app = &app;
    
    float* block = NULL;

    float* block2 =  mrn_malloc(block2, sizeof(float) * 2);
    block2[0] = 3;
    block2[1] = 4;


    assign_ptr(block2, block); 

    return app;
}
                                            
void applicationRun(application* app) {
    while(app->running) {
        if(glfwWindowShouldClose(app->window.glfwInstance)) {
            app->running = false;
        }
        if(!app->suspended) {
            float currentTime = glfwGetTime();
            app->deltaTime = currentTime - app->lastTime;
            app->lastTime = currentTime;

            glfwPollEvents();
            glfwSwapBuffers(app->window.glfwInstance);

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
        }
    }
}

void applicationTerminate(application* app) {
    glfwDestroyWindow(app->window.glfwInstance);
    glfwTerminate();
}
