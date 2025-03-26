#include "engine/render.h"
#include "engine/bindings.h"

const char* vertex_source = "					\n\
#version 330 core								\n\
layout (location = 0) in vec3 pos;				\n\
void main()										\n\
{												\n\
	gl_Position = vec4(pos, 1.0);				\n\
}";

const char* fragment_source = "					\n\
#version 330 core								\n\
out vec4 FragColor;								\n\
void main()										\n\
{												\n\
	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);	\n\
}";

float vertices[] = {
	0.0f,  0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
};

unsigned int create_shader()
{
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);

	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

unsigned int create_triangle()
{
	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vao;
}

int main()
{
	window* window = window_new("Nyx", 1920, 1080);
	load_gl_bindings();

	unsigned int shader = create_shader();
	unsigned int vao = create_triangle();

	while (!window_should_close(window))
	{
		window_update(window);

		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		window_render(window);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(shader);

	window_destroy(window);

	return 0;
}
