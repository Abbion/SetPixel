#include "SandBoxTwo.h"
#include "spAlgorithms.h"

SandBoxTwo::SandBoxTwo() : m_window(800, 600, "SandBoxOne"), m_camera(0.2, 5.0, 90)
{
	m_window.setPixelSize(4);
	m_window.showFps(true);
}

void SandBoxTwo::update()
{
	SP_FLOAT x_offset = 0;
	SP_FLOAT y_offset = 0;
	SP_FLOAT rot = 0.0;
	SP_FLOAT scl = 1.0;

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

		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::D))
			x_offset += 0.01;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::A))
			x_offset -= 0.01;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::W))
			y_offset += 0.01;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::S))
			y_offset -= 0.01;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Left))
			rot += 0.5;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Right))
			rot -= 0.5;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Up))
			scl += 0.01;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Down))
			scl -= 0.01;

		sp::vector3f triData[3] = { sp::vector3f(-0.5, -0.5, 0.0), sp::vector3f(0.5, -0.5, 0.0), sp::vector3f(0.0, 0.5, 0.0) };
		sp::Matrix4 M1;
		sp::Matrix4 translate = sp::Transform::translate(sp::vector3f(x_offset, y_offset, 0));
		sp::Matrix4 rotate = sp::Transform::rotateByZ(rot);
		sp::Matrix4 scale = sp::Transform::scale(sp::vector3f(scl, scl, scl));
		M1 = scale * rotate * translate;
	
		std::vector<sp::vector3f> output;

		sp::Transform::applyTransform(triData, 3, M1);

		//sp::clipTriangleToView(triData[0], triData[1], triData[2], output, cam);
		sp::BitMap tri;

		for (int i = 0; i < output.size(); i += 3)
		{
			sp::BitMap tri2 = sp::Triangle(output[i], output[i + 1], output[i + 2]);
			tri.marge(tri2);
		}

		m_window.clear();
		m_window.draw(tri);
		m_window.display();
	}
}