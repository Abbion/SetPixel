#include "setPixel.h"
#include <iostream>
#include <chrono>

int main()
{
	sp::PixelWindow MyWindow(800, 600, "Set_pixel graphical lib");	//150, 100
	sp::Event event;

	MyWindow.setPixelSize(4);
	
	sp::vector2f p1(-0.5f, -0.5f);
	sp::vector2f c1(0.0f, -0.5f);
	sp::vector2f p2(0.5f, 0.5f);
	sp::vector2f c2(0.0f, 0.5f);

	float time = 0.0f;

	double pos_x = -0.4;
	double pos_y = 0.5;

	double pos_x2 = 0.4;
	double pos_y2 = -0.5;
	MyWindow.showFps(true);

	while (MyWindow.isOpen())
	{
		while (MyWindow.peekEvents())
		{
			MyWindow.getNextEvent(event);
			sp::Keyboard::updateKeyMap(event);
			sp::Mouse::updateButtonMap(event);
		}

		if (sp::Keyboard::getKeyPress(sp::Keyboard::KeyCode::Esc))
		{
			MyWindow.close();
		}

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::A))
			pos_x -= 0.01;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::D))
			pos_x += 0.01;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::W))
			pos_y += 0.01;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::S))
			pos_y -= 0.01;

		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Left))
			pos_x2 -= 0.01;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Right))
			pos_x2 += 0.01;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Up))
			pos_y2 += 0.01;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Down))
			pos_y2 -= 0.01;

		//sp::BitMap lineTest = sp::lineLI(sp::vector2f(-0.5f, 0.0f), sp::vector2f(0.5f, 0.0f));
		//sp::QuadraticBezier bezTest(sp::vector2f(-0.5, 0.0), sp::vector2f(0.5, 0.0), sp::vector2f(pos_x, pos_y));
		//bezTest.drawControlPoints();
		sp::CubicBezier bezTest(sp::vector2f(-0.5, 0.0), sp::vector2f(0.5, 0.0), sp::vector2f(pos_x, pos_y), sp::vector2f(pos_x2, pos_y2), 8);
		bezTest.drawControlPoints();
		//sp::BitMap rectTest = sp::Rectangle(sp::vector2f(-0.5f, 0.5f), sp::vector2f(1.0f, 1.0f));
		//sp::BitMap linetest = sp::line(sp::vector2f(-0.3f, -0.7f), sp::vector2f(0.3f, 0.7f));
		sp::BitMap circleTest = sp::Circle(sp::vector2f(0.0, 0.0), 0.2);

		MyWindow.clear();
		//MyWindow.draw(bezTest.getDrawable());
		MyWindow.draw(circleTest);
		MyWindow.display();
		time += 0.01f;

	}

	return 0;
}
