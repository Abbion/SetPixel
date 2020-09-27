#include "spFileLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>

sp::ModelLoader::ModelLoader(const std::string& path)
{
    loadFromFlie(path);
    buildModel();
}

sp::ModelLoader::~ModelLoader()
{
    m_modelData.clear();
    m_vertexData.clear();
    m_faceElements.clear();
}

void sp::ModelLoader::loadFromFlie(const std::string& path)
{
    std::fstream file;
    file.open(path);
    if(!file.good())
    {
        std::cout << "Couldn't load " << path << std::endl;
        return;
    }
    else
    {
        std::string str;
        std::getline(file, str);
        while (str[0] != 'v')
        {
            std::getline(file, str);
        }

        while (str[0] == 'v' && str[1] == ' ')
        {
            loadVertex(str);
            std::getline(file, str);
        }

        while (str[0] != 'f')
        {
            std::getline(file, str);
        }
        
        while (str[0] == 'f')
        {
            loadFaceElements(str);
            std::getline(file, str);
        }
        
    }
}

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

void sp::ModelLoader::loadFaceElements(const std::string& str)
{
    std::string intStr;
    std::istringstream strStream(str);
    sp::vector3i temp;

    std::getline(strStream, intStr, ' ');
    std::getline(strStream, intStr, '/');
    temp.x = std::stoi(intStr);

    std::getline(strStream, intStr, ' ');
    std::getline(strStream, intStr, '/');
    temp.y = std::stoi(intStr);

    std::getline(strStream, intStr, ' ');
    std::getline(strStream, intStr, '/');
    temp.z = std::stoi(intStr);

    m_faceElements.push_back(temp);
}

void sp::ModelLoader::buildModel()
{
    for (int i = 0; i < m_faceElements.size(); i++)
    {
        m_modelData.push_back(m_vertexData[m_faceElements[i].x - 1]);
        m_modelData.push_back(m_vertexData[m_faceElements[i].y - 1]);
        m_modelData.push_back(m_vertexData[m_faceElements[i].z - 1]);
    }

    m_vertexData.clear();
    m_faceElements.clear();
}