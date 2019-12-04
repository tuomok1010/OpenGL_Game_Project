#include "Window.h"

#include <iostream>


Window::Window(int width, int height, std::string name)
	: width(width), height(height), name(name)
{
	Init();
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Window::Init()
{
	// init GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	// we need this for the callback functions
	glfwSetWindowUserPointer(window, this);

	// register callback functions
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	glfwSetKeyCallback(window, KeyCallback);

	return 0;
}

void Window::KeyCallback(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		currentWindow->SetShouldClose(true);
	}

	if (key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
			currentWindow->keys[key] = true;
		else if(action == GLFW_RELEASE)
			currentWindow->keys[key] = false;
	}
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	currentWindow->bufferWidth = width;
	currentWindow->bufferHeight = height;
	glViewport(0, 0, width, height);
}
