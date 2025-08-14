#pragma once

unsigned int create_shader_vf(const char* vert_file, const char* frag_file);
void destroy_shader(unsigned int program);
