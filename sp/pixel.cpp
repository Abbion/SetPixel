#include "pixel.h"
#include <iostream>
#include <string.h>

//==============BITMAP==============
sp::BitMap::BitMap() :
    m_startPos(sp::vector2i(0, 0)) , m_size(sp::vector2i(0, 0)), m_pixelPosMap(nullptr)
{
}


sp::BitMap::BitMap(const vector2i& pos, const vector2i& size) :
    m_startPos(pos), m_size(size)
{
    m_size.x;
    m_size.y;
    int full_size = m_size.x * m_size.y;

    m_pixelPosMap = new bool[full_size];
    memset(m_pixelPosMap, 0, full_size);    //Clear pixelMap
}


sp::BitMap::BitMap(const BitMap& bm)
{
    this->m_startPos = bm.m_startPos;                   //Copy position
    this->m_size = bm.m_size;                           //Copy size
    this->m_pixelPosMap = bm.m_pixelPosMap;             //Copy ptr to pixel_map
    const_cast<BitMap*>(&bm)->m_pixelPosMap = nullptr;  //Delete pointer to pixel map
}

sp::BitMap::~BitMap()
{
    clear();
}
//-----------------------------------------------------


//-----------------------------------------------------
sp::BitMap& sp::BitMap::operator=(const BitMap& bm)
{
    this->clear();                                      //Delete last pixel_map
    this->m_startPos = bm.m_startPos;                   //Copy position
    this->m_size = bm.m_size;                           //Copy size
    this->m_pixelPosMap = bm.m_pixelPosMap;             //Copy ptr to pixel_map
    const_cast<BitMap*>(&bm)->m_pixelPosMap = nullptr;  //Delete pointer to pixel map
    return *this;
}
//-----------------------------------------------------

void sp::BitMap::clear()
{
    if(m_pixelPosMap != nullptr){
        delete[] m_pixelPosMap;
        m_pixelPosMap = nullptr;
    }
}

//-----------------------------------------------------
void sp::BitMap::marge(BitMap& bm)  //Margeing to one object
{
    //Calcuating new bitmap size
    vector2i new_pos = this->m_startPos;
    vector2i new_sum_size = this->m_size + new_pos;
    calculateNewRect(bm, &new_pos, &new_sum_size);
    
    vector2i new_size = new_sum_size - new_pos;
    BitMap marged(new_pos, new_size);
    //------------------------------
    //Margeing
    margeToBitMap(marged, *this);
    margeToBitMap(marged, bm);
    //------------------------------
    //*this = marged;

    this->clear();                                          //Delete last pixel_map
    this->m_startPos = marged.m_startPos;                   //Copy position
    this->m_size = marged.m_size;                           //Copy size
    this->m_pixelPosMap = marged.m_pixelPosMap;             //Copy ptr to pixel_map
    marged.m_pixelPosMap = nullptr;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::BitMap::marge(BitMap* bm, int obj_count)   //Margeing for many objects
{
    //Calcuating new bitmap size
    vector2i new_pos = this->m_startPos;
    vector2i new_sum_size = this->m_size + new_pos;
    calculateNewRect(bm, obj_count, &new_pos, &new_sum_size);
    
    vector2i new_size = new_sum_size - new_pos;
    BitMap marged(new_pos, new_size);
    //-------------------------------

    //Margeing
    margeToBitMap(marged, *this);
    for (int i = 0; i < obj_count; i++)
        margeToBitMap(marged, bm[i]);
    //------------------------------
    //*this = marged;

    this->clear();                                          //Delete last pixel_map
    this->m_startPos = marged.m_startPos;                   //Copy position
    this->m_size = marged.m_size;                           //Copy size
    this->m_pixelPosMap = marged.m_pixelPosMap;             //Copy ptr to pixel_map
    marged.m_pixelPosMap = nullptr;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::BitMap::calculateNewRect(const BitMap& bm, sp::vector2i* pos, sp::vector2i* size)
{
    //Comparing top corners
    if(bm.m_startPos.x < pos->x)
        pos->x = bm.m_startPos.x;
        
    if(bm.m_startPos.y < pos->y)
        pos->y = bm.m_startPos.y;
    //--------------------------
    

        
    //Comparing down corners
    int temp_size_sum = bm.m_size.x + bm.m_startPos.x;
    if(temp_size_sum > size->x)
        size->x = temp_size_sum;

    temp_size_sum = bm.m_size.y + bm.m_startPos.y; 
    if(temp_size_sum > size->y)
        size->y = temp_size_sum;
    //--------------------------
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::BitMap::calculateNewRect(const BitMap* bm, int obj_count, sp::vector2i* pos, sp::vector2i* size)
{
    for (int i = 0; i < obj_count; i++)
    {
        //Comparing top corners
        if(bm[i].m_startPos.x < pos->x)
            pos->x = bm[i].m_startPos.x;
        
        if(bm[i].m_startPos.y < pos->y)
            pos->y = bm[i].m_startPos.y;
        //--------------------------
        


        //Comparing down corners
        int temp_size_sum = bm[i].m_size.x + bm[i].m_startPos.x; 
        if(temp_size_sum > size->x)
            size->x = temp_size_sum;

        temp_size_sum = bm[i].m_size.y + bm[i].m_startPos.y; 
        if(temp_size_sum > size->y)
            size->y = temp_size_sum;
        //--------------------------
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::BitMap::margeToBitMap(BitMap& target, BitMap& bm)
{
    //Bitmap position in the new bitmap
    vector2i start_edge = bm.m_startPos - target.m_startPos; 
    vector2i end_edge = start_edge + bm.m_size;
    //--------------------------

    //Copying data
    int itr = 0;
    for (int i = start_edge.y; i < end_edge.y; i++) //Every row
    {
        int y_start = i * target.m_size.x;  //Calculate row number

        for (int j = start_edge.x; j < end_edge.x; j++) //Every column
        {
            if(bm.m_pixelPosMap[itr])  //If there is a pixel
                target.m_pixelPosMap[y_start + j] = 1;
            itr++;
        }
    }
    //--------------------------
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::BitMap::fill()
{
    bool hit = false;
    int start;

    for (int i = 0; i < m_size.y; i++)  //Every row
    {
        int y_pos = i * m_size.x;   //Calculate row number

        for (int j = 0; j < m_size.x; j++)  //Every column
        {
            if(m_pixelPosMap[y_pos + j]) //If there is a pixel
            {
                if(hit) //Second hit
                {
                    fillLine(start, y_pos + j);
                    hit = false;    //Reset
                }
                else    //Fist hit
                {
                    hit = true;
                    start = y_pos + j;  //Mark position
                }
            }
        }
        hit = false;    //Reset
    }
    
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::BitMap::fillLine(int start, int end)
{
    for (int i = start + 1; i < end; i++)
        m_pixelPosMap[i] = 1;    
}
//-----------------------------------------------------



//-----------------------------------------------------
sp::Pixel::Pixel(int pos_x, int pos_y, const Color& col) :
    m_position(pos_x, pos_y), m_color(col)
{

}

sp::Pixel::Pixel(int pos_x, int pos_y) :
    m_position(pos_x, pos_y), m_color(Color(255, 255, 255))
{

}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Pixel::setPosition(int pos_x, int pos_y)
{
    m_position.x = pos_x;
    m_position.y = pos_y;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::Pixel::setColor(const Color& col)
{
    m_color = col;
}
//-----------------------------------------------------