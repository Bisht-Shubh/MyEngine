#pragma once

#include <Windows.h>
#include <psapi.h>

class DebugLayer
{
public:
	size_t GetMemoryUsage();
	void SetShaderLoadTime(int time);
	int  GetShaderLoadTime() const;

private:
	int m_shaderLoadTime{ 0 };
};

