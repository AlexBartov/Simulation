#ifndef ANIMATION_H
#define ANIMATION_H
#include <QOpenGLFunctions>
#include <vector>
#include "Animator.h"
#include <QTime>
#include "SceneObject.h"
#include "AnimatorSphere.h"
#include <QElapsedTimer>
#include <QWidget>
#include <QEventLoop>

class Animate
{
public:
    Animate();
    static Animate *animation;
    std::vector<Animator*> animators; //vector of animators
    void addAnimator(SceneObject *object);
    void removeAnimator(int id);
    const std::vector<GLfloat> *time;

private:
    void finish();
    // Check whether animation object for given
    // Scene object exists
    bool exists(SceneObject *object);
};

#endif // ANIMATION_H
