#pragma once
#include <vector>

class Window;
constexpr int MAX_FPS_VECTOR_SIZE = 10;

class Time
{
	double deltaTime = 0;
	double timeScale = 1;
	double unscaledDeltaTime = 0;
	double currentTime = 0;
	double lastTime = 0;

	std::vector<float> fpsVec;

	float fps = 0;
	float averageFps = 0;
	float fpsAddition = 0;
	float FPSUpdateDelay = 0.5f;
	float lastFPSUpdate = 0.0f;

	void UpdateFPS();
	[[nodiscard]] std::vector<float>& GetFPSVec();
	[[nodiscard]] double GetCurrentTime();

public:
	void UpdateDeltaTime();


	void ToggleVSync(Window& window, bool input);

	void SetFPSUpdateDelay(const float newDelay);

	[[nodiscard]] float GetFPSUpdateDelay();
	[[nodiscard]] float GetFPS();
	[[nodiscard]] float GetAverageFPS();

	[[nodiscard]] double GetDeltaTime();
	[[nodiscard]] double GetTimeScale();
	[[nodiscard]] double GetUnscaledDeltaTime();

	void SetTimeScale(const double& newTimeScale);
};