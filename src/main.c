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
        .title = "Lux Test",
        .width = 1280,
        .height = 720,

        .on_resize = on_resize,
        .on_error = on_error,
    });


    printf("\033[?1049h");

    while (lx_is_alive())
    {
        lx_poll_events();

        printf("\033[2J");
        printf("\033[H");
        printf("gl version %g\n", lx_get_loaded_gl_version());
        printf("fps %lf\n", lx_get_fps());

        lx_swap_buffers();
    }

    printf("\033[?1049l");
    lx_quit();
    return 0;
}
