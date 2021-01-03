#ifndef _SP_MODEL_H
#define _SP_MODEL_H
#include <vector>
#include "spMath.h"
#include "spBitMap.h"
#include "spCamera.h"
#include "spPixel.h"
#include "spBitMapLoader.h"

namespace sp {
	//3D model structure
	enum fillType
	{
		NONE,
		COLOR,
		TEXTURE
	};

	struct Model
	{
		sp::BitMap bm;
		std::vector<PixelList> plv;
	};

    sp::Model GenerateModel(std::vector<sp::vector3f>& vertexVec, fillType type, const BitMapTexture* texture = nullptr, bool faceCulling = true, bool switchCullingDirection = false);
};

#endif