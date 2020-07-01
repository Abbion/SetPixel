#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <limits>
#include <unistd.h>
#include <time.h>
#include <cstdlib>

#include "../sp/setPixel.h"


bool fpsSwitch = false;
int d_x = 400, d_y = 300;

int main(void)
{
    sp::PixelWindow newWindow(1200, 800, "Okienko testowe"); 
    sp::Event event;
    
    sp::Color c1(0, 128, 128);
    newWindow.setClearColor(c1);

    newWindow.showFps(true);
    sp::Pixel testPix(0,0, sp::Color(0,0,0));

    std::srand(time(0));
    
    /*
    sp::pixel* pixSet = new sp::pixel[100 * 75];
    int k = 0;
        for (int i = 0; i < 75; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                pixSet[k].setPosition(j, i);
                pixSet[k].setColor(sp::color(255 * std::abs(std::sin((i) * 0.01)), 255 * std::abs(std::sin((i+j) * 0.01)), 255 * std::abs(std::sin((j) * 0.01))));
                k++;
            }
            
        }
    */
   
    float time = 0;
    newWindow.setPixelSize(4);
    
    //main loop
    while(newWindow.isOpen())
    {   
        //event loop
        while(newWindow.peekEvents())
        {
            newWindow.getNextEvent(event);
            sp::Keyboard::updateKeyMap(event);
            sp::Mouse::updateButtonMap(event);
        }

        if(sp::Keyboard::getKeyIsPressed(sp::Keyboard::Esc))
        {
            newWindow.close();
        }

        if(sp::Keyboard::getKeyPress(sp::Keyboard::F))
        {
            fpsSwitch = !fpsSwitch;
            newWindow.showFps(fpsSwitch);
        }

        if(sp::Keyboard::getKeyPress(sp::Keyboard::A))
        {
            //d_x = 100;
            //d_y = 75;
            newWindow.setSize(400, 300);
        }

        if(sp::Keyboard::getKeyPress(sp::Keyboard::D))
        {
            d_x = 200;
            d_y = 150;
            newWindow.setSize(800, 600);
        }

        
        newWindow.clear();
        
        for (int i = 0; i < d_y; i++)
        {
            for (int j = 0; j < d_x; j++)
            {
                int r = rand() % 255;
                int g = rand() % 255;
                int b = rand() % 255;
                sp::Pixel pix(j, i, sp::Color(r, g, b));
                newWindow.draw(pix);
            }
            
        }
       //newWindow.drawset(pixSet, 100 * 75);
       newWindow.display();
       
    }

    return 0;
 }

 