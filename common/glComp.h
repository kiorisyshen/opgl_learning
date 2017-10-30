#ifndef glComp_h
#define glComp_h

#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <GL/glew.h>
    #else
        #include <OpenGLES/ES3/gl.h>
    #endif
#elif defined _WIN32 || defined _WIN64
    #include <GL/glew.h>
#elif defined __ANDROID__
    #include <GLES/gl.h>
#endif

#define BUFFER_OFFSET(offset) ((void *)(offset))

#endif /* glComp_h */
