#include <fssimplewindow.h>
#include <math.h>
#include <vector>

#define PI 3.14159265358979

struct Point
{
    double x, y;
};

Point RotatePoint(Point p, double angle)
{
    Point rotated;
    rotated.x = cos(angle) * p.x - sin(angle) * p.y;
    rotated.y = sin(angle) * p.x + cos(angle) * p.y;
    return rotated;
}

void DrawLine(Point p1, Point p2)
{
    glBegin(GL_LINES);
    glVertex2d(p1.x, p1.y);
    glVertex2d(p2.x, p2.y);
    glEnd();
}

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 600;
    FsOpenWindow(0, 0, windowWidth, windowHeight, 1);

    Point origin = {100.0, 500.0};
    const double scale = 100.0; // 1m = 100 pixels
    const double shaft1Length = 1.0 * scale;
    const double shaft2Length = 4.0 * scale;
    const double shaft3Length = 2.0 * scale;
    const double L = 4.0 * scale;

    //P3 position
    Point P3 = {origin.x + L, origin.y};
    double angle = 0.0;

    std::vector<Point> midpointPath;

    while (FSKEY_ESC != FsInkey())
    {
        FsPollDevice();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //P1 position
        Point P1 = RotatePoint({shaft1Length, 0}, angle);
        P1.x += origin.x;
        P1.y += origin.y;

        //P2 position
        double dx = P3.x - P1.x;
        double dy = P3.y - P1.y;
        double d = sqrt(dx * dx + dy * dy);
        double a = (d * d + shaft2Length * shaft2Length - shaft3Length * shaft3Length) / (2 * d);
        double h = sqrt(shaft2Length * shaft2Length - a * a);

        Point midPoint = {P1.x + a * dx / d, P1.y + a * dy / d};
        Point P2 = {midPoint.x + h * dy / d, midPoint.y - h * dx / d};

        glColor3ub(0, 0, 255);
        DrawLine(origin, P1);
        DrawLine(P1, P2);
        DrawLine(P2, P3);

        // Midpoit of P1 and P2
        Point midP1P2 = {(P1.x + P2.x) / 2.0, (P1.y + P2.y) / 2.0};
        midpointPath.push_back(midP1P2);
        glColor3ub(255, 0, 0);
        glBegin(GL_LINE_STRIP);
        for (const auto &p : midpointPath)
        {
            glVertex2d(p.x, p.y);
        }
        glEnd();

        FsSwapBuffers();
        FsSleep(10);

        angle += 0.01;
    }

    return 0;
}