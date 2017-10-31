// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <common/glComp.h>
#include <common/glfwWindow.hpp>
#include <glm/glm.hpp> // Include GLM
#include <common/shaders.h>
using namespace glm;

GLuint program;
GLuint vertexbuffer;

void init_triangle(){
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // Preparing data
    GLuint VertexArrayID; // VAOs
    glGenVertexArrays(1, &VertexArrayID); // allocate some number (name) for a vertex array.
    glBindVertexArray(VertexArrayID); // create a new vertex-array object and assigned to the given number (name)
    
    const GLfloat g_vertex_buffer_data[] = {
         -0.90f, -0.90f,
          0.85f, -0.90f,
         -0.90f,  0.85f,  // Triangle 1
          0.90f, -0.85f,
          0.90f,  0.90f,
         -0.85f,  0.90f   // Triangle 2
    };
    
    glGenBuffers(1, &vertexbuffer); // VBOs
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    // Preparing shaders
    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER, "vertShader.vertshader" },
        { GL_FRAGMENT_SHADER, "fragShader.fragshader" },
        { GL_NONE, NULL }
    };
    program = LoadShaders(shaders);
}

void display(){
    glClear( GL_COLOR_BUFFER_BIT ); // Clear the screen
    // Drawing
    //  Set the render program
    glUseProgram(program);
    //  Set the data to be rendered
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0,           // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          2,           // size
                          GL_FLOAT,    // type
                          GL_FALSE,    // normalized
                          0,           // stride
                          BUFFER_OFFSET(0)     // array buffer offset
                          );
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

int main( void )
{
    glfwWindow glWin = glfwWindow();
    if (!glWin.Init("01 first window")) // Initialize GLFW
        return -1;
    glWin.computeFPS(true);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n Type anykey to exit...\n");
        getchar();
        glWin.Terminate();
        return -1;
    }

    init_triangle();
    glWin.Frame(&display);
    glWin.Terminate();
    
    return 0;
}

