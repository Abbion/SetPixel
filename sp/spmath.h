#ifndef SP_MATH_H_
#define SP_MATH_H_

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
        vector2f(float v_x, float v_y) { x = v_x; y = v_y; }
        vector2f() { x = 0; y = 0; }
        float x, y;
    };

    struct coordConverter
    {
        static vector2f normalToView(const vector2f& normal);

        static int m_renderWidth, m_renderHeight;
    };

    vector2f subtractVec2f(const vector2f& vec_1, const vector2f& vec_2);
    vector2i subtractVec2i(const vector2i& vec_1, const vector2i& vec_2);
    void scaleVec2(vector2f& vec_1, float scale);
    void scaleVec2(vector2f& vec_1, float scale_x, float scale_y);

    void changeValues(float* val_1, float* val_2);
    
    float lengthVec2(const  vector2f& vec_1);
    float distanceVec2(const vector2f& vec_1, const vector2f& vec_2);
    float getLineSlope(const vector2f& vec_1, const vector2f& vec_2);
};

#endif // !SP_MATH_H_
