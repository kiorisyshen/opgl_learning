#ifndef glfwWindow_hpp
#define glfwWindow_hpp

// Include GLFW
#include <GLFW/glfw3.h>

class glfwWindow{
public:
    GLFWwindow* window = NULL;
    bool Init(int WWidth=1024, int WHeight=768, const char* WTittle="opgl_learning");
    void Frame(void (*userDisplay)());
    void Terminate();
};

#endif /* glfwWindow_hpp */
