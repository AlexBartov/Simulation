#ifndef SPIRAL_H
#define SPIRAL_H
#include "SceneObject.h"
#include "Sphere.h"
#include <glm/gtc/quaternion.hpp>

class Spiral : public SceneObject
{
public:
    Spiral(int id, QOpenGLShaderProgram* myProg,
           const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
           GLfloat radius = 0.5f,
           GLfloat height = 1.0f);
    glm::vec3 m_scale;
    void setPositions(const glm::vec3 &positions);

    void setPosX(GLfloat xPos);
    void setPosY(GLfloat yPos);
    void setPosZ(GLfloat zPos);

    GLfloat getPosX() const;
    GLfloat getPosY() const;
    GLfloat getPosZ() const;

    void setRadius(GLfloat radius);
    void setHeight(GLfloat height);

    GLfloat getHeight() const;
    GLfloat getRadius() const;
    void setTarget(Sphere *target);
    GLint getTargetId();
    void setTarget(int id);
    void draw();
    ~Spiral();
private:
    void setHeightRotation(GLfloat height, const glm::quat &rotation);
    Sphere *m_target;
    glm::quat m_rotation;
    // re-calcuilate model and normal matrices
    void recalcMats();
    glm::mat4 m_model;
    glm::vec3 m_positions;
    GLfloat m_radius;
    GLfloat m_height;
    static QOpenGLShaderProgram *m_myProg;
    static GLuint m_VAO;
    static GLfloat *m_vertices;
    static GLuint m_numVertices;
    static GLuint m_VBO;
};

#endif // SPIRAL_H
