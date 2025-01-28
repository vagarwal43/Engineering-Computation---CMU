#include <fssimplewindow.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <GL/gl.h>
#include <ysglfontdata.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Floors of the Buildings
struct Block {
    int x, y, width, height;
    float r, g, b;

    void draw() const {
        glColor3f(r * 0.8f, g * 0.8f, b * 0.8f); 
        glBegin(GL_QUADS);
        glVertex2i(x, y + height);          
        glVertex2i(x + width, y + height);  
        glVertex2i(x + width, y);           
        glVertex2i(x, y);                   
        glEnd();

        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2i(x, y);                   
        glVertex2i(x + width, y);            
        glVertex2i(x + width, y + height);   
        glVertex2i(x, y + height);           
        glEnd();

        // Border of the blocks
        glColor3f(0, 0, 0); 
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();

        // 2 WINDOWS of each block
        glColor3f(1, 1, 1); 
        for (int j = 0; j < 2; j++) { 
            int winX = x + 10 + j * 40; 
            int winY = y + 10;          

            
            glColor3f(0.8f, 0.8f, 0.8f); 
            glBegin(GL_QUADS);
            glVertex2i(winX, winY);
            glVertex2i(winX + 30, winY);
            glVertex2i(winX + 30, winY + 30);
            glVertex2i(winX, winY + 30);
            glEnd();

            // Border of the windows
            glColor3f(0, 0, 0); 
            glLineWidth(1);
            glBegin(GL_LINE_LOOP);
            glVertex2i(winX, winY);
            glVertex2i(winX + 30, winY);
            glVertex2i(winX + 30, winY + 30);
            glVertex2i(winX, winY + 30);
            glEnd();
        }
    }
};

// base of the building and variable initialized for the game
std::vector<Block> blocks;
int baseX = 300, baseY = 550, baseWidth = 100, baseHeight = 80;
Block movingBlock;
bool isGameOver = false;
int score = 0;
bool isFalling = false;  
int fallSpeed = 15;       

// Initializing the blocks for movement
void InitializeMovingBlock() {
    movingBlock.x = 0;
    movingBlock.y = 50;
    movingBlock.width = 100;
    movingBlock.height = 50;
    movingBlock.r = static_cast<float>(rand() % 100) / 100.0f;
    movingBlock.g = static_cast<float>(rand() % 100) / 100.0f;
    movingBlock.b = static_cast<float>(rand() % 100) / 100.0f;
}

// Base of the building kind of like ground floor
void DrawBase() {
    glColor3f(0.6, 0.4, 0.2); 
    glBegin(GL_QUADS);
    glVertex2i(baseX, baseY);
    glVertex2i(baseX + baseWidth, baseY);
    glVertex2i(baseX + baseWidth, baseY - baseHeight);
    glVertex2i(baseX, baseY - baseHeight);
    glEnd();

    // Door of the building 
    int doorWidth = baseWidth / 5; 
    int doorHeight = baseHeight / 3; 
    int doorX = baseX + (baseWidth - doorWidth) / 2; 
    int doorY = baseY; 
    glColor3f(1.0f, 0.0f, 0.0f); 
    glBegin(GL_QUADS);
    glVertex2i(doorX, doorY); 
    glVertex2i(doorX + doorWidth, doorY); 
    glVertex2i(doorX + doorWidth, doorY - doorHeight); 
    glVertex2i(doorX, doorY - doorHeight);
    glEnd();
}

int const numClouds = 6; 
float meghX[numClouds]; 
float meghY = 100;

// Drawing clouds
void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments); 
        float x = r * cosf(theta); 
        float y = r * sinf(theta); 
        glVertex2f(x + cx, y + cy); 
    }
    glEnd();
}
void InitializeClouds() {
    meghX[0] = 100;
    meghX[1] = 200; 
    meghX[2] = 300; 
    meghX[3] = 500; 
    meghX[4] = 600;
    meghX[5] = 700;
}
void DrawClouds() {
    glColor3f(1.0, 1.0, 1.0); 
    DrawCircle(meghX[0], meghY, 60, 200); 
    DrawCircle(meghX[1], meghY, 80, 200); 
    DrawCircle(meghX[2], meghY, 55, 200); 
    DrawCircle(meghX[3], meghY, 60, 200);
    DrawCircle(meghX[4], meghY, 80, 200);
    DrawCircle(meghX[5], meghY, 55, 200);
}

// Grass, Gradient Sky and Base of the background
void DrawBackground() {
    // Code for Sky to create a gradient
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.1f, 0.1f); // Dark blue
    glVertex2i(0, 0);
    glColor3f(0.0f, 0.1f, 0.1f); // Dark blue
    glVertex2i(800, 0);
    glColor3f(0.6f, 0.8f, 1.0f); // Sky blue
    glVertex2i(800, 600);
    glColor3f(0.6f, 0.8f, 1.0f); // Sky blue
    glVertex2i(0, 600);
    glEnd();
    
    // Grass 
    glColor3f(0.2f, 0.5f, 0.2f); 
    glBegin(GL_QUADS);
    glVertex2i(0, 500); 
    glVertex2i(800, 500);
    glVertex2i(800, 600); 
    glVertex2i(0, 600); 
    glEnd();

    // Spikes of the grass
    glColor3f(0.0f, 0.3f, 0.0f); 
    for (int i = 0; i < 800; i += 20) {
        glBegin(GL_TRIANGLES);
        glVertex2i(i, 500); 
        glVertex2i(i + 10, 450); 
        glVertex2i(i + 20, 500); 
        glEnd();
    }
}

//Checking the floor falling with the previous floor or base
bool CheckCollision() {
    if (blocks.empty()) {
        return (movingBlock.x + movingBlock.width > baseX && movingBlock.x < baseX + baseWidth);
    } else {
        Block lastBlock = blocks.back();
        return (movingBlock.x + movingBlock.width > lastBlock.x && movingBlock.x < lastBlock.x + lastBlock.width);
    }
}

//When spacebar is pressed
void DropBlock() {
    isFalling = true; 
}

//Keeping the floor on the top of another
void FinalizeBlock() {
    if (CheckCollision()) {
        if (blocks.empty()) {
            movingBlock.y = baseY - baseHeight - movingBlock.height; 
        } else {
            Block lastBlock = blocks.back();
            movingBlock.y = lastBlock.y - lastBlock.height;
        }
        blocks.push_back(movingBlock);
        score++;
    } else {
        isGameOver = true;
    }
    isFalling = false; 
    InitializeMovingBlock();  
}

// To creat the stacked blocks
void DrawScene() {
    DrawBase();
    for (const auto &block : blocks) {
        block.draw();
    }
    if (!isGameOver) {
        movingBlock.draw();
    }
    FsSwapBuffers();
}

//Movement of the blocks from left to right
void MoveBlock() {
    if (!isFalling) {
        movingBlock.x += 15;  
        if (movingBlock.x > 800) {
            movingBlock.x = 0;  
        }
    }
}

//Falling of the floor
void AnimateFall() {
    if (isFalling) {
        int targetY;
        if (blocks.empty()) {
            targetY = baseY - baseHeight;  
        } else {
            Block lastBlock = blocks.back();
            targetY = lastBlock.y - lastBlock.height;  
        }
        if (movingBlock.y + movingBlock.height >= targetY) {
            movingBlock.y = targetY - movingBlock.height;
            FinalizeBlock();  
        } else {
            movingBlock.y += fallSpeed; 
        }
    }
}

//Main Function
int main() {
    FsOpenWindow(0, 0, 800, 600, 1);
    srand(static_cast<unsigned int>(time(nullptr)));
    glShadeModel(GL_SMOOTH);
    InitializeMovingBlock();
    InitializeClouds();
    while (!isGameOver) {
        FsPollDevice();
        int key = FsInkey();
        if (key == FSKEY_ESC) {
            break;
        }
        if (key == FSKEY_SPACE && !isFalling) {
            DropBlock();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawBackground();
        DrawClouds();
        MoveBlock();
        AnimateFall();
        DrawScene();
        FsSleep(10); // Control frame rate
    }

    // Game Over
    std::cout << "Game Over! Final Score: " << score << std::endl;
    return 0;
}
