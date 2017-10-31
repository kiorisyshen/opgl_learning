#include "shaders.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

GLuint LoadShaders(ShaderInfo* shaders){
    if (shaders == NULL) return 0;
    GLuint programID = glCreateProgram();
    ShaderInfo* entry = shaders;
    // loop for all shaders
    while ( entry->type != GL_NONE ) {
        printf("Loading shader : %s\n", entry->filename);
        GLuint shaderID = glCreateShader(entry->type);
        entry->shaderID = shaderID;
        
        // Read the Vertex Shader code from the file
        std::string strShaderCode;
        std::ifstream shaderStream(entry->filename, std::ios::in);
        if(shaderStream.is_open()){
            std::string Line = "";
            while(getline(shaderStream, Line))
                strShaderCode += "\n" + Line;
            shaderStream.close();
        }else{
            printf("Impossible to open %s for loading shaders.\n Press any key to exit...\n", entry->filename);
            glDeleteShader( shaderID );
            entry->shaderID = 0;
            getchar();
            return 0;
        }
        printf("Loading shader done!\n");
        
        // Compile Shader
        printf("Compiling shader : %s\n", entry->filename);
        const char* shaderCode = strShaderCode.c_str();
        glShaderSource(shaderID, 1, &shaderCode, NULL);
        glCompileShader(shaderID);
        
        // Check Shader
        GLint compiled = GL_FALSE;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
        if ( !compiled ) {
            GLsizei InfoLogLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if ( InfoLogLength > 0 ){
                std::vector<char> shaderErrorMessage(InfoLogLength+1);
                glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
                printf("%s\n", &shaderErrorMessage[0]);
            }
        }else{
            printf("Compiling done!\n");
        }
        
        glAttachShader( programID, shaderID );
        ++entry;
    }
    
    // Link the program
    printf("Linking program\n");
    glLinkProgram(programID);
    
    // Check the program
    GLint linked = GL_FALSE;
    glGetProgramiv( programID, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        GLsizei InfoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }
        for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
            glDetachShader(programID, entry->shaderID);
            glDeleteShader(entry->shaderID);
            entry->shaderID = 0;
        }
    }else{
        printf("Linking done!\n");
    }
    
    // Clean created shader
    for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
        glDetachShader(programID, entry->shaderID);
        glDeleteShader(entry->shaderID);
        entry->shaderID = 0;
    }
    
    return programID;
}
