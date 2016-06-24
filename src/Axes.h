#ifndef AXES_H
#define AXES_H

#include "SceneObject.h"
#include "glm/glm.hpp"


class Axes : public SceneObject
{
public:
    Axes(int id, QOpenGLShaderProgram *myProg,
         float xMax =  10.0f, float yMax =  10.0f, float zMax =  10.0f,
         float xMin = -10.0f, float yMin = -10.0f, float zMin = -10.0f
         );
    void draw();
    void setXMax(float xMax);
    void setYMax(float yMax);
    void setZMax(float zMax);
    void setXMin(float xMin);
    void setYMin(float yMin);
    void setZMin(float zMin);
    float getXMax() const;
    float getYMax() const;
    float getZMax() const;
    float getXMin() const;
    float getYMin() const;
    float getZMin() const;

    ~Axes();
    glm::vec3 getXColor() const;
    void setXColor(const glm::vec3 &xColor);

    glm::vec3 getYColor() const;
    void setYColor(const glm::vec3 &yColor);

    glm::vec3 getZColor() const;
    void setZColor(const glm::vec3 &zColor);

    glm::vec3 getTextColor() const;
    void setTextColor(const glm::vec3 &textColor);

private:
    void setCoords();
    static QOpenGLShaderProgram* m_myProg;
    glm::vec3 m_center;
    GLuint m_VAO;
    GLuint m_VBO;
    glm::vec3 m_xColor;
    glm::vec3 m_yColor;
    glm::vec3 m_zColor;
    glm::vec3 m_textColor;
    float m_xMax;
    float m_yMax;
    float m_zMax;
    float m_xMin;
    float m_yMin;
    float m_zMin;
    // Letters parameters
    float m_lHeight;
    float m_lWidth;
    float m_vDistance;
    float m_hDistance;
};

#endif // AXES_H
