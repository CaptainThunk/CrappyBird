//
////  main.cpp
////  CrappyBird
////
////  Created by Dean Becker on 14/12/2015.
////  Copyright © 2015 Dean Becker. All rights reserved.
////
//
//#include <GL/glew.h>

#include "gl_headers.h"

#include "Input.hpp"
#include "Shader.hpp"

#include <iostream>

static int width = 1280;
static int height = 720;
static float ratio = width / (float)height;

static bool running = false;

static GLFWwindow *window;

static void error_callback(int error, const char* description)
{
    std::cout << description << std::endl;
}

void init()
{
    if (!glfwInit()) {
        std::cout << "GLFW could not initialise!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "Crappy Bird", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "GLFW could not create a window!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

    Shader::LoadAll();
}

void update()
{
    glfwPollEvents();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glfwSwapBuffers(window);
}

void run()
{
    init();

    double lastTime = glfwGetTime();
    int frames = 0;

    while (running) {
        double now = glfwGetTime();
        frames++;
        if (now - lastTime >= 1.0) {
            printf("%f ms/frame\n", 1000.0/double(frames));
            frames = 0;
            lastTime += 1.0;
        }

        update();
        render();

        int error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << error << std::endl;
        }

        if (glfwWindowShouldClose(window)) {
            running = false;
        }
    }
}

void stop()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void start()
{
    running = true;
    run();
    stop();
}

int main(int argc, const char * argv[])
{
    start();

    return 0;
}