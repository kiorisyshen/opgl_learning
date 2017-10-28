// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h> // Include GLEW
#include <common/glfwWindow.hpp>
#include <glm/glm.hpp> // Include GLM
using namespace glm;

void display(){
    glClear( GL_COLOR_BUFFER_BIT ); // Clear the screen
    // Drawing
}

int main( void )
{
    glfwWindow glWin = glfwWindow();
    if (!glWin.Init()) // Initialize GLFW
        return -1;
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n Type anykey to exit...\n");
        getchar();
        glWin.Terminate();
        return -1;
    }
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    glWin.Frame(&display);
    glWin.Terminate();
    
    return 0;
}

