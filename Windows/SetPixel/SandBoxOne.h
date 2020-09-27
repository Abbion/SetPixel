#pragma once
#include "setPixel.h"
#include <chrono>

class SandBoxOne
{
public:
	SandBoxOne();
    void update();

private:
    sp::PixelWindow m_window;
    sp::Event m_event;
    sp::Camera m_camera;
};