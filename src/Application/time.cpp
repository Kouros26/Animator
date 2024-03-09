#include "Application/time.hpp"

#include "Application/window.hpp"

float Time::GetFPS()
{
	return fps;
}

float Time::GetAverageFPS()
{
	return averageFps;
}

std::vector<float>& Time::GetFPSVec()
{
	return fpsVec;
}

void Time::UpdateFPS()
{
	if (currentTime - lastFPSUpdate < FPSUpdateDelay) return;

	fps = static_cast<float>(1 / deltaTime);
	lastFPSUpdate = currentTime;

	fpsVec.push_back(fps);

	const int size = fpsVec.size();
	if (size > MAX_FPS_VECTOR_SIZE)
	{
		fpsAddition -= fpsVec[0];
		fpsVec.erase(fpsVec.begin());
	}

	fpsAddition += fps;
	averageFps = fpsAddition / size;
}

void Time::ToggleVSync(Window& window, const bool input)
{
	window.ToggleVSync(input);
}

void Time::SetFPSUpdateDelay(const float newDelay)
{
	FPSUpdateDelay = newDelay;
}

float Time::GetFPSUpdateDelay()
{
	return FPSUpdateDelay;
}

void Time::UpdateDeltaTime()
{
	currentTime = glfwGetTime();
	unscaledDeltaTime = currentTime - lastTime;
	deltaTime = timeScale * unscaledDeltaTime;
	lastTime = currentTime;

	UpdateFPS();
}

double Time::GetDeltaTime()
{
	return deltaTime;
}

double Time::GetTimeScale()
{
	return timeScale;
}

double Time::GetUnscaledDeltaTime()
{
	return unscaledDeltaTime;
}

double Time::GetCurrentTime()
{
	return currentTime;
}

void Time::SetTimeScale(const double& newTimeScale)
{
	timeScale = newTimeScale;
}