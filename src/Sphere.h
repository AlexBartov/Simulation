#ifndef SPHERE_H
#define SPHERE_H
#include "SceneObject.h"
#define RES_FACTOR 4
class Sphere : public SceneObject
{
public:
    Sphere(int id, QOpenGLShaderProgram* myProg,
           const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
           GLfloat radius = 1.0f);
    void setScale(const glm::vec3 &scale);
    void setPositions(const glm::vec3 &positions);
    void setPosX(GLfloat xPos);
    void setPosY(GLfloat yPos);
    void setPosZ(GLfloat zPos);
    glm::vec3 getPositions();
    GLfloat getPosX() const;
    GLfloat getPosY() const;
    GLfloat getPosZ() const;

    void setRadius(GLfloat radius);
    GLfloat getRadius() const;

    const std::vector<GLfloat> *xValues;
    const std::vector<GLfloat> *yValues;
    const std::vector<GLfloat> *zValues;

    int xValsIndex;
    int yValsIndex;
    int zValsIndex;

    void draw();
    ~Sphere();
private:
    // re-calcuilate model and normal matrices
    void recalcMats();
    glm::mat4 m_model;
    glm::vec3 m_positions;
    glm::vec3 m_scale;
    GLfloat m_radius;
    static QOpenGLShaderProgram *m_myProg;
    static GLuint m_VAO;
    static GLfloat *m_vertices;
    static GLuint m_numVertices;
    static GLuint m_VBO;
};

#endif // SPHERE_H
