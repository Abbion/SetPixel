#include "spModelLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>


//-----------------------------------------------------
sp::ModelLoader::ModelLoader(const std::string& path, bool texture)
{
    m_texture = texture;
    loadFromFlie(path);
    buildModel();
}
//-----------------------------------------------------


//-----------------------------------------------------
sp::ModelLoader::~ModelLoader()
{
    m_modelData.clear();
    m_vertexData.clear();
    m_faceElements.clear();
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::ModelLoader::loadFromFlie(const std::string& path)
{
    std::fstream file;
    file.open(path);
    if (!file.good())
    {
        std::cout << "Couldn't load " << path << std::endl;
        return;
    }
    else
    {
        std::string str;
        std::getline(file, str);
        //Skip to vertex data
        while (str[0] != 'v')
        {
            std::getline(file, str);
        }

        //Load vertex data
        while (str[0] == 'v' && str[1] == ' ')
        {
            loadVertex(str);
            std::getline(file, str);
        }

        if (m_texture)
        {
            while (str[1] == 't')
            {
                loadTextureCoordinates(str);
                std::getline(file, str);
            }
        }

        //Skip to face elements
        while (str[0] != 'f')
        {
            std::getline(file, str);
        }

        //Read face elements
        while (str[0] == 'f')
        {
            loadFaceElements(str);
            std::getline(file, str);
        }

    }
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::ModelLoader::loadVertex(const std::string& str)
{
    std::string floatStr;
    std::istringstream strStream(str);
    sp::vector3f temp;

    std::getline(strStream, floatStr, ' ');
    std::getline(strStream, floatStr, ' ');
    temp.x = std::stof(floatStr);
    std::getline(strStream, floatStr, ' ');
    temp.y = std::stof(floatStr);
    std::getline(strStream, floatStr, ' ');
    temp.z = std::stof(floatStr);

    m_vertexData.push_back(temp);
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::ModelLoader::loadTextureCoordinates(const std::string& str)
{
    std::string floatStr;
    std::istringstream strStream(str);
    sp::vector3f temp;

    std::getline(strStream, floatStr, ' ');
    std::getline(strStream, floatStr, ' ');
    temp.x = std::stof(floatStr);
    std::getline(strStream, floatStr, ' ');
    temp.y = std::stof(floatStr);
    temp.z = 0.0;

    m_textureCoordData.push_back(temp);
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::ModelLoader::loadFaceElements(const std::string& str)
{
    std::string intStr;
    std::istringstream strStream(str);
    sp::vector3i vertexTemp;
    sp::vector3i textureTemp;

    std::getline(strStream, intStr, ' ');
    std::getline(strStream, intStr, '/');
    vertexTemp.x = std::stoi(intStr);
    if (m_texture)
    {
        std::getline(strStream, intStr, '/');
        textureTemp.x = std::stoi(intStr);
    }

    std::getline(strStream, intStr, ' ');
    std::getline(strStream, intStr, '/');
    vertexTemp.y = std::stoi(intStr);
    if (m_texture)
    {
        std::getline(strStream, intStr, '/');
        textureTemp.y = std::stoi(intStr);
    }

    std::getline(strStream, intStr, ' ');
    std::getline(strStream, intStr, '/');
    vertexTemp.z = std::stoi(intStr);
    if (m_texture)
    {
        std::getline(strStream, intStr, '/');
        textureTemp.z = std::stoi(intStr);
    }

    m_faceElements.push_back(vertexTemp);
    if (m_texture)
        m_faceElements.push_back(textureTemp);
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::ModelLoader::buildModel()
{
    if (m_texture)
    {
        for (int i = 0; i < m_faceElements.size(); i += 2)
        {
            m_modelData.push_back(m_vertexData[m_faceElements[i].x - 1]);
            m_modelData.push_back(m_textureCoordData[m_faceElements[i + 1].x - 1]);

            m_modelData.push_back(m_vertexData[m_faceElements[i].y - 1]);
            m_modelData.push_back(m_textureCoordData[m_faceElements[i + 1].y - 1]);

            m_modelData.push_back(m_vertexData[m_faceElements[i].z - 1]);
            m_modelData.push_back(m_textureCoordData[m_faceElements[i + 1].z - 1]);
        }
    }
    else
    {
        for (int i = 0; i < m_faceElements.size(); i++)
        {
            m_modelData.push_back(m_vertexData[m_faceElements[i].x - 1]);
            m_modelData.push_back(m_vertexData[m_faceElements[i].y - 1]);
            m_modelData.push_back(m_vertexData[m_faceElements[i].z - 1]);
        }
    }

    m_vertexData.clear();
    m_faceElements.clear();
}
//-----------------------------------------------------