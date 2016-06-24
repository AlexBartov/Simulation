#include "Cube.h"
QOpenGLShaderProgram *Cube::m_myProg = nullptr;
GLuint Cube::m_VBO = -1;
GLuint Cube::m_VAO = -1;
GLfloat Cube::m_vertices[216] =
{
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    // Bottom
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    // Top
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

Cube::Cube(int id, QOpenGLShaderProgram* myProg,
           const glm::vec3 &position,
           const glm::vec3 &scale) :
    m_positions(position), m_scale(scale)
{
    m_color = glm::vec3(0.5f, 0.5f, 0.5f);
#ifdef DEBUG
    qWarning() << "Cube::Cube(int id, QOpenGLShaderProgram *myProg)";
#endif
    this->type = CUBE;
    if(!m_myProg)
    {
    m_myProg = myProg;
    }
    if(m_VAO == -1)
    {
#ifdef DEBUG
    qWarning() << "    m_glFuncs->glGenVertexArrays(1, &m_VAO)";
#endif
        m_glFuncs->glGenVertexArrays(1, &m_VAO);
#ifdef DEBUG
    qWarning() << "    m_glFuncs->glGenBuffers(1, &m_VBO)";
#endif
        m_glFuncs->glGenBuffers(1, &m_VBO);
#ifdef DEBUG
    qWarning() << "    m_VAO: " << m_VAO;
    qWarning() << "    m_VBO: " << m_VBO;
#endif
        m_glFuncs->glBindVertexArray(m_VAO);
        m_glFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
          m_glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
          // Position attribute
          m_glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
          // Normal vector Attribute
          m_glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat)*3));
          m_glFuncs->glEnableVertexAttribArray(0);
          m_glFuncs->glEnableVertexAttribArray(1);
        m_glFuncs->glBindVertexArray(0);
    }
    recalcMats();
    setId(id);
}

void Cube::draw()
{
#ifdef DEBUG
    qWarning() << "Cube::draw()";
#endif
    m_glFuncs->glBindVertexArray(m_VAO);
      GLuint modelLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "model");
      GLuint affectLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "affect");
      GLuint normalMatLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "normalMat");
      GLuint uColorLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "uColor");

      m_glFuncs->glUniform1i(affectLoc, 1);
      m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_color));
      m_glFuncs->glUniformMatrix3fv(normalMatLoc, 1, GL_FALSE, glm::value_ptr(m_normalMatrix));
      m_glFuncs->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
      m_glFuncs->glDrawArrays(GL_TRIANGLES, 0, 36);
      m_glFuncs->glBindVertexArray(0);
}

void Cube::setPositions(const glm::vec3 &positions)
{
    m_positions = positions;
    recalcMats();
}

void Cube::setPosX(GLfloat xPos)
{
    m_positions.x = xPos;
    recalcMats();
}

void Cube::setPosY(GLfloat yPos)
{
    m_positions.y = yPos;
    recalcMats();
}

void Cube::setPosZ(GLfloat zPos)
{
    m_positions.z = zPos;
    recalcMats();
}

GLfloat Cube::getPosX() const
{
    return m_positions.x;
}

GLfloat Cube::getPosY() const
{
    return m_positions.y;
}

GLfloat Cube::getPosZ() const
{
    return m_positions.z;
}

void Cube::setScaleX(GLfloat xScale)
{
    m_scale.x = xScale;
    recalcMats();
}

void Cube::setScaleY(GLfloat yScale)
{
    m_scale.y = yScale;
    recalcMats();
}

void Cube::setScaleZ(GLfloat zScale)
{
    m_scale.z = zScale;
    recalcMats();
}

GLfloat Cube::getScaleX() const
{
    return m_scale.x;
}

GLfloat Cube::getScaleY() const
{
    return m_scale.y;
}

GLfloat Cube::getScaleZ() const
{
    return m_scale.z;
}

Cube::~Cube()
{
#ifdef DEBUG
    qWarning() << "Cube::~Cube()";
#endif
}

void Cube::recalcMats()
{
    m_model = glm::mat4();
    m_model = glm::translate(m_model, m_positions);
    m_model = glm::scale(m_model, m_scale);

    m_normalMatrix = glm::mat3(glm::transpose(glm::inverse(m_model)));
}
