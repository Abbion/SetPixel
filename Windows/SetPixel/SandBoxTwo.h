#pragma once
#include "setPixel.h"
#include <chrono>

class SandBoxTwo
{
public:
	SandBoxTwo();
	void update();

private:
	sp::PixelWindow m_window;
	sp::Event m_event;
	sp::Camera m_camera;
};