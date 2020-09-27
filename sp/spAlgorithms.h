#ifndef _SP_ALGORITHMS_
#define _SP_ALGORITHMS_
#include "spVector.h"
#include "spCamera.h"
#include <vector>

namespace sp
{
    bool faceCulling(const sp::vector3f& a, const sp::vector3f& b, const sp::vector3f& c);

    void clipToCamera(std::vector<sp::vector3f>& vertexVec, const sp::Camera& cam);
    bool clipTriangleToPlanes(const sp::vector3f& a, const sp::vector3f& b, const sp::vector3f& c, std::vector<sp::vector3f>& output, const std::vector<sp::vector3f>& planes);


    static int countPointsOut(std::vector<sp::vector3f>& vertex, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane);
    static void compareToPlane(std::vector<sp::vector3f>& vertex, int out, SP_FLOAT* relative,  const sp::vector3f& onPlane, const sp::vector3f& normalPlane);

    static sp::vector3f getIntersectionPoint(const sp::vector3f& pointOnPlane, const sp::vector3f& normalToPlane, const sp::vector3f& lineStart, const sp::vector3f& lineEnd);
    static int clipTriangleToPlane(const sp::vector3f& pointOnPlane, const sp::vector3f& normalToPlane, std::vector<sp::vector3f>& vertexVec);
}


#endif //_SP_ALGORITHMS_