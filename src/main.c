#include <rias.h>
#include <lux.h> 

int main()
{
    lx_window* window = lx_window_create("Nyx", 1920, 1080);

    while (lx_window_is_alive(window))
    {
        lx_window_update(window);
        lx_window_render(window);
    }

    lx_window_destroy(window);

    return 0;
}
