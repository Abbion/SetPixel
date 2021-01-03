#include "spBitMap.h"


//==============BITMAP==============
sp::BitMap::BitMap() :
    m_startPos(sp::vector2i(0, 0)) , m_size(sp::vector2i(0, 0)), m_bitMapData(nullptr)
{
}


sp::BitMap::BitMap(const vector2i& pos, const vector2i& size) :
    m_startPos(pos), m_size(size)
{
    m_size.x;
    m_size.y;
    int full_size = m_size.x * m_size.y;

    m_bitMapData = new bool[full_size];
    memset(m_bitMapData, 0, full_size);    //Clear mapData
}


sp::BitMap::BitMap(const BitMap& bm)
{
    this->m_startPos = bm.m_startPos;                   //Copy position
    this->m_size = bm.m_size;                           //Copy size
    this->m_bitMapData = bm.m_bitMapData;               //Copy ptr to mapData
    const_cast<BitMap*>(&bm)->m_bitMapData = nullptr;   //Delete pointer to mapData
}

sp::BitMap::~BitMap()
{
    clear();
}
//-----------------------------------------------------


//-----------------------------------------------------
sp::BitMap& sp::BitMap::operator=(const BitMap& bm)
{
    this->clear();                                      //Delete last mapData
    this->m_startPos = bm.m_startPos;                   //Copy position
    this->m_size = bm.m_size;                           //Copy size
    this->m_bitMapData = bm.m_bitMapData;             //Copy ptr to mapData
    const_cast<BitMap*>(&bm)->m_bitMapData = nullptr;  //Delete pointer to mapData
    return *this;
}
//-----------------------------------------------------

void sp::BitMap::clear()
{
    if(m_bitMapData != nullptr){
        delete[] m_bitMapData;
        m_bitMapData = nullptr;
    }
}

//-----------------------------------------------------
void sp::BitMap::marge(BitMap& bm)  //Margeing to one object
{
    //Calcuating new bitmap size----
    vector2i new_pos = this->m_startPos;
    vector2i new_sum_size = this->m_size + new_pos;
    calculateNewRect(bm, &new_pos, &new_sum_size);
    
    vector2i new_size = new_sum_size - new_pos;
    BitMap marged(new_pos, new_size);
    //------------------------------

    //Margeing----------------------
    margeToBitMap(marged, *this);
    margeToBitMap(marged, bm);
    //------------------------------

    this->clear();                                          //Delete last mapData
    this->m_startPos = marged.m_startPos;                   //Copy position
    this->m_size = marged.m_size;                           //Copy size
    this->m_bitMapData = marged.m_bitMapData;               //Copy ptr to mapData
    marged.m_bitMapData = nullptr;
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

    this->clear();                                          //Delete last mapData
    this->m_startPos = marged.m_startPos;                   //Copy position
    this->m_size = marged.m_size;                           //Copy size
    this->m_bitMapData = marged.m_bitMapData;               //Copy ptr to mapData
    marged.m_bitMapData = nullptr;
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
            if(bm.m_bitMapData[itr])  //If there is a pixel
                target.m_bitMapData[y_start + j] = 1;
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

    for (int i = 0; i < m_size.y; i++)      //Every row
    {
        int y_pos = i * m_size.x;           //Calculate row number

        for (int j = 0; j < m_size.x; j++)  //Every column
        {
            if(m_bitMapData[y_pos + j])    //If there is a pixel
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
        m_bitMapData[i] = 1;    
}
//-----------------------------------------------------