#ifndef _SP_GFX_SHPAES_
#define _SP_GFX_SHAPES_
#include "coreDefines.h"
#include "spmath.h"
#include "pixel.h"
#include "spCamera.h"
#include <vector>

namespace sp{    
    sp::BitMap Triangle(const sp::vector2f& p1, const sp::vector2f& p2, const sp::vector2f& p3);
    sp::BitMap Triangle(const sp::vector3f& p1, const sp::vector3f& p2, const sp::vector3f& p3);
    sp::BitMap Rectangle(sp::vector2f pos, sp::vector2f size);
    sp::BitMap Circle(sp::vector2f pos, SP_FLOAT radius, bool scaleX = false);
    sp::BitMap Elipse(sp::vector2f pos, SP_FLOAT radiusX, SP_FLOAT radiusY);

    sp::BitMap Mesh(sp::vector3f* vertex, int count, sp::Camera& cam, bool faceCulling = true, bool switchCullingDirection = false);
    sp::BitMap Mesh(std::vector<sp::vector3f>& vertexVec, bool faceCulling = true, bool switchCullingDirection = false);
    
    static inline void PlotPointToBitmap(const sp::vector2i& plot, sp::BitMap& bm);
};

#endif