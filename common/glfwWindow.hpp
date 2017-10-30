#ifndef glfwWindow_hpp
#define glfwWindow_hpp

// Include GLFW
#include <GLFW/glfw3.h>

class glfwWindow{
private:
    GLFWwindow* window = NULL;
    bool useFPS = false;
    
public:
    bool Init(const char* WTittle="opgl_learning", int WWidth=1024, int WHeight=768);
    void Frame(void (*userDisplay)());
    void Terminate();
    
    void computeFPS(bool yorn){useFPS = yorn;};
};

#endif /* glfwWindow_hpp */
