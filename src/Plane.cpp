#include "Plane.h"

QOpenGLShaderProgram *Plane::m_myProg = nullptr;
GLuint Plane::m_VBO = -1;
GLuint Plane::m_VAO = -1;
GLfloat Plane::m_vertices[72] =
{
    // Top
    -0.5f, 0.001f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f, 0.001f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f, 0.001f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f, 0.001f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f, 0.001f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f, 0.001f, -0.5f,  0.0f,  1.0f,  0.0f,
    // Bottom
    -0.5f, 0.0f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, 0.0f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, 0.0f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, 0.0f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, 0.0f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, 0.0f, -0.5f,  0.0f, -1.0f,  0.0f
};

Plane::Plane(int id, QOpenGLShaderProgram* myProg,
           const glm::vec3 &position,
           const glm::vec3 &scale, GLfloat length, GLfloat width) :
    m_positions(position), m_scale(scale), m_length(length), m_width(width)
{
    m_color = glm::vec3(0.5f, 0.5f, 0.5f);
    m_rotX = m_rotY = m_rotZ = 0;
#ifdef DEBUG
    qWarning() << "Plane::Plane(int id, QOpenGLShaderProgram* myProg, ...)";
#endif
    this->type = PLANE;
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

void Plane::draw()
{
#ifdef DEBUG
    qWarning() << "Plane::draw()";
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
      m_glFuncs->glDrawArrays(GL_TRIANGLES, 0, 12);
      m_glFuncs->glBindVertexArray(0);
}

void Plane::setWidth(GLfloat width)
{
    m_width = width;
    recalcMats();
}

void Plane::setLength(GLfloat length)
{
    m_length = length;
    recalcMats();
}

GLfloat Plane::getWidth() const
{
    return m_width;
}

GLfloat Plane::getLength() const
{
    return m_length;
}

void Plane::setPositions(const glm::vec3 &positions)
{
    m_positions = positions;
    recalcMats();
}

void Plane::setPosX(GLfloat xPos)
{
    m_positions.x = xPos;
    recalcMats();
}

void Plane::setPosY(GLfloat yPos)
{
    m_positions.y = yPos;
    recalcMats();
}

void Plane::setPosZ(GLfloat zPos)
{
    m_positions.z = zPos;
    recalcMats();
}

GLfloat Plane::getPosX() const
{
    return m_positions.x;
}

GLfloat Plane::getPosY() const
{
    return m_positions.y;
}

GLfloat Plane::getPosZ() const
{
    return m_positions.z;
}

void Plane::setRotationX(GLfloat rotX)
{
    m_rotX = Aux_::normalAngle(rotX);
    recalcMats();
}

void Plane::setRotationY(GLfloat rotY)
{
    m_rotY = Aux_::normalAngle(rotY);
    recalcMats();
}

void Plane::setRotationZ(GLfloat rotZ)
{
    m_rotZ = Aux_::normalAngle(rotZ);
    recalcMats();
}

GLfloat Plane::getRotationX() const
{
    return m_rotX;
}

GLfloat Plane::getRotationY() const
{
    return m_rotY;
}

GLfloat Plane::getRotationZ() const
{
    return m_rotZ;
}

Plane::~Plane()
{
#ifdef DEBUG
    qWarning() << "Plane::~Plane()";
#endif
}

void Plane::recalcMats()
{
    m_model = glm::mat4();
    m_scale = glm::vec3(m_width, 1.0f, m_length);

    m_model = glm::translate(m_model, m_positions);
    m_model = glm::rotate(m_model, glm::radians(m_rotX), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(m_rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
    m_model = glm::scale(m_model, m_scale);
}
