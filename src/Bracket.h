#ifndef BRACKET_H
#define BRACKET_H
#include "SceneObject.h"

class Bracket : public SceneObject
{
public:
    Bracket(int id, QOpenGLShaderProgram* myProg,
         const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
         const glm::vec3 &scale = glm::vec3(3.0f, 1.0f, 1.0f));
    void draw();

    void setPositions(const glm::vec3 &positions);
    void setPosX(GLfloat xPos);
    void setPosY(GLfloat yPos);
    void setPosZ(GLfloat zPos);

    GLfloat getPosX() const;
    GLfloat getPosY() const;
    GLfloat getPosZ() const;

    void setScaleX(GLfloat xScale);
    void setScaleY(GLfloat yScale);
    void setScaleZ(GLfloat zScale);

    GLfloat getScaleX() const;
    GLfloat getScaleY() const;
    GLfloat getScaleZ() const;
    ~Bracket();
private:
    glm::vec3 m_positions;
    glm::mat4 m_model;
    glm::vec3 m_scale;
    static QOpenGLShaderProgram *m_myProg;
    static GLuint m_VAO;
    static GLfloat m_vertices[];
    static GLuint m_VBO;
    void recalcMats();
};

#endif // BRACKET_H
