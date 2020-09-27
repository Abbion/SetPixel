#ifndef SP_CAMERA_H_
#define SP_CAMERA_H_
#include "coreDefines.h"
#include "spmath.h"
#include <vector>

namespace sp{
    class Camera
    {
    public:
        Camera(SP_FLOAT nearPlane, SP_FLOAT farPlane, SP_FLOAT angle);

        void update();
        sp::Matrix4 getCameraTransform();
        std::vector<sp::vector3f> getCameraClipPlanes() const;

        SP_FLOAT getNear() { return m_near; }
        SP_FLOAT getFar() { return m_far; }

    private:
        sp::vector3f m_position;
        sp::vector3f m_forward;
        sp::vector3f m_up;
        sp::vector3f m_right;
        sp::vector3f m_woldUP;

        SP_FLOAT m_pitch = 0;
        SP_FLOAT m_yaw = -90;
        SP_FLOAT m_near;
        SP_FLOAT m_far;
        SP_FLOAT m_angle;
        SP_FLOAT m_speed = 0.04;
        SP_FLOAT m_mouseSnesitivity = 0.1f;
        SP_FLOAT m_rotationSpeed = 0.5f;

        sp::vector2i m_deltaMousePos;
    };
}


#endif //SP_CAMERA_H_