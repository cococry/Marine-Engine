#include "app.h"
#include "input.h"

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
    glfwSetKeyCallback(app.window.glfwInstance, inputGLFWKeyCallback);
    glfwSetMouseButtonCallback(app.window.glfwInstance, inputGLFWMouseButtonCallback);
    glfwSetCursorPosCallback(app.window.glfwInstance, inputGLFWMouseCursorPosCallback);
    glfwSetScrollCallback(app.window.glfwInstance, inputGLFWMouseScrollCallback);

    glfwSwapInterval(true); 

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };
    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    u32 vao, vbo, ibo;

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glCreateBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
    
    gState.app = &app; 

    return app;
}
                                            
void applicationRun(application* app) {
    while(app->running) {
        if(glfwWindowShouldClose(app->window.glfwInstance)) {
            app->running = false;
        }
        if(!app->suspended) {
            if(keyWentDown(GLFW_KEY_ESCAPE)) 
                app->running = false;

            float currentTime = glfwGetTime();
            app->deltaTime = currentTime - app->lastTime;
            app->lastTime = currentTime;
            
            glfwPollEvents();
            glfwSwapBuffers(app->window.glfwInstance);

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        }
    }
}

void applicationTerminate(application* app) {
    glfwDestroyWindow(app->window.glfwInstance);
    glfwTerminate();

    LOG_TRACE("Total memory allocated by Marine-Runtime");
    LOG_TRACE("===================================");
    LOG_TRACE("%lliB", mrnTotalAllocatedMem);
    LOG_TRACE("%fKB", (float)(mrnTotalAllocatedMem / 1024.0f));
    LOG_TRACE("%fMB", (float)(mrnTotalAllocatedMem / (1024.0f * 1024.0f)));
    LOG_TRACE("%fGB", (float)(mrnTotalAllocatedMem / (1024.0f * 1024.0f * 1024.0f))); 
    LOG_TRACE("===================================");
    if(mrnMemUsage != 0) {
        LOG_WARN("Not deallocated memory: %lliB", mrnMemUsage);
    }

}
