#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <array>

class Window
{
// public functions
public:
	Window(int width = 800, int height = 600, std::string name = "Game");
	Window(const Window& src);
	~Window();

	int Init();

	// returns the width of the viewport
	GLint GetBufferWidth() const { return bufferWidth; }
	// returns the height of the viewport
	GLint GetBufferHeight() const { return bufferHeight; }

	GLint GetWindowWidth()const { return width; }
	GLint GetWindowHeight()const { return height; }

	GLboolean GetShouldClose() const { return glfwWindowShouldClose(window); }
	void SetShouldClose(bool shouldClose) { glfwSetWindowShouldClose(window, shouldClose); }

	void DisableCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
	void EnableCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

	void SwapBuffers() { glfwSwapBuffers(window); }
	void PollEvents(){ glfwPollEvents(); }

	// check if a key is being pressed, for example by passing "GLFW_KEY_A" as argument
	bool IsKeyPressed(int keyCode) const { return keys[keyCode]; }

// public variables
public:

// private functions
private:
	static void KeyCallback(GLFWwindow* window, int key, int code, int action, int mode);
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

// private variables
private:
	GLint width{};
	GLint height{};
	GLint bufferWidth{};
	GLint bufferHeight{};
	std::string name{};

	std::array<bool, 1024> keys{};

	GLFWwindow* window{};
};

