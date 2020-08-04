#ifndef SP_VECTOR_H_
#define SP_VECTOR_H_
#include "coreDefines.h"

namespace sp {
    struct vector2i
    {
        vector2i(int v_x, int v_y) { x = v_x; y = v_y; }
        vector2i() { x = 0; y = 0; }

        vector2i operator+(vector2i& vec_2) 
        { 
            vector2i sum;
            sum.x = this->x + vec_2.x;
            sum.y = this->y + vec_2.y;
            return sum;
        }

        vector2i operator-(vector2i& vec_2) 
        { 
            vector2i sub;
            sub.x = this->x - vec_2.x;
            sub.y = this->y - vec_2.y;
            return sub;
        }

        int x, y;
    };




    
    struct vector2f
    {
        vector2f(SP_FLOAT v_x, SP_FLOAT v_y) { x = v_x; y = v_y; }
        vector2f() { x = 0; y = 0; }
        SP_FLOAT x, y;
    };





    struct coordConverter
    {
        static vector2f normalToView(const vector2f& normal);

        static int m_renderWidth, m_renderHeight;
    };



    

    vector2f subtractVec2f(const vector2f& vec_1, const vector2f& vec_2);
    vector2i subtractVec2i(const vector2i& vec_1, const vector2i& vec_2);
    void scaleVec2(vector2f& vec_1, SP_FLOAT scale);
    void scaleVec2(vector2f& vec_1, SP_FLOAT scale_x, SP_FLOAT scale_y);

    void changeValues(SP_FLOAT* val_1, SP_FLOAT* val_2);
    
    SP_FLOAT lengthVec2(const  vector2f& vec_1);
    SP_FLOAT distanceVec2(const vector2f& vec_1, const vector2f& vec_2);
    SP_FLOAT getLineSlope(const vector2f& vec_1, const vector2f& vec_2);
};

#endif // !SP_VECTOR_H_
