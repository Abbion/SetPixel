#include "../sp/setPixel.h"
#include <iostream>
#include <chrono>
#include <math.h>


int main()
{
	sp::PixelWindow MyWindow(800, 600, "Set_pixel graphical lib");
	sp::Event event;

	MyWindow.setPixelSize(4);
	MyWindow.showFps(true);

	sp::ModelLoader model("Spyro.obj", true);
	sp::BitMapTexture tex("Body.bmp", false, true);
	
	sp::Camera cam(0.2, 5.0, 90);

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

	cam.update();

	/*
		std::vector<sp::vector3f> triData = {   sp::vector3f(-0.5, -0.5, 0.0), sp::vector3f(1.0, 0.0, 0.0),
												sp::vector3f(0.5, -0.5, 0.0), sp::vector3f(0.0, 1.0, 0.0),
												sp::vector3f(0.0, 0.5, 0.0), sp::vector3f(0.0, 0.0, 1.0) };

	*/

	std::vector<sp::vector3f> data = model.getModelData();
	sp::Matrix4 M1;
	sp::Matrix4 translate = sp::Transform::translate(sp::vector3f(0.0, -1.0, 0.5));
	sp::Matrix4 scale = sp::Transform::scale(sp::vector3f(0.1f, 0.1f, 0.1f));
	sp::Matrix4 projection = sp::Transform::cameraProjectionMatrix(0.5, 5, 39.6);
	sp::Matrix4 view = cam.getCameraTransform();
	M1 = scale * translate * view * projection;

	sp::Transform::applyTransform(data, M1, 1);
	

		sp::Model tri = sp::GenerateModel(data, sp::fillType::TEXTURE, &tex);

		MyWindow.clear();
		for (int i = 0; i < tri.plv.size(); i++)
		{
			MyWindow.draw(tri.plv[i]);
		}
		//MyWindow.draw(tri.bm);
		MyWindow.display();
	}

	return 0;
}