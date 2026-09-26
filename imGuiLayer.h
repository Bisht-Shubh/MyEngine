#pragma once

struct GLFWwindow;

class imGuiLayer
{
public:
	void Init(GLFWwindow* window);
	void BeginFrame();
	void EndFrame();
	void Shutdown();

private:
	bool m_isInitialized = false;
};

