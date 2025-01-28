#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include "fssimplewindow.h"
#include "yspng.h"

class Histogram {
protected:
    int hist[256];
    bool isDone;

public:
    Histogram() : isDone(false) {
        Clear();
    }

    void Clear() {
        for(int &j : hist) {
            j = 0;
        }
    }

    void Make(const YsRawPngDecoder &png) {
        Clear();
        for (int i = 0; i < (png.wid * png.hei); ++i) {
            auto r = png.rgba[i * 4];
            auto g = png.rgba[i * 4 + 1];
            auto b = png.rgba[i * 4 + 2];
            hist[r]++;
            hist[g]++;
            hist[b]++;
        }
        isDone = true;
    }

    void Print() const {
        if(isDone == false) {
            std::cout << "Error! No histogram created" << std::endl;
            return;
        }
        int maxNum=0;
        for(int i=0; i<256; ++i)
        {
            maxNum=std::max<unsigned int>(maxNum,hist[i]);
        }

        for(int i=0; i<256; ++i)
        {
            printf("%3d:",i);

            int len;
            len=hist[i]*80/maxNum;
            for(int j=0; j<len; ++j)
            {
                printf("#");
            }
            printf("\n");
        }
    }

    void Draw(int height) const {
        if(isDone == false) {
            std::cout << "Error! No histogram created" << std::endl;
            return;
        }
        int maxNum = 0;
        for (int value : hist) {
            if (value > maxNum) {
                maxNum = value;
            }
        }
        if (maxNum == 0) {
            maxNum = 1;
        }
        float scale = 80.0f / maxNum;

        glColor3f(1.0f, 1.0f, 1.0f); 
        for (int i = 0; i < 256; ++i) {
            int len = static_cast<int>(hist[i] * scale);
            glBegin(GL_LINES);
            glVertex2i(i, height);        
            glVertex2i(i, height - len);  
            glEnd();
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <PNG filename>" << std::endl;
        return 1;
    }

    FsChangeToProgramDir();
    YsRawPngDecoder png;
    if (YSOK != png.Decode(argv[1])) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }
    png.Flip();

    Histogram histogram;
    histogram.Make(png);
    histogram.Print();

    FsOpenWindow(0, 0, png.wid, png.hei, 1);

    while (true) {
        FsPollDevice();
        if (FSKEY_ESC == FsInkey()) {
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glRasterPos2i(0, png.hei - 1);
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

        histogram.Draw(png.hei);

        FsSwapBuffers();
        FsSleep(10);
    }

    return 0;
}
