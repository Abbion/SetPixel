#include "setPixel.h"
#include <iostream>
#include <chrono>

int main()
{
	sp::PixelWindow MyWindow(800, 600, "Set_pixel graphical lib");	//150, 100
	sp::Event event;

	MyWindow.setPixelSize(4);
	float time = 0.0f;

	bool sth = false;

	//float testTriangle[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f }; 

	float cx_1 = 0.0f;
	float cy_1 = 0.0f;
	float cx_2 = 0.0f;
	float cy_2 = 0.0f;
	float spped = 0.01f;
	
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

		if (sp::Keyboard::getKeyPress(sp::Keyboard::KeyCode::E))
		{
			MyWindow.setSize(900, 900);
		}

		//sp::drawable dp_line = sp::lineLI(sp::vector2f(-0.5f, 0.5f), sp::vector2f(0.5f, -0.5f));

		//sp::drawable dp_triangle = sp::triangle(testTriangle);
		//sp::drawable dp_triangle_fill =  sp::fill(dp_triangle, testTriangle, 6);

		/*
		sp::BitMap pixelTest(sp::vector2i(50, 50), sp::vector2i(4, 4));
		pixelTest.pixel_map[0] = 1;
		pixelTest.pixel_map[1] = 1;
		pixelTest.pixel_map[2] = 1;
		pixelTest.pixel_map[3] = 1;
		pixelTest.pixel_map[4] = 1;
		pixelTest.pixel_map[7] = 1;
		pixelTest.pixel_map[8] = 1;
		pixelTest.pixel_map[11] = 1;
		pixelTest.pixel_map[12] = 1;
		pixelTest.pixel_map[13] = 1;
		pixelTest.pixel_map[14] = 1;
		pixelTest.pixel_map[15] = 1;
		*/
		
		float x_1 = cos(time) / 2;
		float y_1 = sin(time) / 2;
		float x_2 = 2 * cos(2 * time);
		float y_2 = 2 * cos(3 * time);

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::A))
			cx_1 -= spped;
		
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::D))
			cx_1 += spped;

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::W))
			cy_1 += spped;

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::S))
			cy_1 -= spped;

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::Left))
			cx_2 -= spped;

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::Right))
			cx_2 += spped;

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::Up))
			cy_2 += spped;

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::Down))
			cy_2 -= spped;
		
		if(sp::Keyboard::getKeyPress(sp::Keyboard::F))
		{
			sth = !sth;
			MyWindow.showFps(sth);
		}
		
		//sp::BitMap lineTest = sp::line(sp::vector2f(-0.3f, 0.1f), sp::vector2f(0.3f, -0.1f));
		//sp::BitMap lineTest = sp::line(sp::vector2f(cx_1, cy_1), sp::vector2f(cx_2, cy_2));
		//sp::BitMap lineTest2 = sp::line(sp::vector2f(x_1, y_1), sp::vector2f(x_2, y_2));
		//sp::BitMap lineTest2 = sp::line(sp::vector2f(-0.5f, 0.5f), sp::vector2f(0.5f, -0.5f));
		//lineTest2.marge(lineTest);

		sp::BitMap triangle[4] =   {sp::line(sp::vector2f(-0.5f, -0.5f), sp::vector2f(-0.5f, 0.5f)),
									sp::line(sp::vector2f(-0.5f, 0.5f), sp::vector2f(0.5f, 0.5f)),
									sp::line(sp::vector2f(0.5f, 0.5f), sp::vector2f(0.5f, -0.5f)),
									sp::line(sp::vector2f(0.5f, -0.5f), sp::vector2f(-0.5f, -0.5f))};

		sp::BitMap triangle_marged;
		triangle_marged.marge(triangle, 4);
		triangle_marged.fill();
		
		MyWindow.clear();
		//MyWindow.draw(lineTest);
		//MyWindow.draw(lineTest2);
		MyWindow.draw(triangle_marged);;
		MyWindow.display();

		//lineTest.clear();
		//lineTest2.clear();
		triangle_marged.clear();
		

		time += 0.008f;
		
	}

	return 0;
}


/*
vector2i getRenderSpaceFromNormalized(const vector2f& coords);      //Converts normalized coordinates to window coordinates.
//-----------------------------------------------------
sp::vector2i sp::RendererBase::getRenderSpaceFromNormalized(const vector2f& coords)
{
    vector2i renderCoords((m_renderSpaceWidth / 2.0f) * (coords.x + 1), (m_renderSpaceHeight / 2.0f) * (coords.y + 1));
    return renderCoords;
}
//-----------------------------------------------------
*/