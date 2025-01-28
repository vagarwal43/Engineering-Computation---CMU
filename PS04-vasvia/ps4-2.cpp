#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fssimplewindow.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const double PI = 3.14159265;
const int SCREEN_W = 800, SCREEN_H = 600;
const double G = 98.1, V_INIT = 400.0;
const int TRAIL_LEN = 10;

vector<pair<float, float>> projectileTrail;

struct Block {
    int posX, posY, sizeW, sizeH;
    int hitCount = 0;
};

Block blocks[5];

int goalX = SCREEN_W - 50, goalY = 50, goalW = 100, goalH = 100;
float projX, projY, projVX, projVY;
bool projActive = false;
int fireCount = 0;
float launchAngle = 45.0 * PI / 180.0;
bool isGameActive = true;

void DrawCannon(int x, int y, float angle) {
    glColor3ub(0, 0, 255);
    glBegin(GL_QUADS);
    glVertex2i(x - 10, y - 10);
    glVertex2i(x + 10, y - 10);
    glVertex2i(x + 10, y + 10);
    glVertex2i(x - 10, y + 10);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(x, y);
    glVertex2i(x + cos(angle) * 30, y - sin(angle) * 30);
    glEnd();
}

void DrawCannonBall(float x, float y) {
    if (fireCount < 5) {
        switch (fireCount % 5) {
            case 1: glColor3ub(0, 0, 255); break;
            case 2: glColor3ub(0, 255, 255); break;
            case 3: glColor3ub(255, 255, 0); break;
            case 4: glColor3ub(255, 0, 255); break;
            default: glColor3ub(255, 0, 0); break;
        }
    } else {
        glColor3ub(255, 0, 0);
    }
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * PI / 180.0;
        glVertex2f(x + cos(rad) * 5, y + sin(rad) * 5);
    }
    glEnd();
}

void DrawObstacle(int x, int y, int w, int h, int hits) {
    if (hits == 0) glColor3ub(0, 255, 0);
    else if (hits == 1) glColor3ub(255, 255, 0);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + w, y);
    glVertex2i(x + w, y + h);
    glVertex2i(x, y + h);
    glEnd();
}

void DrawTarget(int x, int y) {
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(x - goalW / 2, y - goalH / 2);
    glVertex2i(x + goalW / 2, y - goalH / 2);
    glVertex2i(x + goalW / 2, y + goalH / 2);
    glVertex2i(x - goalW / 2, y + goalH / 2);
    glEnd();
}

bool DetectCollision(float bx, float by, Block b) {
    return (bx > b.posX && bx < b.posX + b.sizeW && by > b.posY && by < b.posY + b.sizeH);
}

bool DetectGoalHit(float bx, float by) {
    return (bx > goalX - goalW / 2 && bx < goalX + goalW / 2 && by > goalY - goalH / 2 && by < goalY + goalH / 2);
}

void LaunchProjectile(int launcherX, int launcherY) {
    if (!projActive) {
        projActive = true;
        projX = launcherX + cos(launchAngle) * 30;
        projY = launcherY - sin(launchAngle) * 30;
        projVX = V_INIT * cos(launchAngle);
        projVY = V_INIT * -sin(launchAngle);
        fireCount++;
        projectileTrail.clear();
    }
}

void UpdateGoalPosition() {
    static int dir = 1;
    goalY += dir * 10;
    if (goalY + goalH / 2 >= SCREEN_H || goalY - goalH / 2 <= 0) {
        dir = -dir;
    }
}

void UpdateProjectilePosition(float dt) {
    if (projActive) {
        projX += projVX * dt;
        projVY += G * dt;
        projY += projVY * dt + 0.5 * G * dt * dt;
        projectileTrail.push_back({projX, projY});
        if (projectileTrail.size() > TRAIL_LEN) {
            projectileTrail.erase(projectileTrail.begin());
        }
        for (int i = 0; i < 5; i++) {
            if (blocks[i].hitCount < 2 && DetectCollision(projX, projY, blocks[i])) {
                projActive = false;
                blocks[i].hitCount++;
                projectileTrail.clear();
            }
        }
        if (DetectGoalHit(projX, projY)) {
            projActive = false;
            isGameActive = false;
            projectileTrail.clear();
        }
        if (projX > SCREEN_W || projY > SCREEN_H) {
            projActive = false;
            projectileTrail.clear();
        }
    }
}

void CannonballTrail() {
    if (fireCount < 5) {
        switch (fireCount % 5) {
            case 1: glColor3ub(0, 0, 255); break;
            case 2: glColor3ub(0, 255, 255); break;
            case 3: glColor3ub(255, 255, 0); break;
            case 4: glColor3ub(255, 0, 255); break;
            default: glColor3ub(255, 0, 0); break;
        }
    } else {
        glColor3ub(255, 0, 0);
    }
    glBegin(GL_LINE_STRIP);
    for (auto &pos : projectileTrail) {
        glVertex2f(pos.first, pos.second);
    }
    glEnd();
}

void InitializeBlocks() {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < 5; ++i) {
        int width = rand() % 70 + 80;
        int height = rand() % 70 + 80;
        int x = rand() % (SCREEN_W - width - 100) + 100; // Ensure obstacles are not too close to the left edge
        int y = rand() % (SCREEN_H - height - 100) + 50; // Ensure obstacles are not too close to the top or bottom
        blocks[i].posX = x;
        blocks[i].posY = y;
        blocks[i].sizeW = width;
        blocks[i].sizeH = height;
    }
}

int main(void) {
    FsOpenWindow(0, 0, SCREEN_W, SCREEN_H, 1);
    InitializeBlocks();
    int launcherX = 50, launcherY = 580;
    const float dt = 0.1;
    while (isGameActive) {
        FsPollDevice();
        auto key = FsInkey();
        if (key == FSKEY_ESC) break;
        if (key == FSKEY_SPACE) LaunchProjectile(launcherX, launcherY);
        if (key == FSKEY_UP) launchAngle = min(launchAngle + 3 * PI / 180.0, PI / 2);
        if (key == FSKEY_DOWN) launchAngle = max(launchAngle - 3 * PI / 180.0, 0.0);
        UpdateGoalPosition();
        UpdateProjectilePosition(dt);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        DrawCannon(launcherX, launcherY, launchAngle);
        for (int i = 0; i < 5; i++) {
            if (blocks[i].hitCount < 2) {
                DrawObstacle(blocks[i].posX, blocks[i].posY, blocks[i].sizeW, blocks[i].sizeH, blocks[i].hitCount);
            }
        }
        DrawTarget(goalX, goalY);
        if (projActive) {
            CannonballTrail();
            DrawCannonBall(projX, projY);
        }
        FsSwapBuffers();
        FsSleep(25);
    }

    // Number of shots taken to hit the target
    cout << "Target hit after " << fireCount << " shots!" << endl;

    return 0;
}