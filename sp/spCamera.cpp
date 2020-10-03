#include "spCamera.h"
#include "spKeyboard.h"
#include "spMouse.h"

sp::Camera::Camera(SP_FLOAT nearPlane, SP_FLOAT farPlane, SP_FLOAT angle) :
    m_near(nearPlane), m_far(farPlane), m_angle(angle)
{ 
    m_position = sp::vector3f(0.0, 0.0, 3.0);
    m_forward = sp::vector3f(0.0, 0.0, -1.0);
    m_up = sp::vector3f(0.0, 1.0, 0.0);
    m_woldUP = m_up;
}

void sp::Camera::update()
{
    if (sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::W))
        m_position += m_forward * m_speed;

    if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::S))
        m_position -= m_forward * m_speed;

    if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::D))
        m_position += m_right * m_speed;

    if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::A))
        m_position -= m_right * m_speed;

    if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::K))
        sp::Mouse::hideMouse(false);
    if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::KeyCode::O))
        sp::Mouse::hideMouse(true);

    Mouse::getDeltaMousePosition(&m_deltaMousePos.x, &m_deltaMousePos.y);
    //std::cout << m_deltaMousePos.x << m_deltaMousePos.y << std::endl; 
    if(m_deltaMousePos.y != 0)
    {
        SP_FLOAT speed = m_deltaMousePos.y * m_mouseSnesitivity;
        m_pitch += speed;
        if(m_pitch > 89.0)
            m_pitch = 89.0;
        if(m_pitch < -89.0)
            m_pitch = -89.0;
    }

    if(m_deltaMousePos.x != 0)
    {
        SP_FLOAT speed = m_deltaMousePos.x * m_mouseSnesitivity;
        m_yaw += speed;
    }
}

sp::Matrix4 sp::Camera::getCameraTransform()
{

    sp::vector3f m_direction;
    
    m_direction.x = std::cos(SP_DEGTORAD * m_yaw) * std::cos(SP_DEGTORAD * m_pitch);
    m_direction.y = std::sin(SP_DEGTORAD * m_pitch);
    m_direction.z = std::sin(SP_DEGTORAD * m_yaw) * std::cos(SP_DEGTORAD * m_pitch);
    m_forward = sp::getNormal(m_direction);
    m_right = sp::getNormal(sp::getCrossProduct(m_forward, m_woldUP));
    m_up = sp::getNormal(sp::getCrossProduct(m_right, m_forward));

    
    sp::Matrix4 cameraMatrix = sp::Transform::lookAt(m_position, m_position + m_forward, m_up);
    return cameraMatrix;
}

std::vector<sp::vector3f> sp::Camera::getCameraClipPlanes() const
{
    std::vector<sp::vector3f> planes;

    sp::vector3f nearInWorld = m_position + (m_forward * m_near);
    sp::vector3f farInWorld = m_position + (m_forward * m_far);
    planes.push_back(nearInWorld);
    planes.push_back(m_forward);
    planes.push_back(farInWorld);
    planes.push_back(m_forward * (-1));

    return planes;
}