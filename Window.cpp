#include "pch.h"
#include "Window.h"

Window::Window(unsigned int width, unsigned int height, Input& input)
	: m_Width(width), m_Height(height), m_input(input) {}

Window::~Window()
{
	if (m_window)
		glfwDestroyWindow(m_window);

	glfwTerminate();
}

void Window::InitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

	m_window = glfwCreateWindow(m_Width, m_Height, "AISE", NULL, NULL);
    if(m_window == NULL)
    {
        std::cout << "DEBUG::ERROR::Failed to create GLFW window" << std::endl;
        glfwTerminate();
		std::exit(EXIT_FAILURE);
    }

	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);	
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(this->m_window, mouseCallBack);
	glfwSetMouseButtonCallback(this->m_window, mouseButtonCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "DEBUG::ERROR::Failed to initialize GLAD" << std::endl;
		std::exit(EXIT_FAILURE);
	}  

	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	
	
	//glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow* Window::GetWindow() const
{
	return m_window;
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

unsigned int Window::GetWidth() const
{
	return m_Width;
}

unsigned int Window::GetHeight() const
{
	return m_Height;
}

void Window::Update()
{
	glfwPollEvents();	

	if (m_input.IsKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(m_window, true);
}

void Window::framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode)
{
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

	self->m_input.OnKeyPressed(key, action);
}

void Window::mouseCallBack(GLFWwindow* glfwWindow, double xPos, double yPos)
{
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

	self->m_input.OnMouseMove(xPos, yPos);
}

void Window::mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
{
	auto* self = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

	if(self)
		self->m_input.OnMouseButtonPressed(button, action);
}
