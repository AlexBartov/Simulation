#include "Line.h"
#include "Scene.h"
QOpenGLShaderProgram *Line::m_myProg = nullptr;
GLfloat Line::m_vertices[6] =
{
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

GLuint Line::m_numVertices = 0;
GLuint Line::m_VBO = -1;
GLuint Line::m_VAO = -1;

Line::Line(int id, QOpenGLShaderProgram* myProg,
            const glm::vec3 &position,
            GLfloat length, GLfloat width):
    m_height(length), m_positions(position), m_width(width),
    m_rotX(0), m_rotY(0), m_rotZ(0), m_target(nullptr)
{
    m_color = glm::vec3(0.5f, 0.5f, 0.5f);
#ifdef DEBUG
    qWarning() << "Line::Line(int id, QOpenGLShaderProgram* myProg, ...)";
#endif
    this->type = LINE;
    if(!m_myProg)
    {
    m_myProg = myProg;
    }
    if(m_VAO == -1)
    {
        m_glFuncs->glGenVertexArrays(1, &m_VAO);
        m_glFuncs->glGenBuffers(1, &m_VBO);
        m_glFuncs->glBindVertexArray(m_VAO);
        m_glFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
          m_glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
          // Position attribute
          m_glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
          m_glFuncs->glEnableVertexAttribArray(0);
        m_glFuncs->glBindVertexArray(0);
    }
    recalcMats();
    setId(id);
}

void Line::setPositions(const glm::vec3 &positions)
{
    m_positions = positions;
    recalcMats();
}

void Line::setPosX(GLfloat xPos)
{
    m_positions.x = xPos;
    recalcMats();
}

void Line::setPosY(GLfloat yPos)
{
    m_positions.y = yPos;
    recalcMats();
}

void Line::setPosZ(GLfloat zPos)
{
    m_positions.z = zPos;
    recalcMats();
}

GLfloat Line::getPosX() const
{
    return m_positions.x;
}

GLfloat Line::getPosY() const
{
    return m_positions.y;
}

GLfloat Line::getPosZ() const
{
    return m_positions.z;
}

void Line::setHeight(GLfloat length)
{
    m_height = length;
    recalcMats();
}

void Line::setWidth(GLfloat width)
{
    m_width = width;
    recalcMats();
}

GLfloat Line::getHeight() const
{
    return m_height;
}

GLfloat Line::getWidth() const
{
    return m_width;
}

GLint Line::getTargetId()
{
    if(m_target)
    {
        return m_target->getId();
    }
    else return -1;
}

void Line::setRotationX(GLfloat rotX)
{
    m_rotX = Aux_::normalAngle(rotX);
    recalcMats();
}

void Line::setRotationY(GLfloat rotY)
{
    m_rotY = Aux_::normalAngle(rotY);
    recalcMats();
}

void Line::setRotationZ(GLfloat rotZ)
{
    m_rotZ = Aux_::normalAngle(rotZ);
    recalcMats();
}

void Line::draw()
{
#ifdef DEBUG
    qWarning() << "Line::draw()";
#endif
    m_glFuncs->glBindVertexArray(m_VAO);
      GLuint modelLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "model");
      GLuint affectLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "affect");
      GLuint uColorLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "uColor");

      m_glFuncs->glUniform1i(affectLoc, 0);
      m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_color));
      if(m_target)
      {
          glm::vec3 targetPos = m_target->getPositions();
          GLfloat height = glm::length(targetPos - m_positions);
          setHeightRotation(glm::length(targetPos - m_positions), glm::angleAxis(glm::acos(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f),glm::normalize(targetPos - m_positions))),
                                                                                  glm::normalize(glm::cross(glm::vec3(0.0f, height, 0.0f),(targetPos - m_positions)))));
      }
      m_glFuncs->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
      m_glFuncs->glLineWidth(m_width);
      m_glFuncs->glDrawArrays(GL_LINE_STRIP, 0, 2);
      m_glFuncs->glLineWidth(1.0f);
      m_glFuncs->glBindVertexArray(0);
}

Line::~Line()
{
#ifdef DEBUG
    qWarning() << "Line::~Line()";
#endif
}

void Line::recalcMats()
{
    m_model = glm::mat4();
    m_scale = glm::vec3(1.0f, m_height, 1.0f);
    m_model = glm::translate(m_model, m_positions);
    m_model = m_model * glm::mat4_cast(m_rotation);
    m_model = glm::scale(m_model, m_scale);
}

void Line::setTarget(Sphere *target)
{
    m_target = target;
}

void Line::setTarget(int id)
{
    SceneObject *sphere = Scene::scene->getSceneObject(id);
    if(sphere)
    {
        if(sphere->type != SPHERE)
        {
            m_target = nullptr;
            return;
        }
        m_target = (Sphere*) sphere;
    }
    else
    {
        m_target = nullptr;
    }
}

void Line::setHeightRotation(GLfloat height, const glm::quat &rotation)
{
    m_height = height;
    m_rotation = rotation;
    recalcMats();
}
