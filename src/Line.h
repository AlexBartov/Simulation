#ifndef THREAD_H
#define THREAD_H
#include "SceneObject.h"
#include "Sphere.h"
#include <glm/gtc/quaternion.hpp>
class Line : public SceneObject
{
public:
    Line(int id, QOpenGLShaderProgram* myProg,
           const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
           GLfloat length = 1.0f,
         GLfloat width = 1.0f);
    glm::vec3 m_scale;
    void setPositions(const glm::vec3 &positions);
    void setPosX(GLfloat xPos);
    void setPosY(GLfloat yPos);
    void setPosZ(GLfloat zPos);

    GLfloat getPosX() const;
    GLfloat getPosY() const;
    GLfloat getPosZ() const;

    void setHeight(GLfloat length);
    void setWidth(GLfloat width);
    GLfloat getHeight() const;
    GLfloat getWidth() const;
    GLint getTargetId();
    void setRotationX(GLfloat rotX);
    void setRotationY(GLfloat rotY);
    void setRotationZ(GLfloat rotZ);

    void draw();
    ~Line();
    void setTarget(Sphere *target);
    void setTarget(int id);

private:
    void setHeightRotation(GLfloat height, const glm::quat &rotation);
    // re-calcuilate model and normal matrices
    void recalcMats();
    GLfloat m_rotX;
    GLfloat m_rotY;
    GLfloat m_rotZ;
    glm::mat4 m_model;
    glm::vec3 m_positions;
    GLfloat m_height;
    GLfloat m_width;
    Sphere *m_target;
    glm::quat m_rotation;
    static QOpenGLShaderProgram *m_myProg;
    static GLuint m_VAO;
    static GLfloat m_vertices[];
    static GLuint m_numVertices;
    static GLuint m_VBO;
};

#endif // THREAD_H
