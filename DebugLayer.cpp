#include "pch.h"
#include "DebugLayer.h"

size_t DebugLayer::GetMemoryUsage()
{
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
	{
		return pmc.WorkingSetSize; // Return memory usage in bytes
	}
	return 0; // Return 0 if unable to retrieve memory info
}

void DebugLayer::SetShaderLoadTime(int time)
{
	m_shaderLoadTime = time;
}	

int DebugLayer::GetShaderLoadTime() const
{
	return m_shaderLoadTime;
}
