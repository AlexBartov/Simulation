#include "Bracket.h"
QOpenGLShaderProgram *Bracket::m_myProg = nullptr;
GLuint Bracket::m_VBO = -1;
GLuint Bracket::m_VAO = -1;
GLfloat Bracket::m_vertices[216] =
{
    // Left
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

    -0.499f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    -0.499f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    -0.499f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    -0.499f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    -0.499f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    -0.499f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    // Right
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

     0.499f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     0.499f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     0.499f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     0.499f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     0.499f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     0.499f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

    // Bottom
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f, -0.499f, -0.5f,  0.0f, 1.0f,  0.0f,
     0.5f, -0.499f, -0.5f,  0.0f, 1.0f,  0.0f,
     0.5f, -0.499f,  0.5f,  0.0f, 1.0f,  0.0f,
     0.5f, -0.499f,  0.5f,  0.0f, 1.0f,  0.0f,
    -0.5f, -0.499f,  0.5f,  0.0f, 1.0f,  0.0f,
    -0.5f, -0.499f, -0.5f,  0.0f, 1.0f,  0.0f
};

Bracket::Bracket(int id, QOpenGLShaderProgram* myProg,
           const glm::vec3 &position,
           const glm::vec3 &scale) :
    m_positions(position), m_scale(scale)
{
    m_color = glm::vec3(0.5f, 0.5f, 0.5f);
#ifdef DEBUG
    qWarning() << "Bracket::Bracket(int id, QOpenGLShaderProgram* myProg, ...)";
#endif
    this->type = BRACKET;
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

void Bracket::draw()
{
#ifdef DEBUG
    qWarning() << "Bracket::draw()";
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

void Bracket::setPositions(const glm::vec3 &positions)
{
    m_positions = positions;
    recalcMats();
}

void Bracket::setPosX(GLfloat xPos)
{
    m_positions.x = xPos;
    recalcMats();
}

void Bracket::setPosY(GLfloat yPos)
{
    m_positions.y = yPos;
    recalcMats();
}

void Bracket::setPosZ(GLfloat zPos)
{
    m_positions.z = zPos;
    recalcMats();
}

GLfloat Bracket::getPosX() const
{
    return m_positions.x;
}

GLfloat Bracket::getPosY() const
{
    return m_positions.y;
}

GLfloat Bracket::getPosZ() const
{
    return m_positions.z;
}

void Bracket::setScaleX(GLfloat xScale)
{
    m_scale.x = xScale;
    recalcMats();
}

void Bracket::setScaleY(GLfloat yScale)
{
    m_scale.y = yScale;
    recalcMats();
}

void Bracket::setScaleZ(GLfloat zScale)
{
    m_scale.z = zScale;
    recalcMats();
}

GLfloat Bracket::getScaleX() const
{
    return m_scale.x;
}

GLfloat Bracket::getScaleY() const
{
    return m_scale.y;
}

GLfloat Bracket::getScaleZ() const
{
    return m_scale.z;
}

Bracket::~Bracket()
{
#ifdef DEBUG
    qWarning() << "Bracket::~Bracket()";
#endif
}

void Bracket::recalcMats()
{
    m_model = glm::mat4();
    m_model = glm::translate(m_model, m_positions);
    m_model = glm::scale(m_model, m_scale);
    m_normalMatrix = glm::mat3(glm::transpose(glm::inverse(m_model)));
}

