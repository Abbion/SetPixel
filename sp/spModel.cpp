#include "spModel.h"
#include "spClippingAlgorithms.h"
#include "spShapes.h"
#include "spFragmentsMapper.h"

//-----------------------------------------------------
sp::Model sp::GenerateModel(std::vector<sp::vector3f>& vertexVec, fillType type, const BitMapTexture* texture, bool faceCulling, bool switchCullingDirection)
{
    //Left Top Right Down 
    std::vector<sp::vector3f> viewPlanes = { sp::vector3f(-1.0, 0.0, 0.0), sp::vector3f(1.0, 0.0, 0.0), sp::vector3f(0.0, 1.00, 0.0), sp::vector3f(0.0, -1.0, 0.0),
                                             sp::vector3f(1.0, 0.0, 0.0),  sp::vector3f(-1.0, 0.0, 0.0), sp::vector3f(0.0, -1.00, 0.0), sp::vector3f(0.0, 1.0, 0.0) };

    int offset = 2;
    if (type == fillType::NONE)
        offset = 1;

    sp::Model finalModel;
    int count = vertexVec.size();
    int blockSize = 3 * offset;

    if (count % blockSize != 0)
    {
        count -= count % blockSize;
    }

    for (int i = 0; i < count; i += blockSize)
    {
        bool showFace = true;
        if (faceCulling)
            showFace = sp::faceCulling(vertexVec[i], vertexVec[i + offset], vertexVec[i + (2 * offset)]);

        if (!switchCullingDirection && showFace)
        {
            std::vector<sp::vector3f> output;
            sp::clipTriangleToPlanes(vertexVec, i, offset, output, viewPlanes);
            int l = 0;

            for (int j = 0; j < output.size(); j += blockSize)
            {
                sp::BitMap triangles = sp::Triangle(output[j], output[j + offset], output[j + (2 * offset)]);
                if (triangles.m_bitMapData != nullptr)
                {
                    finalModel.bm.marge(triangles);

                    if (type == fillType::COLOR)
                    {
                        std::vector<sp::vector3f> framentsInfo(output.begin() + (l * blockSize), output.begin() + ((l + 1) * blockSize));
                        finalModel.plv.push_back(sp::fillWithColor(framentsInfo, triangles));
                    }

                    else if (type == fillType::TEXTURE)
                    {
                        std::vector<sp::vector3f> framentsInfo(output.begin() + (l * blockSize), output.begin() + ((l + 1) * blockSize));
                        finalModel.plv.push_back(sp::fillWithColor(framentsInfo, triangles, texture));
                    }
                }
                l++;
            }
        }
    }
    return finalModel;
}
//-----------------------------------------------------