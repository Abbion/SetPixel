#include "SandBoxThree.h"

SandBoxThree::SandBoxThree() : m_window(800, 600, "SandBoxOne"), m_camera(0.2, 5.0, 90)
{
	m_window.setPixelSize(5);
	m_window.showFps(true);
	sp::Mouse::lockMouse(true);
	sp::Mouse::hideMouse(true);
}

void SandBoxThree::update()
{
	SP_FLOAT x_offset = 0;
	SP_FLOAT y_offset = 0;
	SP_FLOAT rot = 0.0;
	SP_FLOAT scl = 0.0;

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
		/*
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::D))
			x_offset += 0.02;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::A))
			x_offset -= 0.02;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::W))
			y_offset += 0.02;
		if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::S))
			y_offset -= 0.02;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Left))
			rot += 2;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Right))
			rot -= 2;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Up))
			scl += 0.05;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Down))
			scl -= 0.05;
			*/

		SP_FLOAT off = 0.0f;
		std::vector<sp::vector3f> triData = {   sp::vector3f(-0.5, -0.5, 0.0), sp::vector3f(0.949, 0.0745, 0.149),			//Lewy dolny
												sp::vector3f(0.5, -0.5, 0.0), sp::vector3f(0.949, 0.0745, 0.149),			//Prawy dolny
												sp::vector3f(-0.5, 0.5, 0.0), sp::vector3f(0.949, 0.0745, 0.149),			//Gorny

												sp::vector3f(0.5, -0.5, 0.0), sp::vector3f(0.949, 0.0745, 0.149),
												sp::vector3f(0.5, 0.5, 0.0), sp::vector3f(0.949, 0.0745, 0.149),
												sp::vector3f(-0.5, 0.5, 0.0), sp::vector3f(0.949, 0.0745, 0.149),

												//--------
												sp::vector3f(-0.5, 0.5, 0.0), sp::vector3f(0.5608, 0.0549, 0.1137),
												sp::vector3f(0.5, 0.5, 0.0), sp::vector3f(0.5608, 0.0549, 0.1137),
												sp::vector3f(0.5, 0.5, -1.0), sp::vector3f(0.5608, 0.0549, 0.1137),

												sp::vector3f(-0.5, 0.5, 0.0), sp::vector3f(0.5608, 0.0549, 0.1137),
												sp::vector3f(0.5, 0.5, -1.0), sp::vector3f(0.5608, 0.0549, 0.1137),
												sp::vector3f(-0.5, 0.5, -1.0), sp::vector3f(0.5608, 0.0549, 0.1137),

												//---------
												sp::vector3f(0.5, -0.5, 0.0), sp::vector3f(0.8118, 0.0784, 0.1647),
												sp::vector3f(0.5, -0.5, -1.0), sp::vector3f(0.8118, 0.0784, 0.1647),
												sp::vector3f(0.5, 0.5, 0.0), sp::vector3f(0.8118, 0.0784, 0.1647),

												sp::vector3f(0.5, 0.5, 0.0), sp::vector3f(0.8118, 0.0784, 0.1647),
												sp::vector3f(0.5, -0.5, -1.0), sp::vector3f(0.8118, 0.0784, 0.1647),
												sp::vector3f(0.5, 0.5, -1.0), sp::vector3f(0.8118, 0.0784, 0.1647),

												//----------
												sp::vector3f(-0.5, -0.5, 0.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(-0.5, 0.5, 0.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(-0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),

												sp::vector3f(-0.5, 0.5, 0.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(-0.5, 0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(-0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),

												//-----------
												sp::vector3f(-0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(-0.5, 0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),

												sp::vector3f(0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(-0.5, 0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(0.5, 0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),

												//--------
												sp::vector3f(-0.5, -0.5, 0.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(0.5, -0.5, 0.0), sp::vector3f(0.3098, 0.0314, 0.0627),

												sp::vector3f(-0.5, -0.5, 0.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(-0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
												sp::vector3f(0.5, -0.5, -1.0), sp::vector3f(0.3098, 0.0314, 0.0627),
        };

		sp::Matrix4 M1;
		sp::Matrix4 translate = sp::Transform::translate(sp::vector3f(x_offset, y_offset, 0));
		sp::Matrix4 rotate = sp::Transform::rotate(sp::vector3f(0.0, 0.0, rot));
		sp::Matrix4 scale = sp::Transform::scale(sp::vector3f(scl, scl, scl));
		sp::Matrix4 projection = sp::Transform::cameraProjectionMatrix(0.5, 5, 39.6);
		sp::Matrix4 view = m_camera.getCameraTransform();

		M1 = rotate * translate * view * projection;

		
		sp::Transform::applyTransform(triData, M1, 1);

        sp::Model tri = sp::GenerateModel(triData, sp::fillType::COLOR);

		m_window.clear();
		for (int i = 0; i < tri.plv.size(); i++)
		{
			m_window.draw(tri.plv[i]);
		}
		m_window.draw(tri.bm);
		m_window.display();
	}
}