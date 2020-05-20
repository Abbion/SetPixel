#ifndef _SP_WINDOW_BASE_
#define _SP_WINDOW_BASE_

//Base class for os specific window classes.
namespace sp
{
class WindowBase
{
public:
    virtual ~WindowBase() {}

    virtual void setSize(unsigned int width, unsigned int height) = 0;  //To set window size.
    virtual void setPosition(int x_pos, int y_pos) = 0;                 //To set window position.
    virtual void setTitle(const char* title) = 0;                       //To set window title.
    virtual void close() = 0;                                           //To close the window.

    void getSize(int *width, int *height) const;                        //Returns the window size.
    void getPosition(int *x_pos, int *y_pos) const;                     //Returns the window position.

protected:
    int m_x_pos, m_y_pos;
    unsigned int m_width, m_height;
    bool m_running = true;
};
};
#endif
