#include "AnimatorSphere.h"
#include "Animate.h"
#include <glm/gtx/string_cast.hpp>
#include "MainSceneGL.h"

AnimatorSphere::AnimatorSphere(Sphere *sphere)
    : m_sphere(sphere)
{
}

int AnimatorSphere::getObjectId()
{
    return m_sphere->getId();
}

void AnimatorSphere::nextFrame()
{
    int index = MainSceneGL::mainScene->index;
    GLfloat posX = csvPosX(index);
    GLfloat posY = csvPosY(index);
    GLfloat posZ = csvPosZ(index);
//#ifdef DEBUG
//    qWarning() << "AnimatorSphere::nextFrame()";
//    qWarning() << "positions: " << "(" << posX << "," << posY << "," << posZ << ")";
//#endif
    m_sphere->setPositions(interpolate(m_sphere->getPositions(), glm::vec3(posX, posY, posZ), MainSceneGL::mainScene->delta));
}

void AnimatorSphere::setInitial()
{
    m_initialPos = m_sphere->getPositions();
}

void AnimatorSphere::revertInitial()
{
    m_sphere->setPositions(m_initialPos);
}

void AnimatorSphere::firstPos()
{
    m_sphere->setPositions(glm::vec3(csvPosX(0), csvPosY(0), csvPosZ(0)));
}

GLfloat AnimatorSphere::csvPosX(int i)
{
    if(m_sphere->xValues)
    {
        return m_sphere->xValues->operator [](i);
    }
    else return m_initialPos.x;
}

GLfloat AnimatorSphere::csvPosY(int i)
{
    if(m_sphere->yValues)
    {
        return m_sphere->yValues->operator [](i);
    }
    else return m_initialPos.y;
}

GLfloat AnimatorSphere::csvPosZ(int i)
{
    if(m_sphere->zValues)
    {
        return m_sphere->zValues->operator [](i);
    }
    else return m_initialPos.z;
}

glm::vec3 AnimatorSphere::interpolate(const glm::vec3 &p1, const glm::vec3 &p2, const GLfloat &delta)
{
    glm::vec3 result;
    if(delta >=1.0f)
    {
        result = p2;
//        result = glm::mix(p1, p2, 1.0f);
    }
    if(delta <= epsilon)
    {
        result = p1;
//        result = glm::mix(p1, p2, 1.0f);
    }
    result = glm::mix(p1, p2, delta);
#ifdef DEBUG
    qWarning() << "intepolation result: " << glm::to_string(result).c_str();
#endif
    return result;
}
