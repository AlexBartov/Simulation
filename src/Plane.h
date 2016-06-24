#ifndef PLANE_H
#define PLANE_H
#include "SceneObject.h"


class Plane : public SceneObject
{
public:
    Plane(int id, QOpenGLShaderProgram* myProg,
         const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
         const glm::vec3 &scale = glm::vec3(3.0f, 1.0f, 1.0f),
            GLfloat length = 8.0f,
          GLfloat width = 5.0f);
    void draw();

    void setWidth(GLfloat width);
    void setLength(GLfloat length);

    GLfloat getWidth() const;
    GLfloat getLength() const;

    void setPositions(const glm::vec3 &positions);
    void setPosX(GLfloat xPos);
    void setPosY(GLfloat yPos);
    void setPosZ(GLfloat zPos);

    GLfloat getPosX() const;
    GLfloat getPosY() const;
    GLfloat getPosZ() const;

    void setRotationX(GLfloat rotX);
    void setRotationY(GLfloat rotY);
    void setRotationZ(GLfloat rotZ);

    GLfloat getRotationX() const;
    GLfloat getRotationY() const;
    GLfloat getRotationZ() const;

    ~Plane();
private:
    glm::vec3 m_positions;
    glm::mat4 m_model;
    glm::vec3 m_scale;
    GLfloat m_length;
    GLfloat m_width;
    GLfloat m_rotX;
    GLfloat m_rotY;
    GLfloat m_rotZ;
    static QOpenGLShaderProgram *m_myProg;
    static GLuint m_VAO;
    static GLfloat m_vertices[];
    static GLuint m_VBO;
    void recalcMats();
};

#endif // PLANE_H
