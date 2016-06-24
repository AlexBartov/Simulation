#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLFunctions>
#include <QDebug>


enum Scene_Object_Type
{
    AXES,
    CUBE,
    SPIRAL,
    SPHERE,
    LINE,
    BRACKET,
    PLANE
};

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Triangle.h"

class SceneObject
{
public:
    static QOpenGLFunctions_4_5_Core *m_glFuncs;
    // draws an object
    virtual void draw() = 0;
    // returns object's Id
    int getId();
    // set object Id
    void setId(int id);
    void setColor(GLfloat R, GLfloat G, GLfloat B);
    const glm::vec3 getColor();
    virtual ~SceneObject();
    Scene_Object_Type type;
protected:
    glm::mat3 m_normalMatrix;
    glm::vec3 m_color;
private:
    int m_Id;
};

namespace Aux_
{
    QString typeToStr(Scene_Object_Type type);
    QString objToStr(SceneObject *object);
    // Divide each triangle given into four ones
    std::vector<Triangle>* genTriangles(const std::vector<Triangle>* triangles);
    // Convert given array of objects into planar vertices array
    GLfloat* planeVecs(const std::vector<Triangle> *triangles);
    GLfloat* planeVecs(const std::vector<glm::vec3> *vertices);
    glm::vec3 normalize(const glm::vec3 &A, const glm::vec3 &B, const GLfloat length);
    void normalizeTriangles(std::vector<Triangle> *triangles, const glm::vec3 &point, const GLfloat &length);
    // Create three normal vertices out of given triangle
    Triangle normalVec(const Triangle& triangle);
    // Create array of vertices along with their normals out of given triangle vector
    std::vector<glm::vec3>* genNormals(const std::vector<Triangle> *triangles);
    GLfloat normalAngle(GLfloat angle);
}

#endif // SCENEOBJECT_H
