#include <iostream>
#include "fssimplewindow.h"

// dRAWING A POLYGON and using strip
void DrawPolygon(float vertices[][2], int numVertices)
{
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numVertices; ++i)
    {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

//Function to draw polygon and using loop
void DrawPolygon2(float vertices[][2], int numVertices)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; ++i)
    {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// Function to draw a filled polygon 
void DrawFilledPolygon(float vertices[][2], int numVertices)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i)
    {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// Function to draw the rubber duck
void DrawRubberDuck()
{
    //head
    glColor3f(1.0f, 1.0f, 0.0f);
    float headVertices[][2] = {
        { 185.0f, 260.0f },
        { 195.0f, 220.0f },
        { 225.0f, 160.0f },
        { 275.0f, 130.0f },
        { 345.0f, 140.0f },
        { 395.0f, 200.0f },
        { 415.0f, 280.0f },
        { 375.0f, 320.0f },
        { 305.0f, 350.0f },
        { 265.0f, 340.0f },
        { 235.0f, 330.0f }
        
    };
    DrawPolygon(headVertices, 10);

    //body
    glColor3f(1.0f, 1.0f, 0.0f);
    float bodyVertices[][2] = {
        { 405.0f, 240.0f },
        { 462.5f, 220.5f },
        { 512.5f, 255.0f },
        { 540.0f, 315.0f },
        { 540.0f, 375.0f },
        { 500.5f, 455.0f },
        { 420.5f, 485.0f },
        { 300.0f, 480.0f },
        { 210.0f, 427.5f },
        { 205.0f, 380.0f },
        { 220.0f, 340.0f }
    };
    DrawPolygon(bodyVertices, 11);

    //feather of the duck
    glColor3f(0.9f, 0.8f, 0.1f);
    float featherVertices[][2] = {
        { 540.0f, 375.0f },
        { 530.5f, 350.0f },
        { 490.5f, 370.0f },
        { 480.0f, 390.0f },
        { 430.0f, 410.0f },
        { 400.5f, 435.0f },
        { 405.5f, 455.0f },
        { 420.0f, 470.0f },
        { 450.0f, 470.5f }
    };
    DrawPolygon(featherVertices, 9);

    //beak
    glColor3f(1.0f, 0.5f, 0.0f);
    float beakVertices[][2] = {
        { 260.0f, 325.0f },
        { 260.0f, 345.0f },
        { 220.0f, 340.0f },
        { 180.0f, 330.0f },
        { 120.0f, 310.0f },
        { 110.0f, 290.0f },
        { 120.0f, 270.0f },
        { 165.0f, 269.0f },
        { 185.0f, 260.0f }
    };
    DrawPolygon2(beakVertices, 9);

    //eye
    float eyeVertices[][2] = {
        { 285.0f, 200.0f },
        { 277.5f, 212.99f },
        { 262.5f, 212.99f },
        { 255.0f, 200.0f },
        { 262.5f, 187.01f },
        { 277.5f, 187.01f }
    };
    glColor3f(0.0f, 0.0f, 0.0f); 
    DrawFilledPolygon(eyeVertices, 6);
}

int main()
{
    FsOpenWindow(0, 0, 800, 600, 1);
    while (FSKEY_ESC != FsInkey())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        DrawRubberDuck();
        
        FsSwapBuffers();
        FsSleep(20);
    }
    return 0;
}
