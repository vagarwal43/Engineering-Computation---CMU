#include <vector>
#include <iostream>
#include "fssimplewindow.h"

class Drawing
{
public:
    class Point
    {
        friend class Drawing;
    private:
        int v[2];
    public:
        int &x(void)
        {
            return v[0];
        }
        int &y(void)
        {
            return v[1];
        }
        int x(void) const
        {
            return v[0];
        }
        int y(void) const
        {
            return v[1];
        }
        const int *data(void) const
        {
            return v;
        }
        int *data(void)
        {
            return v;
        }
    };

private:
    class PrimitiveBase
    {
    protected:
        float rgb[3];
        std::vector<Point> vtxs;
    public:
        virtual void Set(float r, float g, float b, const std::vector<Point> &vtxs)
        {
            rgb[0] = r;
            rgb[1] = g;
            rgb[2] = b;
            this->vtxs = vtxs;
        }
        virtual void Draw(void) const = 0;
        virtual ~PrimitiveBase() {}
    };

    class Points : public PrimitiveBase
    {
    public:
        void Draw(void) const override
        {
            glColor3fv(rgb);
            glBegin(GL_POINTS);
            for (const auto &v : vtxs)
            {
                glVertex2iv(v.data());
            }
            glEnd();
        }
    };

    class Lines : public PrimitiveBase
    {
    public:
        void Draw(void) const override
        {
            glColor3fv(rgb);
            glBegin(GL_LINES);
            for (const auto &v : vtxs)
            {
                glVertex2iv(v.data());
            }
            glEnd();
        }
    };

    class LineStrip : public PrimitiveBase
    {
    public:
        void Draw(void) const override
        {
            glColor3fv(rgb);
            glBegin(GL_LINE_STRIP);
            for (const auto &v : vtxs)
            {
                glVertex2iv(v.data());
            }
            glEnd();
        }
    };

    class LineLoop : public PrimitiveBase
    {
    public:
        void Draw(void) const override
        {
            glColor3fv(rgb);
            glBegin(GL_LINE_LOOP);
            for (const auto &v : vtxs)
            {
                glVertex2iv(v.data());
            }
            glEnd();
        }
    };

    std::vector<PrimitiveBase *> primitives;

public:
    Drawing() {}
    ~Drawing()
    {
        CleanUp();
    }
    void CleanUp(void)
    {
        for (auto ptr : primitives)
        {
            delete ptr;
        }
        primitives.clear();
    }
    void DeleteLast(void)
    {
        if (0 < primitives.size())
        {
            delete primitives.back();
            primitives.pop_back();
        }
    }

    void AddPoints(const float rgb[3], const std::vector<Point> &vtxs)
    {
        auto *prim = new Points;
        prim->Set(rgb[0], rgb[1], rgb[2], vtxs);
        primitives.push_back(prim);
    }
    void AddLines(const float rgb[3], const std::vector<Point> &vtxs)
    {
        auto *prim = new Lines;
        prim->Set(rgb[0], rgb[1], rgb[2], vtxs);
        primitives.push_back(prim);
    }
    void AddLineStrip(const float rgb[3], const std::vector<Point> &vtxs)
    {
        auto *prim = new LineStrip;
        prim->Set(rgb[0], rgb[1], rgb[2], vtxs);
        primitives.push_back(prim);
    }
    void AddLineLoop(const float rgb[3], const std::vector<Point> &vtxs)
    {
        auto *prim = new LineLoop;
        prim->Set(rgb[0], rgb[1], rgb[2], vtxs);
        primitives.push_back(prim);
    }
    void Draw(void) const
    {
        for (const auto ptr : primitives)
        {
            ptr->Draw();
        }
    }
};

int main(void)
{
    FsOpenWindow(0, 0, 800, 600, 1);
    Drawing drawing;

    std::cout << "[Controls]\n";
    std::cout << "Zero to Seven: Change Color\n";
    std::cout << "L: Insert lines\n";
    std::cout << "S: Insert a line strip.\n";
    std::cout << "O: Insert a line loop.\n";
    std::cout << "P: Insert points.\n";
    std::cout << "Mouse Click: Add a vertex.\n";
    std::cout << "Delete: Delete last primitive.\n";
    std::cout << "Back Space: Delete last vertex.\n";

    glPointSize(2);
    glLineWidth(2);

    float rgb[3] = {0, 0, 0};
    std::vector<Drawing::Point> vtxs;
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
        case FSKEY_BS:
            if (0 < vtxs.size())
            {
                vtxs.pop_back();
            }
            break;
        case FSKEY_DEL:
            drawing.DeleteLast();
            break;
        case FSKEY_0:
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 0;
            break;
        case FSKEY_1:
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 1;
            break;
        case FSKEY_2:
            rgb[0] = 1;
            rgb[1] = 0;
            rgb[2] = 0;
            break;
        case FSKEY_3:
            rgb[0] = 1;
            rgb[1] = 0;
            rgb[2] = 1;
            break;
        case FSKEY_4:
            rgb[0] = 0;
            rgb[1] = 1;
            rgb[2] = 0;
            break;
        case FSKEY_5:
            rgb[0] = 0;
            rgb[1] = 1;
            rgb[2] = 1;
            break;
        case FSKEY_6:
            rgb[0] = 1;
            rgb[1] = 1;
            rgb[2] = 0;
            break;
        case FSKEY_7:
            rgb[0] = 1;
            rgb[1] = 1;
            rgb[2] = 1;
            break;
        case FSKEY_L:
            drawing.AddLines(rgb, vtxs);
            vtxs.clear();
            break;
        case FSKEY_S:
            drawing.AddLineStrip(rgb, vtxs);
            vtxs.clear();
            break;
        case FSKEY_O:
            drawing.AddLineLoop(rgb, vtxs);
            vtxs.clear();
            break;
        case FSKEY_P:
            drawing.AddPoints(rgb, vtxs);
            vtxs.clear();
            break;
        }

        int lb, mb, rb, mx, my;
        auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);
        if (FSMOUSEEVENT_LBUTTONDOWN == evt)
        {
            Drawing::Point p;
            p.x() = mx;
            p.y() = my;
            vtxs.push_back(p);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawing.Draw();
        glColor3fv(rgb);
        glBegin(GL_POINTS);
        for (const auto &v : vtxs)
        {
            glVertex2iv(v.data());
        }
        glEnd();
        FsSwapBuffers();
    }
}
