#include "spFragmentsMapper.h"
#include "math.h"
#include <limits>


//Color filling algorithm------------------------------
sp::PixelList sp::fillWithColor(const std::vector<sp::vector3f>& data, sp::BitMap& bm, const BitMapTexture* texture)
{
    bool hasTexture = false;
    if (texture != nullptr)
        hasTexture = true;

    sp::PixelList pixelList;
    std::vector<sp::vector2i> viewData = {  sp::coordConverter::normalToViewPosI(sp::vector2f(data[0].x, data[0].y)),
                                            sp::coordConverter::normalToViewPosI(sp::vector2f(data[2].x, data[2].y)),
                                            sp::coordConverter::normalToViewPosI(sp::vector2f(data[4].x, data[4].y))};

    SP_FLOAT preCalculatedDivisor = ((viewData[1].y - viewData[2].y) * (viewData[0].x - viewData[2].x)) + ((viewData[2].x - viewData[1].x) * (viewData[0].y - viewData[2].y));
    if (preCalculatedDivisor == 0.0)
        preCalculatedDivisor = 1.0/1000000.0;

    for (int i = 0; i < bm.m_size.y; i++)
    {
        int vertical = i * bm.m_size.x;
        bool hit = false;
        int start = -1;
        int end = -1;

        for (int j = 0; j < bm.m_size.x; j++)
        {
            //Find first hitpoint
            if(!hit && bm.m_bitMapData[vertical + j] == 1)
            {
                int k = j + 1;
                sp::vector2i pos = sp::vector2i(bm.m_startPos.x + j, bm.m_startPos.y + i);
                buildFragment(viewData, pos, preCalculatedDivisor, data, hasTexture, texture, pixelList);

                //Edge
                while (bm.m_bitMapData[vertical + k] && k < bm.m_size.x)
                {
                    sp::vector2i pos = sp::vector2i(bm.m_startPos.x + k, bm.m_startPos.y + i);
                    buildFragment(viewData, pos, preCalculatedDivisor, data, hasTexture, texture, pixelList);
                    k++;
                }
                
                j = k;
                start = j;
                hit = true;
            }

            //End edge hit
            else if(hit && bm.m_bitMapData[vertical + j] == 1)
            {
                sp::vector2i pos = sp::vector2i(bm.m_startPos.x + j, bm.m_startPos.y + i);
                buildFragment(viewData, pos, preCalculatedDivisor, data, hasTexture, texture, pixelList);
                int k = j + 1;

                //Edge
                while (bm.m_bitMapData[vertical + k] && k < bm.m_size.x)
                {
                    sp::vector2i pos = sp::vector2i(bm.m_startPos.x + k, bm.m_startPos.y + i);
                    buildFragment(viewData, pos, preCalculatedDivisor, data, hasTexture, texture, pixelList);
                    k++;
                }

                end = j;
                break;
            }
        }
        
        if(start > -1 && end > - 1)
        {
            for (int k = start; k < end; k++)
            {
                sp::vector2i pos = sp::vector2i(bm.m_startPos.x + k, bm.m_startPos.y + i);
                buildFragment(viewData, pos, preCalculatedDivisor, data, hasTexture, texture, pixelList);
            }
        }
    }

    return pixelList;
}
//-----------------------------------------------------


//Creates a fragment and checks if it is non alpha-----
void sp::buildFragment(const std::vector<sp::vector2i> viewData, const sp::vector2i& pos, const SP_FLOAT& preCalculatedDivisor, const std::vector<sp::vector3f>& data, bool hasTexture, const BitMapTexture* texture, sp::PixelList& pixelList)
{
    sp::vector3f interpolation = interpolateFragment(viewData, pos, preCalculatedDivisor);
    if (hasTexture)
    {
        sp::Pixel pix = generateFragment(data, interpolation, pos, texture);
        if (texture->hasAlpha())
        {
            if(texture->getAlphaColor() != pix.getColor())
                pixelList.push_front(pix);
        }
        else
        {
            pixelList.push_front(pix);
        }
    }
    else
        pixelList.push_front(generateFragment(data, interpolation, pos));
}
//-----------------------------------------------------


//Interpolates fragment color--------------------------
sp::vector3f sp::interpolateFragment(const std::vector<sp::vector2i> viewData, const sp::vector2i& pos, const SP_FLOAT& preCalculatedDivisor)
{
    SP_FLOAT inverse[3];

    inverse[0] = std::abs((SP_FLOAT)(((viewData[1].y - viewData[2].y) * (pos.x - viewData[2].x)) + (( viewData[2].x - viewData[1].x)*( pos.y - viewData[2].y))) / preCalculatedDivisor);

    inverse[1] = std::abs((SP_FLOAT)(((viewData[2].y - viewData[0].y) * (pos.x - viewData[2].x)) + ((viewData[0].x - viewData[2].x) * (pos.y - viewData[2].y))) / preCalculatedDivisor);

    inverse[2] = 1 - inverse[0] - inverse[1];

    for (int i = 0; i < 3; i++)
    {
        if (inverse[i] < 0)
            inverse[i] = 0.0;
        else if (inverse[i] > 1)
            inverse[i] = 1.0;
    }

    return sp::vector3f(inverse[0], inverse[1], inverse[2]);
}
//-----------------------------------------------------


//Calculates the exact color value---------------------
sp::Pixel sp::generateFragment(const std::vector<sp::vector3f>& colorData, const sp::vector3f& interpolation, const sp::vector2i& pos)
{
    sp::Color col;
    col.red =   ((interpolation.x * colorData[1].x + interpolation.y * colorData[3].x + interpolation.z * colorData[5].x) / 1.0) * 255;
    col.green = ((interpolation.x * colorData[1].y + interpolation.y * colorData[3].y + interpolation.z * colorData[5].y) / 1.0) * 255;
    col.blue =  ((interpolation.x * colorData[1].z + interpolation.y * colorData[3].z + interpolation.z * colorData[5].z) / 1.0) * 255;

    SP_FLOAT depth = (interpolation.x * colorData[0].z + interpolation.y * colorData[2].z + interpolation.z * colorData[4].z);

    return sp::Pixel(pos, col, depth);
}
//-----------------------------------------------------


//Calcuates the exact color value using textures-------
sp::Pixel sp::generateFragment(const std::vector<sp::vector3f>& TextureData, const sp::vector3f& interpolation, const sp::vector2i& pos, const sp::BitMapTexture* texture)
{
    sp::vector2f TexCoords;
    TexCoords.x = (interpolation.x * TextureData[1].x + interpolation.y * TextureData[3].x + interpolation.z * TextureData[5].x) / 1.0;
    TexCoords.y = (interpolation.x * TextureData[1].y + interpolation.y * TextureData[3].y + interpolation.z * TextureData[5].y) / 1.0;

    if (TexCoords.x > 1.0)        TexCoords.x = 1.0;
    else if (TexCoords.x < 0.0)   TexCoords.x = 0.0;
    
    if (TexCoords.y > 1.0)        TexCoords.y = 1.0;
    else if (TexCoords.y < 0.0)   TexCoords.y = 0.0;
    
    SP_FLOAT depth = (interpolation.x * TextureData[0].z + interpolation.y * TextureData[2].z + interpolation.z * TextureData[4].z);
    
    return sp::Pixel(pos, texture->sampleFragment(TexCoords), depth);
}
//-----------------------------------------------------


//Calculates the exact color value usinge the triangle coordinate system
sp::Pixel sp::generatePixel(const std::vector<sp::vector2i> viewData, const std::vector<sp::vector3f>& data, const sp::vector2i& pos)
{
    sp::vector2i posTranslated = sp::vector2i(pos.x - viewData[0].x, pos.y - viewData[0].y);

    sp::vector2f vec_1 = sp::vector2f(viewData[1].x, viewData[1].y) - sp::vector2f(viewData[0].x, viewData[0].y);
    sp::vector2f vec_2 = sp::vector2f(viewData[2].x, viewData[2].y) - sp::vector2f(viewData[1].x, viewData[1].y);

    SP_FLOAT sx = (posTranslated.x * vec_1.y - posTranslated.y * vec_1.x) / (vec_2.x * vec_1.y - vec_2.y * vec_1.x);
    SP_FLOAT sy = (posTranslated.x - vec_2.x * sx) / vec_1.x;

    if (sx > 1)         sx = 1;
    else if (sx < 0)    sx = 0;
    if (sy > 1)         sy = 1;
    else if (sy < 0)    sy = 0;

    sp::vector3f int_1 = data[1] * (1 - sy) + data[3] * sy;
    sp::vector3f int_2 = int_1 * (1 - sx) + data[5] * sx;

    return sp::Pixel(pos, sp::Color(255 * int_2.x, 255 * int_2.y, 255 * int_2.z));
}
//-----------------------------------------------------