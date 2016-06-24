#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <glm/glm.hpp>
#include <QOpenGLFunctions>
#define EPSILON 0.000001f

class Animator
{
public:
    static GLfloat epsilon;
    virtual int getObjectId() = 0;
    // move to first position in CSV table
    virtual void firstPos() = 0;
    // move to next frame
    virtual void nextFrame() = 0;
    // set initial position
    virtual void setInitial() = 0;
    // return to initial position
    virtual void revertInitial() = 0;
    Animator();
    virtual ~Animator();
};

#endif // ANIMATOR_H
