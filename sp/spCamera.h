#ifndef _SP_CAMERA_H_
#define _SP_CAMERA_H_
#include <vector>
#include "spCoreDefined.h"
#include "spMath.h"


namespace sp
{
    //Camera class for 3D projection
    class Camera
    {
    public:
        Camera(SP_FLOAT nearPlane, SP_FLOAT farPlane, SP_FLOAT angle);

        SP_FLOAT getNear() const { return m_near; }
        SP_FLOAT getFar() const { return m_far; }
        sp::Matrix4 getCameraTransform();
        std::vector<sp::vector3f> getCameraClipPlanes() const;

        void update();

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