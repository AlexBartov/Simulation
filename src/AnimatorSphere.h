#ifndef ANIMATORSPHERE_H
#define ANIMATORSPHERE_H
#include "Animator.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#define FPS60 0.016f

class AnimatorSphere : public Animator
{
public:
    AnimatorSphere(Sphere* sphere);
    int getObjectId();
    void nextFrame();
    void setInitial();
    void revertInitial();
    void firstPos();
    Sphere *m_sphere;
private:
    glm::vec3 m_initialPos;
    GLfloat csvPosX(int i);
    GLfloat csvPosY(int i);
    GLfloat csvPosZ(int i);
    glm::vec3 interpolate(const glm::vec3 &p1, const glm::vec3 &p2, const GLfloat &delta);
};

#endif // ANIMATORSPHERE_H
