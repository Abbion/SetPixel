#include "SandBoxOne.h"
#include <vector>


SandBoxOne::SandBoxOne() : m_window(800, 600, "SandBoxOne"), m_camera(0.5, 10, 90)
{
    m_window.setPixelSize(2);
    m_window.showFps(true);
	sp::Mouse::lockMouse(true);
	sp::Mouse::hideMouse(true);
}

void SandBoxOne::update()
{
    sp::vector3f moveIner[3] = {sp::vector3f(0.0, -2.0, -2.0), sp::vector3f(1.5, -0.5, -4.0), sp::vector3f(4, 2, -4)};

	double pos_x = 0;
	double pos_y = 0;
	double pos_z = -2.0;

	double scal_x2 = 0.0;
	double scal_y2 = 0.0;

	double rot_x = 0.0;
	double rot_y = 0.0;
	double rot_z = 0.0;

	sp::ModelLoader test("E:/Silniki/3. SetPixel/Models/Cat.obj", false);

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

		bool rot = false;
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Space))
			rot = true;

		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Numpad_4))
		{
			if (rot) rot_y -= 0.5;
			else pos_x -= 0.05;
		}
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Numpad_6))
		{
			if (rot) rot_y += 0.5;
			else pos_x += 0.05;
		}
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Numpad_8))
		{
			if (rot) rot_x += 0.5;
			else pos_y += 0.05;
		}
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Numpad_2))
		{
			if (rot) rot_x -= 0.5;
			else pos_y -= 0.05;
		}
		if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::Numpad_5)) 
		{
			int inv = 1;
			if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::L_ctrl))
				inv = -1;
			if (rot) rot_z += 0.5 * inv;
			else pos_z += 0.05 * inv;
		}

		sp::Matrix4 M1;
		sp::Matrix4 move = sp::Transform::translate(sp::vector3f(pos_x, pos_y, pos_z));
		sp::Matrix4 rotate = sp::Transform::rotate(sp::vector3f(rot_x, rot_y, rot_z));
		sp::Matrix4 projection = sp::Transform::cameraProjectionMatrix(0.5, 5, 39.6);
		sp::Matrix4 view = m_camera.getCameraTransform();
		M1 = rotate * move * view * projection;
        //M1 = projection * view * move * rotate;
		m_window.clear();

		for(int i = 0; i < 1; i++)
		{
			/*
			std::vector<sp::vector3f> cubeVec = { sp::vector3f(-0.5f, 0.5f, 0.5f), sp::vector3f(-0.5f, -0.5f, 0.5f), sp::vector3f(0.5f,  -0.5f, 0.5f),	//Front
									  sp::vector3f(-0.5f, 0.5f, 0.5f), sp::vector3f(0.5f,  -0.5f, 0.5f), sp::vector3f(0.5f, 0.5f, 0.5f),
						
									  sp::vector3f(-0.5f, 0.5f,  0.5f), sp::vector3f(-0.5f, 0.5f,  -0.5f), sp::vector3f(-0.5f,  -0.5f,  0.5f),	//Left
									  sp::vector3f(-0.5f, 0.5f,  -0.5f), sp::vector3f(-0.5f,  -0.5f,  -0.5f), sp::vector3f(-0.5f, -0.5f,  0.5f),
									
								      sp::vector3f(-0.5f,  0.5f,  0.5f), sp::vector3f(0.5f,  0.5f, 0.5f), sp::vector3f(-0.5f, 0.5f, -0.5f),	//Top
									  sp::vector3f(0.5f,  0.5f, 0.5f), sp::vector3f(0.5f, 0.5f,  -0.5f), sp::vector3f(-0.5f,  0.5f,  -0.5f),

									  sp::vector3f(0.5f,  0.5f,  0.5f), sp::vector3f(0.5f,  -0.5f, 0.5f), sp::vector3f(0.5f, -0.5f, -0.5f),	//Right
							          sp::vector3f(0.5f, -0.5f, -0.5f), sp::vector3f(0.5f, 0.5f, -0.5f), sp::vector3f(0.5f,  0.5f,  0.5f),

							          sp::vector3f(-0.5f, -0.5f, 0.5f), sp::vector3f(-0.5f, -0.5f, -0.5f), sp::vector3f(0.5f, -0.5f,  0.5f),	//Bottom
									  sp::vector3f(0.5f, -0.5f,  0.5f), sp::vector3f(-0.5f, -0.5f,  -0.5f), sp::vector3f(0.5f, -0.5f, -0.5f),

									  sp::vector3f(-0.5f,  -0.5f, -0.5f), sp::vector3f(-0.5f,  0.5f, -0.5f), sp::vector3f(0.5f,  -0.5f,  -0.5f),	//Back
									  sp::vector3f(-0.5f,  0.5f,  -0.5f), sp::vector3f(0.5f,  0.5f,  -0.5f), sp::vector3f(0.5f,  -0.5f, -0.5f)
									 
			};
			*/
			auto model = test.getModelData();

			sp::Matrix4 moveIn = sp::Transform::translate(moveIner[i]);
			M1 = moveIn;
			//sp::Transform::applyTransform(model, M1);

			M1 = view * projection;
			sp::Transform::applyTransform(model, M1, false);
			

			sp::Model cubeMesh = sp::GenerateModel(model, sp::fillType::COLOR);	//VIEW CLIPPING HERE
			m_window.draw(cubeMesh.bm);
		}
		m_window.display();
	}
}