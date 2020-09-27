#include "window.h"
#include "mouse.h"
#include "keyboard.h"

#include <iostream>

#include <stdio.h>


//-----------------------------------------------------
bool sp::PixelWindow::m_windowExists = false;
bool sp::PixelWindow::m_panicClose = false;
//-----------------------------------------------------



//==========LINUX IMPLEMENTATION==========
#if unix
sp::PixelWindow::PixelWindow(unsigned int width, unsigned int height, const char* title)
{
    if(m_windowExists)
    {
        fprintf(stderr, "sp::PixelWindow() Can't create a new window because a window already exists.\n");
        fprintf(stderr, "sp::PixelWindow() Be aware that the auto-repeat key might not work.\n");
        m_panicClose = true;
    }

    m_width = width;
    m_height = height;

    m_display = XOpenDisplay(NULL);
    if (m_display == NULL)
    {
        fprintf(stderr, "sp::PixelWindow() Cannot open display.\n");
        exit(1);
    }

    int screen = DefaultScreen(m_display);

    //Create window.
    m_window = XCreateSimpleWindow(m_display, RootWindow(m_display, screen), 0, 0, m_width, m_height, 0,
                           BlackPixel(m_display, screen), BlackPixel(m_display, screen));

    m_windowExists = true;

    //Select the kind of events we are interested in.
    XSelectInput(m_display, m_window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask | FocusChangeMask);
 
    //Map (show) the window.
    XMapWindow(m_display, m_window);
    
    XAutoRepeatOff(m_display);

    //Sets window name.
    XStoreName(m_display, m_window, title);
    XSetIconName(m_display, m_window, title);

    //Sets window position.
    m_x_pos = (XDisplayWidth(m_display, 0) / 2) - (m_width / 2);
    m_y_pos = (XDisplayHeight(m_display, 0) / 2) - (m_height / 2);
    XMoveWindow(m_display, m_window, m_x_pos, m_y_pos);

    //Exit client massage.
    Atom wmDelete = XInternAtom(m_display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(m_display, m_window, &wmDelete, 1);

    initRenderer(m_display, &m_window);
    setRenderSpaceSize(m_width, m_height);

    Keyboard::init();
    Mouse::init();
    Mouse::setMouseSource(m_display, &m_window);
}
//-----------------------------------------------------



//-----------------------------------------------------
sp::PixelWindow::~PixelWindow()
{
    m_windowExists = false;
    if (m_display != NULL)
    {
        XAutoRepeatOn(m_display);
        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);
    }

}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::setSize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
    XResizeWindow(m_display, m_window, m_width, m_height);
    setRenderSpaceSize(m_width, m_height);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::setPosition(int x_pos, int y_pos)
{
    XMoveWindow(m_display, m_window, x_pos, y_pos);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::setTitle(const char* title)
{
    m_title = title;
    XStoreName(m_display, m_window, m_title);
    XSetIconName(m_display, m_window, m_title);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::close()
{
    m_running = false;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::getNextEvent(Event& event)
{
    XNextEvent(m_display, event.getSystemEventPointer());
    event.updateEventType();

    if(event.type == EventType::Close)
        m_running = false;
    else if(event.type == EventType::LostFocus)
        XAutoRepeatOn(m_display);
    else if(event.type == EventType::GainedFocus)
        XAutoRepeatOff(m_display);
    else if(event.type == EventType::Resized)
    {
        XWindowAttributes attribs;
        XGetWindowAttributes(m_display, m_window, &attribs);
        int p_x, p_y;
        
        //The window was resized
        if (m_width != attribs.width || m_height != attribs.height)
        {
            m_width = attribs.width;
            m_height = attribs.height;
            setRenderSpaceSize(m_width, m_height);
        }

        //The window was moved
        Window child;
        XTranslateCoordinates(m_display, m_window, DefaultRootWindow(m_display), 0, 0, &p_x, &p_y, &child);
        if (m_x_pos != (p_x - attribs.x) || m_y_pos != (p_y - attribs.y))
        {
            m_x_pos = p_x - attribs.x;
            m_y_pos = p_y - attribs.y;
            event.type = Moved;
        }
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
int sp::PixelWindow::peekEvents()
{
    return XPending(m_display);
}
#endif
//-----------------------------------------------------



//==========WINDOWS IMPLEMENTATION==========
#if _WIN32
sp::PixelWindow::PixelWindow(unsigned int width, unsigned int height, const char* title)
{
    m_width = width;
    m_height = height;

    m_x_pos = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
    m_y_pos = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);

    //Window rejestration
	m_className = "myclass";
    
    m_windowClass.cbSize = sizeof( WNDCLASSEX );
    m_windowClass.style = 0;
    m_windowClass.lpfnWndProc = Event::WindowProcedure;
    m_windowClass.cbClsExtra = 0;
    m_windowClass.cbWndExtra = 0;
    m_windowClass.hInstance = GetModuleHandle(0);
    m_windowClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    m_windowClass.hCursor = LoadCursor( NULL, IDC_ARROW );
    m_windowClass.hbrBackground =( HBRUSH )GetStockObject(BLACK_BRUSH);
    m_windowClass.lpszMenuName = NULL;
    m_windowClass.lpszClassName = m_className;
    m_windowClass.hIconSm = LoadIcon( NULL, IDI_APPLICATION ); 

    if( !RegisterClassEx( & m_windowClass ) )
    {
        printf("Cant register window\n");
        return;
    }

    //WindowCreation
    m_window = CreateWindowEx(NULL, m_className, title, WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT , CW_USEDEFAULT , CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, m_windowClass.hInstance, NULL );


    //Set the proper possition and size
    int corr_x_pos, corr_y_pos, corr_width, corr_height;
    getCorrectWindowSize(&corr_x_pos, &corr_y_pos, &corr_width, &corr_height);

    SetWindowPos(m_window, HWND_TOP, corr_x_pos, corr_y_pos, corr_width, corr_height, SWP_SHOWWINDOW);
    
    if( m_window == NULL )
    {
        printf("Cant create window\n");
        return;
    }

    m_windowExists = true;
   
    ShowWindow(m_window, SW_SHOWDEFAULT);
    SetFocus(m_window);
    UpdateWindow(m_window);

    setIcon();

    this->initRenderer(&m_window);
    this->setRenderSpaceSize(m_width, m_height);

    sp::Keyboard::init();
    sp::Mouse::init();
    sp::Mouse::setMouseSource(&m_window);
}
//-----------------------------------------------------



//-----------------------------------------------------
sp::PixelWindow::~PixelWindow()
{
    DestroyWindow(m_window);
    PostQuitMessage(0);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::setSize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;

    int corr_x_pos, corr_y_pos, corr_width, corr_height;
    getCorrectWindowSize(&corr_x_pos, &corr_y_pos, &corr_width, &corr_height);

    SetWindowPos(m_window, HWND_TOP, corr_x_pos, corr_y_pos, corr_width, corr_height, SWP_SHOWWINDOW);

    this->setRenderSpaceSize(m_width, m_height);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::setPosition(int x_pos, int y_pos)
{
    m_x_pos = x_pos;
    m_y_pos = y_pos;

    int corr_x_pos, corr_y_pos, corr_width, corr_height;
    getCorrectWindowSize(&corr_x_pos, &corr_y_pos, &corr_width, &corr_height);

    SetWindowPos(m_window, HWND_TOP, corr_x_pos, corr_y_pos, corr_width, corr_height, SWP_SHOWWINDOW);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::setTitle(const char* title)
{
    SetWindowTextA(m_window, title);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::close()
{
    m_running = false;
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::getNextEvent(Event& event)
{
    m_firstMessage = false;
    event.updateEventType();

    if (event.type == EventType::Close)
        m_running = false;

    else if(event.type == EventType::Resized)
    {
        RECT windowRect;
        GetClientRect(m_window, &windowRect);

        if (m_width != windowRect.right || m_height != windowRect.bottom)
        {
            m_width = windowRect.right;
            m_height = windowRect.bottom;

            int corr_x_pos, corr_y_pos, corr_width, corr_height;
            getCorrectWindowSize(&corr_x_pos, &corr_y_pos, &corr_width, &corr_height);

            SetWindowPos(m_window, HWND_TOP, m_x_pos, m_y_pos, corr_width, corr_height, SWP_SHOWWINDOW);

            this->setRenderSpaceSize(m_width, m_height);
        }
    }

    else if (event.type == EventType::Moved)    //This function also runs when the window is maximized or minimized
    {
        RECT windowRect;
        GetWindowRect(m_window, &windowRect);

        if (m_x_pos != windowRect.left || m_y_pos != windowRect.top)
        {
            m_x_pos = windowRect.left;
            m_y_pos = windowRect.top;

            RECT windowClinetRect;
            GetClientRect(m_window, &windowClinetRect);
            if (m_width != windowClinetRect.right || m_height != windowClinetRect.bottom)
            {
                m_width = windowClinetRect.right - windowClinetRect.left;
                m_height = windowClinetRect.bottom - windowClinetRect.top;
                this->setRenderSpaceSize(m_width, m_height);
            }
        }
    }
}
//-----------------------------------------------------



//-----------------------------------------------------
int sp::PixelWindow::peekEvents()
{
    if (Event::m_messageQueue.empty())
    {
        while(PeekMessage((LPMSG)(&m_messageWin), 0, 0, 0, PM_REMOVE))
        {
            if (m_messageWin.message == WM_QUIT)
            {
                m_windowExists = true;
                return 0;
            }

            TranslateMessage(&m_messageWin);
            DispatchMessage(&m_messageWin);
            m_firstMessage = true;
        }
        Event::clearRepeated();
    }

    else if (!m_firstMessage)
        Event::m_messageQueue.pop_back();

    return Event::m_messageQueue.size();
}
//-----------------------------------------------------


//-----------------------------------------------------
void sp::PixelWindow::setIcon()
{
    m_windowIcon = (HICON)LoadImage(NULL, "SPICO.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE);
    if (m_windowIcon == NULL)
        std::cout << "Can't Load icon\n";
    SendMessage(m_window, WM_SETICON, ICON_BIG, (LPARAM)m_windowIcon);
    SendMessage(m_window, WM_SETICON, ICON_SMALL, (LPARAM)m_windowIcon);
}
//-----------------------------------------------------



//-----------------------------------------------------
void sp::PixelWindow::getCorrectWindowSize(int* pos_x, int* pos_y, int* width, int* height)
{
    RECT windowRect;
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = m_width;
    windowRect.bottom = m_height;
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

    *width = windowRect.right - windowRect.left;
    *height = windowRect.bottom - windowRect.top;
    *pos_x = m_x_pos + windowRect.left;
    *pos_y = m_y_pos + windowRect.top;
}
#endif
//-----------------------------------------------------



//-----------------------------------------------------
bool sp::PixelWindow::isOpen() const
{
    if(m_running || m_panicClose) 
        return true;
    else
        return false;
}
//-----------------------------------------------------
