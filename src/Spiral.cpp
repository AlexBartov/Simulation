#include "Spiral.h"
#include "Scene.h"
GLfloat *Spiral::m_vertices = nullptr;
GLuint Spiral::m_numVertices = 0;
GLuint Spiral::m_VBO = -1;
GLuint Spiral::m_VAO = -1;
QOpenGLShaderProgram *Spiral::m_myProg = nullptr;

Spiral::Spiral(int id, QOpenGLShaderProgram *myProg,
               const glm::vec3 &position, GLfloat radius, GLfloat height):
    m_positions(position), m_radius(radius), m_height(height), m_target(nullptr)
{
    m_color = glm::vec3(1.0f, 0.7f, 0.0f);
#ifdef DEBUG
    qWarning() << "Spiral::Spiral(int id, QOpenGLShaderProgram *myProg, const glm::vec3 &position, GLfloat radius)";
#endif
    this->type = SPIRAL;
    if(!m_myProg)
    {
    m_myProg = myProg;
    }
    if(m_VAO == -1)
    {
        // Generate spiral coordinates
        std::vector<glm::vec3> spiral;
        spiral.resize(0);
        GLfloat y = 0.0f;

        for(GLfloat angle = 0.0f; angle <= 22.5f; angle+=.45f)
        {
            glm::vec3 vertex;
            vertex.x = sin(angle);
            vertex.z = cos(angle);
            y += 0.02f;
            vertex.y = y;
            spiral.push_back(vertex);
        }
        m_numVertices = spiral.size();
        m_vertices = Aux_::planeVecs(&spiral);
#ifdef DEBUG
        qWarning() << "Spiral::m_vertices ";
        for(GLuint i = 0; i < m_numVertices; i += 3)
        {
            qWarning() << "    X: " << m_vertices[i] << "Y: " << m_vertices[i + 1] << "Z: " << m_vertices[i + 2];
        }
#endif
#ifdef DEBUG
        qWarning() << "m_numVertices: " << m_numVertices;
#endif
        m_glFuncs->glGenVertexArrays(1, &m_VAO);
        m_glFuncs->glGenBuffers(1, &m_VBO);
        m_glFuncs->glBindVertexArray(m_VAO);
        m_glFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
          m_glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*(m_numVertices * 3), m_vertices, GL_STATIC_DRAW);
          // Position attribute
          m_glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
          m_glFuncs->glEnableVertexAttribArray(0);
        m_glFuncs->glBindVertexArray(0);
    }
    recalcMats();
    setId(id);
}

void Spiral::setPositions(const glm::vec3 &positions)
{
    m_positions = positions;
    recalcMats();
}

void Spiral::setPosX(GLfloat xPos)
{
    m_positions.x = xPos;
    recalcMats();
}

void Spiral::setPosY(GLfloat yPos)
{
    m_positions.y = yPos;
    recalcMats();
}

void Spiral::setPosZ(GLfloat zPos)
{
    m_positions.z = zPos;
    recalcMats();
}

GLfloat Spiral::getPosX() const
{
    return m_positions.x;
}

GLfloat Spiral::getPosY() const
{
    return m_positions.y;
}

GLfloat Spiral::getPosZ() const
{
    return m_positions.z;
}

void Spiral::setRadius(GLfloat radius)
{
    m_radius = radius;
    recalcMats();
}

void Spiral::setHeight(GLfloat height)
{
    m_height = height;
    recalcMats();
}

GLfloat Spiral::getHeight() const
{
    return m_height;
}

GLfloat Spiral::getRadius() const
{
    return m_radius;
}

void Spiral::setTarget(Sphere *target)
{
    m_target = target;
}

GLint Spiral::getTargetId()
{
    if(m_target)
    {
        return m_target->getId();
    }
    else return -1;
}

void Spiral::setTarget(int id)
{
#ifdef DEBUG
    qWarning() << "Spiral::setTarget";
#endif
    SceneObject *sphere = Scene::scene->getSceneObject(id);
    if(sphere)
    {
#ifdef DEBUG
    qWarning() << "target exists";
    qWarning() << "target id:";
    qWarning() << sphere->getId();
#endif
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

void Spiral::draw()
{
#ifdef DEBUG
    qWarning() << "Spiral::draw()";
#endif
    m_glFuncs->glBindVertexArray(m_VAO);
      GLuint modelLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "model");
      GLuint uColorLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "uColor");
      GLuint affectLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "affect");

      m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_color));
      m_glFuncs->glUniform1i(affectLoc, 0);
      if(m_target)
      {
          glm::vec3 targetPos = m_target->getPositions();
          GLfloat height = glm::length(targetPos - m_positions);
          setHeightRotation(glm::length(targetPos - m_positions), glm::angleAxis(glm::acos(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f),glm::normalize(targetPos - m_positions))),
                                                                                  glm::normalize(glm::cross(glm::vec3(0.0f, height, 0.0f),(targetPos - m_positions)))));
      }
      // set model matrix
      m_glFuncs->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
      // set normal matrix
      m_glFuncs->glDrawArrays(GL_LINE_STRIP, 0, m_numVertices);
      m_glFuncs->glBindVertexArray(0);
}

void Spiral::recalcMats()
{
    m_scale = glm::vec3(m_radius, m_height, m_radius);
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_positions);
    m_model = m_model * glm::mat4_cast(m_rotation);
    m_model = glm::scale(m_model, m_scale);
}

Spiral::~Spiral()
{
#ifdef DEBUG
        qWarning() << "Spiral::~Spiral()";
#endif
}

void Spiral::setHeightRotation(GLfloat height, const glm::quat &rotation)
{
    m_height = height;
    m_rotation = rotation;
    recalcMats();
}
