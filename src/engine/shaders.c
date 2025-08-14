#include "shaders.h"

#include <lux.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int _create_shader(unsigned int type, const char* file)
{
    const char* source = lx_read_file(file);
    if (source == NULL)
        return 0; 

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    char log[512];
    int success;

    free((void*)source);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        printf("error compiling shader >> %s", log);
        return 0;
    }

    return shader;
}

unsigned int create_shader_vf(const char* vert_file, const char* frag_file)
{
    unsigned int vs = _create_shader(GL_VERTEX_SHADER, vert_file);
    if (vs == 0)
        return 0;

    unsigned int fs = _create_shader(GL_FRAGMENT_SHADER, frag_file);
    if (fs == 0)
    {
        glDeleteShader(vs);
        return 0;
    }

    unsigned int sp = glCreateProgram();
    glAttachShader(sp, vs);
    glAttachShader(sp, fs);
    glLinkProgram(sp);

    glDeleteShader(vs);
    glDeleteShader(fs);

    char log[512];
    int success;

    glGetProgramiv(sp, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(sp, 512, NULL, log);
        printf("error linking program >> %s", log);
        return 0;
    }

    return sp;
}

void destroy_shader(unsigned int program)
{
    glDeleteProgram(program);
}
