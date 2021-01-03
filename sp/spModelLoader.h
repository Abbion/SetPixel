#ifndef _SP_FILE_LOADER_H_
#define _SP_FILE_LOADER_H_
#include <vector>
#include <string>
#include "spVector.h"

namespace sp{
    //Loading 3D models (only OBJ)
    class ModelLoader
    {
    public:
        ModelLoader(const std::string& path, bool texture);
        ~ModelLoader();

        std::vector<sp::vector3f> getModelData() const { return m_modelData; }

    private:
        std::vector<sp::vector3f> m_modelData;
        std::vector<sp::vector3f> m_vertexData;
        std::vector<sp::vector3f> m_textureCoordData;
        std::vector<sp::vector3i> m_faceElements;
        bool m_texture;

    private:
        void loadFromFlie(const std::string& path);
        void loadVertex(const std::string& str);
        void loadTextureCoordinates(const std::string& str);
        void loadFaceElements(const std::string& str);

        void buildModel();

    };
}


#endif //SP_FILE_LOADER