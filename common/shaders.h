#ifndef shaders_hpp
#define shaders_hpp

#include "glComp.h"

typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shaderID;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo* );

#endif /* shaders_hpp */
