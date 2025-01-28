#include <iostream>
#include <math.h>
#include "fssimplewindow.h"

const double tolerance=1e-6;


// Equation Class

class Equation {
public:

	double a,b,c;

	void Plot(float R, float G, float B) {

		glColor3f(R,G,B);
		glBegin(GL_LINES);

		if (std::abs(b) < tolerance) {
			double x = -c/a;
			glVertex2d((x+30)*10,0);
			glVertex2d((x+30)*10,600);
		}
		else {
			double y1 = (-a*(-30) -c) /b;
			double y2 = (-a*30 -c) /b;
			glVertex2d(0, (y1+30)*10);
			glVertex2d(600, (y2+30)*10);
		}
		glEnd();
	}
};

// Simultaneous Equation Class
class SimultaneousEquation {
public:

	Equation eqn[2];

	bool Solve(double &x, double &y) {
		double a = eqn[0].a;
		double b=eqn[0].b;
		double c=eqn[0].c;
		double d = eqn[1].a
		double e = eqn[1].b;
		double f = eqn[1].c;

        double det = a*e - b*d;

		if(std::abs(det) < tolerance) {
			return false;
		}

		x = (e*c - b*f) / det;
		y = (a*f - c*d) / det;
		return true;
	}

	void Plot() {
		eqn[0].Plot(1.0f, 0.0f, 0.0f);
		eqn[1].Plot(0.0f, 0.0f, 1.0f);
	}
};

class Axes
{
public:
    void Draw()
    {
        glColor3f(0.7f, 0.7f, 0.7f);
        glBegin(GL_LINES);

        for (int i = -30; i <= 30; ++i) {
            glVertex2i(300 + 10 * i, 0);
            glVertex2i(300 + 10 * i, 600);
            glVertex2i(0, 300 - 10 * i);
            glVertex2i(600, 300 - 10 * i);
        }
        glEnd();

        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(300, 0);
        glVertex2i(300, 600);
        glVertex2i(0, 300);
        glVertex2i(600, 300);
        glEnd();
    }
};

int main(void) {
    SimultaneousEquation eqn;
    double x, y;

    std::cout << "ax+by=c\n";
    std::cout << "dx+ey=f\n";
    std::cout << "Enter a b c d e f: ";
    std::cin >> eqn.eqn[0].a >> eqn.eqn[0].b >> eqn.eqn[0].c
            >> eqn.eqn[1].a >> eqn.eqn[1].b >> eqn.eqn[1].c;

    if (eqn.Solve(x, y)) {
        std::cout << "x=" << x << " y=" << y << '\n';
    } else {
        std::cout << "No solution.\n";
    }

    FsOpenWindow(0, 0, 600, 600, 1); 
    Axes axes;

    for (;;) {
        FsPollDevice();
        if (FSKEY_ESC == FsInkey()) {
            break;
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        axes.Draw();
        eqn.Plot();
        FsSwapBuffers();
    }

    return 0;
}