// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

// The following line is to favor the high performance NVIDIA GPU if there are multiple GPUs
// Has to be .exe module to be correctly detected.
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// And the AMD equivalent
// Also has to be .exe module to be correctly detected.
extern "C" __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;

// Local Headers
#include "shader.hpp"

using namespace Game;

int window_w = 600;
int window_h = 800;

GLuint rect_vao, rect_vbo;

int main() {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(window_w, window_h, "Character Detective", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

	static const float rect_vertices[] = {
		0.5f,  0.5f,  	// top right
		0.5f, -0.5f,  	// bottom right
		-0.5f, -0.5f,  	// bottom left

		-0.5f,  0.5f, 	// top left 
		0.5f,  0.5f,  	// top right
		-0.5f, -0.5f,  	// bottom left
	};

	glCreateVertexArrays(1, &rect_vao);
	glBindVertexArray(rect_vao);
	glGenBuffers(1, &rect_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, rect_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_VERTEX_ARRAY, 0);

	Shader shader;
	shader.create("vertex.vert");
	shader.attach("vertex.vert");
	shader.create("fragment.frag");
	shader.attach("fragment.frag");
	shader.link();

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		// use program
		shader.activate();
		// draw
		glBindVertexArray(rect_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		shader.deactivate();

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();
    return EXIT_SUCCESS;
}
