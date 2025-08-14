#include "engine/macros.h"
#include "engine/shaders.h"

#include <lux.h>
#include <stdio.h>

void on_resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void on_error(const char* desc)
{
    printf("\033[31merror\033[0m %s\n", desc);
}

int main()
{
    lx_init((lx_init_props){
        .title = "Nyx",
        .width = 1280,
        .height = 720,
        .on_resize = on_resize,
        .on_error = on_error,
    });

    unsigned int main_shader = create_shader_vf(RESOURCE("shaders/default.vert"), RESOURCE("shaders/default.frag")); 

    while (lx_is_alive())
    {
        lx_poll_events();

        glUseProgram(main_shader);

        lx_swap_buffers();
    }

    destroy_shader(main_shader);

    lx_quit();
    return 0;
}
