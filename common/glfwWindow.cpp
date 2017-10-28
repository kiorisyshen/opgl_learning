#include "glfwWindow.hpp"

#include <stdio.h>

bool glfwWindow::Init(int WWidth, int WHeight, const char* WTittle){
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW.\n Type anykey to exit...\n" );
        getchar();
        return false;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);    // sampling
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // whether the OpenGL context should be forward-compatible
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow( 1024, 768, WTittle, NULL, NULL);
    
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n Type anykey to exit...\n" );
        getchar();
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(window);
    
    // Ensure we can capture the key being pressed
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    return true;
}

void glfwWindow::Frame(void (*userDisplay)()){
    do{
        userDisplay();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           !glfwWindowShouldClose(window) );
}

void glfwWindow::Terminate(){
    if(window != NULL)
        glfwTerminate();
}
