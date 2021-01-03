#ifndef _SP_FRAGMENTS_MAPPER_H_
#define _SP_FRAGMENTS_MAPPER_H_
#include <vector>

#include "spColor.h"
#include "spVector.h"
#include "spPixel.h"
#include "spBitMap.h"
#include "spBitMapLoader.h"

namespace sp
{
    //Set of functions to map color to bitmaps
    PixelList fillWithColor(const std::vector<sp::vector3f>& data, sp::BitMap& bm, const BitMapTexture* texture = nullptr); //Change to FillWithFragments
    void buildFragment(const std::vector<sp::vector2i> viewData, const sp::vector2i& pos, const SP_FLOAT& preCalculatedDivisor, const std::vector<sp::vector3f>& data, bool hasTexture, const BitMapTexture* texture, sp::PixelList& pixelList);
    sp::vector3f interpolateFragment(const std::vector<sp::vector2i> viewData, const sp::vector2i& pos, const SP_FLOAT& preCalculatedDivisor);//Interpolates using pythagorean theorem
    sp::Pixel generateFragment(const std::vector<sp::vector3f>& colorData, const sp::vector3f& interpolation, const sp::vector2i& pos);
    sp::Pixel generateFragment(const std::vector<sp::vector3f>& TextureData, const sp::vector3f& interpolation, const sp::vector2i& pos, const BitMapTexture* texture);

    sp::Pixel generatePixel(const std::vector<sp::vector2i> viewData, const std::vector<sp::vector3f>& colorData, const sp::vector2i& pos); //Interpolates in triangle coordiantes (NOT WORKING)
}


#endif //PIXELMAP