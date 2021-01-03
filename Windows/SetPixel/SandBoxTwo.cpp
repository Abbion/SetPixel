#include "SandBoxTwo.h"

SandBoxTwo::SandBoxTwo() : m_window(800, 600, "SandBoxOne"), m_camera(0.2, 5.0, 90)
{
	m_window.setPixelSize(4);
	m_window.showFps(true);
	sp::Mouse::lockMouse(true);
	sp::Mouse::hideMouse(true);
}

void SandBoxTwo::update()
{
	SP_FLOAT x_offset = 0;
	SP_FLOAT y_offset = 0;
	SP_FLOAT rot = 0.0;
	SP_FLOAT scl = 1.0;

	sp::ModelLoader model("Spyro.obj", true);
	sp::BitMapTexture tex("Body.bmp", false, true);


	while (m_window.isOpen())
	{
		while (m_window.peekEvents())
		{
			m_window.getNextEvent(m_event);
			sp::Keyboard::updateKeyMap(m_event);
			sp::Mouse::updateButtonMap(m_event);
		}

		if (sp::Keyboard::getKeyPress(sp::Keyboard::KeyCode::Esc))
		{
			m_window.close();
		}

		m_camera.update();

		rot += 1.5;
		std::vector<sp::vector3f> data = model.getModelData();
		
		sp::Matrix4 M1;
		sp::Matrix4 translate = sp::Transform::translate(sp::vector3f(0.0, -1.0, 0.5));
		sp::Matrix4 rotate = sp::Transform::rotateByY(rot);
		sp::Matrix4 scale = sp::Transform::scale(sp::vector3f(0.1f, 0.1f, 0.1f));
		sp::Matrix4 projection = sp::Transform::cameraProjectionMatrix(0.5, 5, 39.6);
		sp::Matrix4 view = m_camera.getCameraTransform();

		M1 = scale * rotate * translate * view * projection;

		sp::Transform::applyTransform(data, M1, 1);

		
		sp::Model tri = sp::GenerateModel(data, sp::fillType::TEXTURE, &tex);

		m_window.clear();
		
		
		for (int i = 0; i < tri.plv.size(); i++)
		{
			m_window.draw(tri.plv[i]);
		}
		
		
		//m_window.draw(tri.bm);
		m_window.display();
	}
}