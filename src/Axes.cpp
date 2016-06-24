#include "Axes.h"
#define NUMVECS 84
#include "MainSceneGL.h"
QOpenGLShaderProgram *Axes::m_myProg = nullptr;

Axes::Axes(int id, QOpenGLShaderProgram *myProg,
               float xMax, float yMax, float zMax,
               float xMin, float yMin, float zMin):
    m_xMax(xMax), m_yMax(yMax), m_zMax(zMax),
    m_xMin(xMin), m_yMin(yMin), m_zMin(zMin),
    m_xColor(0.0f, 0.0f, 1.0f),
    m_yColor(1.0f, 0.0f, 0.0f),
    m_zColor(0.0f, 1.0f, 0.0f),
    m_lHeight(0.5f),
    m_lWidth(0.5f),
    m_hDistance(0.5f),
    m_vDistance(0.5f)
{
#ifdef DEBUG
    qWarning() << "Axes::Axes(int id, QOpenGLShaderProgram *myProg,\
                  float xMax, float yMax, float zMax,\
                  float xMin, float yMin, float zMin)";
#endif
    this->type = AXES;
    if(!m_myProg)
    {
        m_myProg = myProg;
    }

    m_glFuncs->glGenVertexArrays(1, &m_VAO);
    m_glFuncs->glGenBuffers(1, &m_VBO);

    // Create Buffer object and Set axes coordinates
    GLfloat vertices[NUMVECS] = {0.0f};
    vertices[0] = m_xMin;
    vertices[3] = m_xMax;
    vertices[6] = m_xMax - 0.5f;
    vertices[8] = -0.5f;
    vertices[9] = m_xMax;
    vertices[12] = m_xMax - 0.5f;
    vertices[14] = 0.5f;

    vertices[16] = m_yMin;
    vertices[19] = m_yMax;
    vertices[22] = m_yMax - 0.5f;
    vertices[23] = -0.5f;
    vertices[25] = m_yMax;
    vertices[28] = m_yMax - 0.5f;
    vertices[29] = 0.5f;

    vertices[32] = m_zMin;
    vertices[35] = m_zMax;
    vertices[38] = m_zMax - 0.5f;
    vertices[36] = -0.5f;
    vertices[41] = m_zMax;
    vertices[44] = m_zMax - 0.5f;
    vertices[42] = 0.5f;


    // x letter
    vertices[45] = m_xMax + m_hDistance;
    vertices[46] = m_lHeight + m_vDistance;
//    vertices[47] = 0.0f;

    vertices[48] = m_xMax + m_hDistance + m_lWidth;
    vertices[49] = m_vDistance;
//    vertices[50] = 0.0f;

    vertices[51] = m_xMax + m_hDistance + m_lWidth/2.0f;
    vertices[52] = m_vDistance + m_lHeight/2.0f;
//    vertices[53] = 0.00f;

    vertices[54] = m_xMax + m_hDistance + m_lWidth;
    vertices[55] = m_vDistance + m_lHeight;
//    vertices[56] = 0.00f;

    vertices[57] = m_xMax + m_hDistance;
    vertices[58] = m_vDistance;
//    vertices[59] = 0.00f;

    // z letter
//    vertices[60] = 0.0f;
    vertices[61] = m_vDistance + m_lHeight;
    vertices[62] = m_zMax + m_hDistance;

//    vertices[63] = 0.0f;
    vertices[64] = m_vDistance + m_lHeight;
    vertices[65] = m_zMax + m_hDistance + m_lWidth;

//    vertices[66] = 0.0f;
    vertices[67] = m_vDistance;
    vertices[68] = m_zMax + m_hDistance;

//    vertices[69] = 0.0f;
    vertices[70] = m_vDistance;
    vertices[71] = m_zMax + m_hDistance + m_lWidth;

    // y letter
    vertices[72] = m_hDistance;
    vertices[73] = m_yMax + m_vDistance + m_lHeight;
//    vertices[74] = 0.0f;

    vertices[75] = m_hDistance + m_lWidth/2.0f;
    vertices[76] = m_yMax + m_vDistance + m_lHeight/2.0f;
//    vertices[77] = 0.0f;

    vertices[78] = m_hDistance + m_lWidth;
    vertices[79] = m_yMax + m_vDistance + m_lHeight;
//    vertices[80] = 0.0f;

    vertices[81] = m_hDistance;
    vertices[82] = m_yMax + m_vDistance;
//    vertices[83] = 0.0f;
#ifdef DEBUG
    qWarning() << "After array initialization";
#endif
    m_glFuncs->glBindVertexArray(m_VAO);
    m_glFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*NUMVECS, vertices, GL_DYNAMIC_DRAW);
        m_glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        m_glFuncs->glEnableVertexAttribArray(0);
    m_glFuncs->glBindVertexArray(0);

    setId(id);
}

void Axes::draw()
{
#ifdef DEBUG
    qWarning() << "Axes::draw()";
#endif
    m_glFuncs->glBindVertexArray(m_VAO);
        GLuint uColorLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "uColor");
        GLuint modelLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "model");
        GLuint affectLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "affect");
        glm::mat4 model;
        m_glFuncs->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        m_glFuncs->glUniform1i(affectLoc, 0);
        // draw axes
        // x-axis
        m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_xColor));
        m_glFuncs->glDrawArrays(GL_LINE_STRIP, 0, 5);
        // y-axis
        m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_yColor));
        m_glFuncs->glDrawArrays(GL_LINE_STRIP, 5, 5);
        // z-axis
        m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_zColor));
        m_glFuncs->glDrawArrays(GL_LINE_STRIP, 10, 5);

        // x letter
        m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_xColor));
        m_glFuncs->glDrawArrays(GL_LINE_STRIP, 15, 5);

        // z letter
        m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_zColor));
        m_glFuncs->glDrawArrays(GL_LINE_STRIP, 20, 4);

        // y letter
        m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_yColor));
        m_glFuncs->glDrawArrays(GL_LINE_STRIP, 24, 4);
    m_glFuncs->glBindVertexArray(0);
}

Axes::~Axes()
{
#ifdef DEBUG
    qWarning() << "Axes::~Axes()";
#endif
    m_glFuncs->glDeleteVertexArrays(1, &m_VAO);
    m_glFuncs->glDeleteBuffers(1, &m_VBO);
}

void Axes::setXMax(float xMax)
{
    m_xMax = xMax;
    setCoords();
}

void Axes::setYMax(float yMax)
{
    m_yMax = yMax;
    setCoords();
}

void Axes::setZMax(float zMax)
{
    m_zMax = zMax;
    setCoords();
}

void Axes::setXMin(float xMin)
{
    m_xMin= xMin;
    setCoords();
}

void Axes::setYMin(float yMin)
{
    m_yMin= yMin;
    setCoords();
}

void Axes::setZMin(float zMin)
{
    m_zMin= zMin;
    setCoords();
}

float Axes::getXMax() const
{
    return m_xMax;
}

float Axes::getYMax() const
{
    return m_yMax;
}

float Axes::getZMax() const
{
    return m_zMax;
}

void Axes::setCoords()
{
#ifdef DEBUG
    qWarning() << "Axes::setCoords()";
#endif
    GLfloat vertices[NUMVECS] = {0.0f};
    vertices[0] = m_xMin;
    vertices[3] = m_xMax;
    vertices[6] = m_xMax - 0.5f;
    vertices[8] = -0.5f;
    vertices[9] = m_xMax;
    vertices[12] = m_xMax - 0.5f;
    vertices[14] = 0.5f;

    vertices[16] = m_yMin;
    vertices[19] = m_yMax;
    vertices[22] = m_yMax - 0.5f;
    vertices[23] = -0.5f;
    vertices[25] = m_yMax;
    vertices[28] = m_yMax - 0.5f;
    vertices[29] = 0.5f;

    vertices[32] = m_zMin;
    vertices[35] = m_zMax;
    vertices[38] = m_zMax - 0.5f;
    vertices[36] = -0.5f;
    vertices[41] = m_zMax;
    vertices[44] = m_zMax - 0.5f;
    vertices[42] = 0.5f;

    // x letter
    vertices[45] = m_xMax + m_hDistance;
    vertices[46] = m_lHeight + m_vDistance;
//    vertices[47] = 0.0f;

    vertices[48] = m_xMax + m_hDistance + m_lWidth;
    vertices[49] = m_vDistance;
//    vertices[50] = 0.0f;

    vertices[51] = m_xMax + m_hDistance + m_lWidth/2.0f;
    vertices[52] = m_vDistance + m_lHeight/2.0f;
//    vertices[53] = 0.00f;

    vertices[54] = m_xMax + m_hDistance + m_lWidth;
    vertices[55] = m_vDistance + m_lHeight;
//    vertices[56] = 0.00f;

    vertices[57] = m_xMax + m_hDistance;
    vertices[58] = m_vDistance;
//    vertices[59] = 0.00f;

    // z letter
//    vertices[60] = 0.0f;
    vertices[61] = m_vDistance + m_lHeight;
    vertices[62] = m_zMax + m_hDistance;

//    vertices[63] = 0.0f;
    vertices[64] = m_vDistance + m_lHeight;
    vertices[65] = m_zMax + m_hDistance + m_lWidth;

//    vertices[66] = 0.0f;
    vertices[67] = m_vDistance;
    vertices[68] = m_zMax + m_hDistance;

//    vertices[69] = 0.0f;
    vertices[70] = m_vDistance;
    vertices[71] = m_zMax + m_hDistance + m_lWidth;

    // y letter
    vertices[72] = m_hDistance;
    vertices[73] = m_yMax + m_vDistance + m_lHeight;
//    vertices[74] = 0.0f;

    vertices[75] = m_hDistance + m_lWidth/2.0f;
    vertices[76] = m_yMax + m_vDistance + m_lHeight/2.0f;
//    vertices[77] = 0.0f;

    vertices[78] = m_hDistance + m_lWidth;
    vertices[79] = m_yMax + m_vDistance + m_lHeight;
//    vertices[80] = 0.0f;

    vertices[81] = m_hDistance;
    vertices[82] = m_yMax + m_vDistance;
//    vertices[83] = 0.0f;

    m_glFuncs->glBindVertexArray(m_VAO);
    m_glFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_glFuncs->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*NUMVECS, vertices);
    m_glFuncs->glBindVertexArray(0);
}

glm::vec3 Axes::getTextColor() const
{
    return m_textColor;
}

void Axes::setTextColor(const glm::vec3 &textColor)
{
    m_textColor = textColor;
}

float Axes::getZMin() const
{
    return m_zMin;
}

float Axes::getYMin() const
{
    return m_yMin;
}

float Axes::getXMin() const
{
    return m_xMin;
}

glm::vec3 Axes::getZColor() const
{
    return m_zColor;
}

void Axes::setZColor(const glm::vec3 &zColor)
{
    m_zColor = zColor;
}

glm::vec3 Axes::getYColor() const
{
    return m_yColor;
}

void Axes::setYColor(const glm::vec3 &yColor)
{
    m_yColor = yColor;
}

glm::vec3 Axes::getXColor() const
{
    return m_xColor;
}

void Axes::setXColor(const glm::vec3 &xColor)
{
    m_xColor = xColor;
}
