#pragma once
class Input
{
public:
	//Input();
	//~Input();

	void OnKeyPressed(int key, int action);
	void OnKeyReleased(int key);

	bool IsKeyPressed(int key); 
	bool IsKeyReleased(int key);

	void OnMouseMove(double xpos, double ypos);
	void OnMouseButtonPressed(int button, int action);

	bool IsMouseButtonPressed(int button) const;

	float GetMouseXOffset() const;
	float GetMouseYOffset() const;

	float GetMouseX() const;
	float GetMouseY() const;

	void ResetMouseDelta();

private:
	bool m_keys[1024];
	bool m_keysReleased[1024];

	double m_lastX{ 0.0f };
	double m_lastY{ 0.0f };
	
	bool m_firstMouse{ true };
	bool m_mouseButtons[8] {};

	float m_MouseXOffset{ 0.0f };
	float m_MouseYOffset{ 0.0f };
};
