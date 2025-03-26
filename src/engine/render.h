#pragma once

typedef struct _window window;

window* window_new(const char* title, int width, int height);
void window_destroy(window* window);

void window_update(window* window);
void window_render(window* window);

int	window_should_close(window* window);
