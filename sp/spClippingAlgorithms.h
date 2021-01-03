#ifndef _SP_CLIPPING_ALGORITHMS_H_
#define _SP_CLIPPING_ALGORITHMS_H_
#include <vector>
#include "spVector.h"
#include "spCamera.h"

namespace sp
{
    //Face culling algorithm
    bool faceCulling(const sp::vector3f& a, const sp::vector3f& b, const sp::vector3f& c);


    //Clipping algorithms
    //Clipps triangles to an array of planes
    bool clipTriangleToPlanes(const std::vector<sp::vector3f>& input, int start, int offset, std::vector<sp::vector3f>& output, const std::vector<sp::vector3f>& planes);

    //Functions used for clipping
    static int countPointsOut(std::vector<sp::vector3f>& data, int offset, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane);
    static void compareToPlaneWithFragments(std::vector<sp::vector3f>& data, SP_FLOAT* relative, const sp::vector3f& onPlane, const sp::vector3f& normalPlane);
    static void compareToPlane(std::vector<sp::vector3f>& data, SP_FLOAT* relative,  const sp::vector3f& onPlane, const sp::vector3f& normalPlane);
    static sp::vector3f getIntersectionPoint(const sp::vector3f& pointOnPlane, const sp::vector3f& normalToPlane, const sp::vector3f& lineStart, const sp::vector3f& lineEnd);
}


#endif //_SP_ALGORITHMS_