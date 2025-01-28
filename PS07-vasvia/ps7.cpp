#include <iostream>
#include <string>
#include <cstring>
#include "fssimplewindow.h"

using namespace std;

class CharBitmap {
    public:

    int wid,hei;
    char *pix;

    CharBitmap() : wid(0), hei(0), pix(nullptr) {}

    void CleanUp() {

        if(pix!=nullptr) {

            delete[] pix;
            pix = nullptr;
        }

        wid = 0;
        hei = 0;
    }

    ~CharBitmap() {

        CleanUp();
    }

    void Create(int h, int w) {

        CleanUp();

        wid = w;
        hei = h;
        pix = new char[w*h];

        for (int i = 0; i < (w*h); ++i) {

            pix[i] = 0;
        }

    }

    void SetPixel(int x, int y, char p) const{

        if (x >= 0 && x < wid && y >= 0 && y < hei) {

            int index = y * wid + x;
            pix [index] = p;
        }
    }

    char GetPixel(int x, int y) const {

        if (x >= 0 && x < wid && y >= 0 && y < hei) {

            int index = y * wid + x;
            return pix [index];
        }
        else {
            return 0;
        }
    }

    void Draw() const {

        for (int y = 0; y < hei; ++y) {

            for (int x = 0; x < wid; ++x) {

                char pixVal = GetPixel(x, y);

                switch (pixVal) {

                    case 0: glColor3ub(0, 0, 0); break;      
                    case 1: glColor3ub(0, 0, 255); break;    
                    case 2: glColor3ub(255, 0, 0); break;   
                    case 3: glColor3ub(255, 0, 255); break;  
                    case 4: glColor3ub(0, 255, 0); break;    
                    case 5: glColor3ub(0, 255, 255); break;  
                    case 6: glColor3ub(255, 255, 0); break;  
                    case 7: glColor3ub(255, 255, 255); break;
                }

                glBegin(GL_QUADS);
                glVertex2i(x * 20, y * 20);
                glVertex2i(x * 20 + 20, y * 20);
                glVertex2i(x * 20 + 20, y * 20 + 20);
                glVertex2i(x * 20, y * 20 + 20);
                glEnd();
            }
        }

        glColor3ub(255, 255, 255); 

        for (int x = 0; x <= wid; ++x) {

            glBegin(GL_LINES);
            glVertex2i(x * 20, 0);
            glVertex2i(x * 20, hei * 20);
            glEnd();
        }

        for (int y = 0; y <= hei; ++y) {

            glBegin(GL_LINES);
            glVertex2i(0, y * 20);
            glVertex2i(wid * 20, y * 20);
            glEnd();
        }
    }
};


int main() {
    
    int w, h;

    while (true) {
        cout << "Enter Dimension (Width Height): ";
        string input;
        getline(cin, input);
        sscanf(input.c_str(), "%d %d", &w, &h);
        if (w > 0 && w <= 64 && h > 0 && h <= 64) {
            break;
        }
        cout << "Invalid dimensions. Please enter again.\n";
    }

    CharBitmap bitmap;
    bitmap.Create(w,h);
    
    int winWidth = w * 20;
    int winHeight = h * 20;

    FsOpenWindow(0,0, winWidth, winHeight, 1);
    
    while (FSKEY_ESC != FsInkey()) {
        FsPollDevice();

        int mx,my,lb,mb,rb;
        FsGetMouseState(lb,mb,rb,mx,my);
        int pixX = mx / 20;
        int pixY = my / 20;

        int key = FsInkey();
        if (key >= FSKEY_0 && key <= FSKEY_7) {

            int color = key - FSKEY_0;
            bitmap.SetPixel(pixX,pixY, color);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        bitmap.Draw();
        FsSwapBuffers();
        FsSleep(20);
    }

    return 0;

}