#pragma once
#include "Input.h"

class EditorLayer
{
public:
	EditorLayer();
	void Init();
	void Update(float deltaTime);
	void Render();

private:
	Input& m_input;
};

