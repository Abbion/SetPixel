#include "spBitMapLoader.h"
#include <fstream>

//==============BITMAP_LOADER==============
sp::BitMapTexture::BitMapTexture(const std::string& filepath, bool vFlip, bool alpha, const sp::Color& alphaColor)
{
    m_alphaColor = alphaColor;
    m_alpha = alpha;
    load(filepath, vFlip);
}


sp::BitMapTexture::~BitMapTexture()
{
    if (m_data != nullptr)
        delete[] m_data;
}
//-----------------------------------------------------


//Get pixel color using normalized coordinate system---
sp::Color sp::BitMapTexture::sampleFragment(const sp::vector2f& pos) const
{
    int pixelPosX = (int)((m_width) * pos.x);
    int pixelPosY = (int)((m_height - 1) * pos.y);
    int finalPixelPos = 3 * (pixelPosY * m_width + pixelPosX);

    return sp::Color(m_data[finalPixelPos], m_data[finalPixelPos + 1], m_data[finalPixelPos + 2]);
}
//-----------------------------------------------------


//Get image width and height--------------------------
sp::vector2i sp::BitMapTexture::getSize() const
{
    return sp::vector2i(m_width, m_height);
}
//----------------------------------------------------


//Check if image has alpha value set-------------------
bool sp::BitMapTexture::hasAlpha() const
{
    return m_alpha;
}
//----------------------------------------------------


//Returns the color of the alpha color-----------------
const sp::Color sp::BitMapTexture::getAlphaColor() const
{
    return m_alphaColor;
}
//----------------------------------------------------


//Free data-------------------------------------------
void sp::BitMapTexture::FreeData()
{
    if(m_data != nullptr)
        delete[] m_data;
}
//----------------------------------------------------


//Open file, check image type, load image in memory---
bool sp::BitMapTexture::load(const std::string& filepath, const bool VFlip)
{
    std::fstream file;
    file.open(filepath.c_str(), std::ios::in | std::ios::binary);

    if(!file.good())
    {
        std::cout << "Can't open file: " << filepath << std::endl;
        file.close();
        return false;
    }

    if(!m_LoadBMP(file, VFlip))
    {
        std::cout << "File corrupted: " << filepath << std::endl;
        return false;
    }

    return true;
}
//----------------------------------------------------


//Flip verticaly the image------------------------------
void sp::BitMapTexture::VerticalFlip()
{
    unsigned int BufforSize = 3 * m_width * m_height;
    unsigned int BitesInRow = 3 * m_width;
    unsigned char* tempRowOfPixels = new unsigned char[BitesInRow];
    

    //If column of pixels is even-----------------------
    if(m_height % 2 == 0)
    {
        for(int i = 0; i < m_height / 2; i++)
        {
            for(int j = 0; j < BitesInRow; j++)
            {
                tempRowOfPixels[j] = m_data[(i * BitesInRow) + j];
                m_data[(i * BitesInRow) + j] = m_data[BufforSize - ((i + 1) * BitesInRow) + j];
                m_data[BufforSize - ((i + 1) * BitesInRow) + j] = tempRowOfPixels[j];
            }
        }
    }
    //--------------------------------------------------


    //If column of pixels is odd------------------------
    else
    {
        for(int i = 0; i < (m_height - 1) / 2; i++)
        {
            for(int j = 0; j < BitesInRow; j++)
            {
                tempRowOfPixels[j] = m_data[(i * BitesInRow) + j];
                m_data[(i * BitesInRow) + j] = m_data[BufforSize - ((i + 1) * BitesInRow) + j];
                m_data[BufforSize - ((i + 1) * BitesInRow) + j] = tempRowOfPixels[j];
            }
        }
    }
    //--------------------------------------------------

    delete[] tempRowOfPixels;
}
//------------------------------------------------------


//Loading bmp image-------------------------------------
bool sp::BitMapTexture::m_LoadBMP(std::fstream& file, const bool VFlip)
{
    //Check if it is really a bmp image-----------------
    file.seekg(0, file.beg);
    unsigned char HaeaderCheck[2];
    file.read((char*)HaeaderCheck, 2);

    if(HaeaderCheck[0] != 'B' || HaeaderCheck[1] != 'M')
        return false;
    //---------------------------------------------------


    //Get Info Header size-------------------------------
    file.seekg(14, file.beg);
    unsigned char InfoHeaderBits[4];
    file.read((char*)InfoHeaderBits, 4);

    int InfoHeaderSize = *(int*)&InfoHeaderBits[0];
    //---------------------------------------------------


    //Get Info Header data-------------------------------
	unsigned char* InfoHeaderData = new unsigned char[InfoHeaderSize-4];
    file.read((char*)InfoHeaderData, InfoHeaderSize-4);

    if(InfoHeaderSize == 12)
    {
        m_width = *(short*)&InfoHeaderData[0];
        m_height = *(short*)&InfoHeaderData[2]; 
    }
    else
    {
        m_width = *(int*)&InfoHeaderData[0];
        m_height = *(int*)&InfoHeaderData[4];          
    }

     delete[] InfoHeaderData;
    //---------------------------------------------------


    //Get color data-------------------------------------
	//>>>>>>>>>>ONLY 24 AND 32 BIT IMAGES!!!<<<<<<<<<<<<<
	unsigned int BufforSize = 3 * m_width * m_height;
    file.seekg(14 + InfoHeaderSize, file.beg);

    m_data = new unsigned char[BufforSize];
    file.read((char*)m_data, BufforSize);
	file.close();
	//---------------------------------------------------


	//Sort data from BGR to RGB------------------------
	unsigned int Pixels = m_width * m_height;

	unsigned char tempBite;
	for (int i = 0; i < Pixels; i++)
	{
			tempBite = m_data[i * 3 + 2];
			m_data[i * 3 + 2] = m_data[i * 3];
			m_data[i * 3] = tempBite;
	}
	//---------------------------------------------------


    //Normaly the image is upside down so we can flip it-
    if(VFlip)
        VerticalFlip();
    //---------------------------------------------------


	return true;
}
//------------------------------------------------------