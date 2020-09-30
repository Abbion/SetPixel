#ifndef _SP_FILE_LOADER_H_
#define _SP_FILE_LOADER_H_
#include <vector>
#include <string>
#include "spVector.h"

namespace sp{

class ModelLoader
{
public:
    ModelLoader(const std::string& path);
    ~ModelLoader();

    std::vector<sp::vector3f> getModelData() { return m_modelData; }

private:
    std::vector<sp::vector3f> m_modelData;
    std::vector<sp::vector3f> m_vertexData;
    std::vector<sp::vector3i> m_faceElements;

private:
    void loadFromFlie(const std::string& path);
    void loadVertex(const std::string& str);
    void loadFaceElements(const std::string& str);

    void buildModel();

};
}


#endif //SP_FILE_LOADER