#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include <vector>

// Function to binarize the image
void BinarizeImage(YsRawPngDecoder &image) {
    for (int i =0; i < (image.wid*image.hei); ++i) {
        int idx = i*4;
        if (image.rgba[idx] < 220 || image.rgba[idx + 1] < 220 || image.rgba[idx + 2] < 220) {
            image.rgba[idx] = 0;
            image.rgba[idx + 1] = 0;
            image.rgba[idx + 2] = 0;
        } 
        else {
            image.rgba[idx] = 255;
            image.rgba[idx + 1] = 255;
            image.rgba[idx + 2] = 255;
        }
    }
}

// Function to extract the contour from the binarized image
void ExtractContour(YsRawPngDecoder &image) {
    std::vector<unsigned char> tempChannel(image.wid*image.hei,255);
    for (int y = 1; y < image.hei - 1; ++y) {
        for (int x = 1; x < image.wid - 1; ++x) {
            int idx = (y * image.wid + x) * 4;
            if (image.rgba[idx] == 255) {
                bool hasBlackNeighbor = false;
                for (int dy = -1; dy <= 1 && !hasBlackNeighbor; ++dy) {
                    for (int dx = -1; dx <= 1 && !hasBlackNeighbor; ++dx) {
                        if (dy != 0 || dx != 0) {
                            int neighborIdx = ((y + dy) * image.wid + (x + dx)) * 4;
                            if (image.rgba[neighborIdx] == 0) {
                                hasBlackNeighbor = true;
                            }
                        }
                    }
                        if(hasBlackNeighbor) {
                            break;
                        }
                }
                if(!hasBlackNeighbor) {
                    tempChannel[y*image.wid+x]=0;
                }
            }
        }
    }
    for (int y = 1; y < image.hei - 1; ++y) {
        for (int x = 1; x < image.wid - 1; ++x) {
            int idx = (y * image.wid + x) * 4;
            if (tempChannel[y * image.wid + x] == 0) {
                image.rgba[idx] = 0;
                image.rgba[idx + 1] = 0;
                image.rgba[idx + 2] = 0;
            }
        }
    }
}

int main() {
    
    FsChangeToProgramDir();

    YsRawPngDecoder png;
    if (YSOK != png.Decode("ps9.png")) {
        std::cerr << "Error: Could not open or decode ps9.png" << std::endl;
        return 1;
    }

    // png.Flip();

    FsOpenWindow(0, 0, png.wid, png.hei, 1);

    bool binarized = false;
    bool contourExtracted = false;

    while (true) {
        FsPollDevice();
        int key = FsInkey();
        if (FSKEY_ESC == key) {
            break; 
        } else if (FSKEY_SPACE == key && !binarized) {
            BinarizeImage(png);
            binarized = true;
        } else if (FSKEY_ENTER == key && binarized && !contourExtracted) {
            ExtractContour(png);
            contourExtracted = true;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glRasterPos2i(0, png.hei - 1);
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
        FsSwapBuffers();
        FsSleep(10);
    }

    return 0;
}
