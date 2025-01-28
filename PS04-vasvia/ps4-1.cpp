#include "fssimplewindow.h"
#include <stdlib.h>
#include <time.h>

// Function to draw the spaceship
// void DrawSpaceShip(int x, int y)
void DrawSpaceShip(int x,int y)
{
	glColor3ub(0,0,0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-3,y+-15);
	glVertex2i(x+-7,y+12);
	glVertex2i(x+-7,y+43);
	glVertex2i(x+-2,y+46);
	glVertex2i(x+0,y+42);
	glVertex2i(x+8,y+42);
	glVertex2i(x+11,y+46);
	glVertex2i(x+14,y+42);
	glVertex2i(x+14,y+8);
	glVertex2i(x+11,y+-15);
	glVertex2i(x+8,y+-2);
	glVertex2i(x+-1,y+-2);
	glVertex2i(x+-3,y+-15);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-7,y+19);
	glVertex2i(x+-19,y+24);
	glVertex2i(x+-18,y+41);
	glVertex2i(x+-7,y+41);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+14,y+18);
	glVertex2i(x+24,y+22);
	glVertex2i(x+24,y+39);
	glVertex2i(x+14,y+39);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-4,y+25);
	glVertex2i(x+-4,y+39);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+10,y+25);
	glVertex2i(x+10,y+37);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+0,y+3);
	glVertex2i(x+-1,y+12);
	glVertex2i(x+0,y+19);
	glVertex2i(x+2,y+21);
	glVertex2i(x+5,y+21);
	glVertex2i(x+7,y+18);
	glVertex2i(x+8,y+11);
	glVertex2i(x+6,y+3);
	glVertex2i(x+4,y+1);
	glVertex2i(x+2,y+1);
	glVertex2i(x+0,y+3);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-1,y+12);
	glVertex2i(x+1,y+15);
	glVertex2i(x+4,y+15);
	glVertex2i(x+7,y+13);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+-15,y+22);
	glVertex2i(x+-15,y+17);
	glVertex2i(x+-14,y+22);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+18,y+19);
	glVertex2i(x+19,y+15);
	glVertex2i(x+20,y+20);
	glEnd();
}

// Function to draw a missile
void DrawMissile(int x,int y)
{
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+11,y+-9);
	glVertex2i(x+10,y+19);
	glVertex2i(x+20,y+19);
	glVertex2i(x+20,y+-9);
	glVertex2i(x+17,y+-16);
	glVertex2i(x+15,y+-17);
	glVertex2i(x+13,y+-16);
	glVertex2i(x+11,y+-9);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+11,y+-7);
	glVertex2i(x+6,y+-6);
	glVertex2i(x+6,y+-4);
	glVertex2i(x+10,y+-4);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+20,y+-8);
	glVertex2i(x+23,y+-7);
	glVertex2i(x+24,y+-4);
	glVertex2i(x+20,y+-4);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+10,y+9);
	glVertex2i(x+6,y+12);
	glVertex2i(x+6,y+16);
	glVertex2i(x+10,y+18);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+20,y+9);
	glVertex2i(x+25,y+10);
	glVertex2i(x+25,y+16);
	glVertex2i(x+20,y+18);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+15,y+9);
	glVertex2i(x+15,y+16);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+15,y+-8);
	glVertex2i(x+15,y+-5);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x+10,y+19);
	glVertex2i(x+11,y+29);
	glVertex2i(x+14,y+27);
	glVertex2i(x+16,y+29);
	glVertex2i(x+18,y+26);
	glVertex2i(x+20,y+28);
	glVertex2i(x+20,y+20);
	glEnd();
}

// Function to draw a target
void DrawTarget(int x, int y, int width, int height)
{
    // Draw the main body of the target with a red color
    glColor3ub(255, 0, 0); // Red color
    glBegin(GL_POLYGON);
    glVertex2i(x + -9, y + -8);
    glVertex2i(x + 8, y + -20);
    glVertex2i(x + 25, y + -10);
    glVertex2i(x + -9, y + -8);
    glVertex2i(x + -8, y + 5);
    glVertex2i(x + 25, y + 3);
    glVertex2i(x + 24, y + -11);
    glEnd();

    // Draw the outline of the target
    glColor3ub(0, 0, 0); // Black color for the outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(x + -9, y + -8);
    glVertex2i(x + 8, y + -20);
    glVertex2i(x + 25, y + -10);
    glVertex2i(x + -9, y + -8);
    glVertex2i(x + -8, y + 5);
    glVertex2i(x + 25, y + 3);
    glVertex2i(x + 24, y + -11);
    glEnd();

    // Draw inner details of the target
    glColor3ub(255, 165, 0); // Orange color for inner details
    glBegin(GL_POLYGON);
    glVertex2i(x + 5, y + -7);
    glVertex2i(x + 2, y + -5);
    glVertex2i(x + 2, y + 0);
    glVertex2i(x + 7, y + 1);
    glVertex2i(x + 11, y + -1);
    glVertex2i(x + 11, y + -5);
    glVertex2i(x + 8, y + -7);
    glEnd();

    // Draw the outline of the inner details
    glColor3ub(0, 0, 0); // Black color for the outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 5, y + -7);
    glVertex2i(x + 2, y + -5);
    glVertex2i(x + 2, y + 0);
    glVertex2i(x + 7, y + 1);
    glVertex2i(x + 11, y + -1);
    glVertex2i(x + 11, y + -5);
    glVertex2i(x + 8, y + -7);
    glEnd();

    // Draw the target's bottom arc with a yellow color
    glColor3ub(255, 255, 0); // Yellow color
    glBegin(GL_POLYGON);
    glVertex2i(x + -8, y + 4);
    glVertex2i(x + -19, y + 12);
    glVertex2i(x + -4, y + 17);
    glVertex2i(x + 8, y + 17);
    glVertex2i(x + 25, y + 13);
    glVertex2i(x + 38, y + 6);
    glVertex2i(x + 24, y + 3);
    glEnd();

    // Draw the outline of the bottom arc
    glColor3ub(0, 0, 0); // Black color for the outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(x + -8, y + 4);
    glVertex2i(x + -19, y + 12);
    glVertex2i(x + -4, y + 17);
    glVertex2i(x + 8, y + 17);
    glVertex2i(x + 25, y + 13);
    glVertex2i(x + 38, y + 6);
    glVertex2i(x + 24, y + 3);
    glEnd();

    // Draw the top detail of the target with a green color
    glColor3ub(0, 255, 0); // Green color
    glBegin(GL_POLYGON);
    glVertex2i(x + 0, y + 17);
    glVertex2i(x + 2, y + 24);
    glVertex2i(x + 9, y + 25);
    glVertex2i(x + 18, y + 23);
    glEnd();

    // Draw the outline of the top detail
    glColor3ub(0, 0, 0); // Black color for the outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 0, y + 17);
    glVertex2i(x + 2, y + 24);
    glVertex2i(x + 9, y + 25);
    glVertex2i(x + 18, y + 23);
    glEnd();
}


// Function to check for collision between missile and target
bool CheckCollision(int mx, int my, int tx, int ty, int tw, int th)
{
    return (tx <= mx && mx <= tx + tw && ty <= my && my <= ty + th);
}

// Constants
#define NUM_PARTICLES 200
#define NUM_TARGETS 3

int main(void)
{
    int x = 400, y = 550;
    int mx, my, mv = 10;
    bool mState = false;

    int tx[NUM_TARGETS], ty[NUM_TARGETS], tw[NUM_TARGETS], th[NUM_TARGETS], tv[NUM_TARGETS];
    bool tState[NUM_TARGETS];

    srand(time(nullptr));

    bool eState = false;
    int eStep = 0;
    int ex[NUM_PARTICLES], ey[NUM_PARTICLES], evx[NUM_PARTICLES], evy[NUM_PARTICLES];

    // Initialize targets
    for (int i = 0; i < NUM_TARGETS; ++i)
    {
        tState[i] = true;
        tx[i] = 0;
        ty[i] = 80 + rand() % 40;
        tw[i] = 40;
        th[i] = 40;
        tv[i] = 5 + rand() % 10;
    }

    FsOpenWindow(0, 0, 800, 600, 1);
    for (;;)
    {
        FsPollDevice();

        auto key = FsInkey();
        if (FSKEY_ESC == key)
        {
            break;
        }

        switch (key)
        {
        case FSKEY_LEFT:
            x -= 10;
            break;
        case FSKEY_RIGHT:
            x += 10;
            break;
        case FSKEY_SPACE:
            if (true != mState)
            {
                mState = true;
                mx = x;
                my = y;
            }
            break;
        }

        if (true == mState)
        {
            my -= mv;
            if (my < 0)
            {
                mState = false;
            }
        }

        for (int i = 0; i < NUM_TARGETS; ++i)
        {
            if (true == tState[i])
            {
                tx[i] += tv[i];
                if (800 < tx[i])
                {
                    tx[i] = 0;
                }
            }
        }

        for (int i = 0; i < NUM_TARGETS; ++i)
        {
            if (true == mState &&
                true == tState[i] &&
                true == CheckCollision(mx, my, tx[i], ty[i], tw[i], th[i]))
            {
                tState[i] = false;
                mState = false;

                eState = true;
                eStep = 0;
                for (int i = 0; i < NUM_PARTICLES; ++i)
                {
                    ex[i] = mx;
                    ey[i] = my;
                    evx[i] = rand() % 51 - 25;
                    evy[i] = rand() % 51 - 25;
                }
            }
        }

        if (true == eState)
        {
            for (int i = 0; i < NUM_PARTICLES; ++i)
            {
                ex[i] += evx[i];
                ey[i] += evy[i];
            }
            ++eStep;
            if (100 < eStep)
            {
                eState = false;

                bool stillAlive = false;
                for (int i = 0; i < NUM_TARGETS; ++i)
                {
                    if (true == tState[i])
                    {
                        stillAlive = true;
                        break;
                    }
                }
                if (true != stillAlive)
                {
                    break;
                }
            }
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        DrawSpaceShip(x, y);

        if (true == mState)
        {
            DrawMissile(mx, my);
        }

        for (int i = 0; i < NUM_TARGETS; ++i)
        {
            if (true == tState[i])
            {
                DrawTarget(tx[i], ty[i], tw[i], th[i]);
            }
        }

        if (true == eState)
        {
            glColor3f(1, 0, 0);
            glBegin(GL_POINTS);
            for (int i = 0; i < NUM_PARTICLES; ++i)
            {
                glVertex2i(ex[i], ey[i]);
            }
            glEnd();
        }

        FsSwapBuffers();
        FsSleep(25);
    }

    return 0;
}
