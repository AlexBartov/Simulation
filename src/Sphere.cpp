#include "Sphere.h"
#include <vector>
QOpenGLShaderProgram *Sphere::m_myProg = nullptr;
GLfloat *Sphere::m_vertices = nullptr;
GLuint Sphere::m_numVertices = 0;
GLuint Sphere::m_VBO = -1;
GLuint Sphere::m_VAO = -1;

Sphere::Sphere(int id, QOpenGLShaderProgram *myProg, const glm::vec3 &position, GLfloat radius)
    : m_radius(radius), m_positions(position), xValsIndex(0), yValsIndex(0), zValsIndex(0),
      xValues(nullptr), yValues(nullptr), zValues(nullptr)
{
    m_color = glm::vec3(1.0f, 0.0f, 0.0f);
    m_scale = glm::vec3(1.0f, 1.0f, 1.0f) * m_radius;
#ifdef DEBUG
    qWarning() << "Sphere::Sphere(int id, QOpenGLShaderProgram *myProg, const glm::vec3 &position, Sphere::radius)";
    qWarning() << "id: " << id;
#endif
    this->type = SPHERE;
    if(!m_myProg)
    {
    m_myProg = myProg;
    }
    if(m_VAO == -1)
    {
        //    Generate sphere coordinates
        //  Create Octahedron
        std::vector<Triangle> *triangles = new std::vector<Triangle>;
        triangles->resize(8);
        // Upside
        triangles->operator [](0) = Triangle(
                                glm::vec3( 1.0f, 0.0f,  0.0f),
                                glm::vec3( 0.0f, 1.0f,  0.0f),
                                glm::vec3( 0.0f, 0.0f,  1.0f)
                                );
        triangles->operator [](1) = Triangle(
                                glm::vec3( 0.0f, 0.0f,  1.0f),
                                glm::vec3( 0.0f, 1.0f,  0.0f),
                                glm::vec3(-1.0f, 0.0f,  0.0f)
                                );
        triangles->operator [](2) = Triangle(
                                glm::vec3(-1.0f, 0.0f,  0.0f),
                                glm::vec3( 0.0f, 1.0f,  0.0f),
                                glm::vec3( 0.0f, 0.0f, -1.0f)
                                );
        triangles->operator [](3) = Triangle(
                                glm::vec3( 0.0f, 0.0f, -1.0f),
                                glm::vec3( 0.0f, 1.0f,  0.0f),
                                glm::vec3( 1.0f, 0.0f,  0.0f)
                                );
        // Downside
        triangles->operator [](4) = Triangle(
                                glm::vec3( 0.0f,  0.0f,  1.0f),
                                glm::vec3( 0.0f, -1.0f,  0.0f),
                                glm::vec3( 1.0f,  0.0f,  0.0f)
                                );
        triangles->operator [](5) = Triangle(
                                glm::vec3(-1.0f,  0.0f,  0.0f),
                                glm::vec3( 0.0f, -1.0f,  0.0f),
                                glm::vec3( 0.0f,  0.0f,  1.0f)
                                );
        triangles->operator [](6) = Triangle(
                                glm::vec3( 0.0f,  0.0f, -1.0f),
                                glm::vec3( 0.0f, -1.0f,  0.0f),
                                glm::vec3(-1.0f,  0.0f,  0.0f)
                                );
        triangles->operator [](7) = Triangle(
                                glm::vec3( 1.0f,  0.0f,  0.0f),
                                glm::vec3( 0.0f, -1.0f,  0.0f),
                                glm::vec3( 0.0f,  0.0f, -1.0f)
                                );
        for(int i = 0; i < RES_FACTOR; i++)
        {
            std::vector<Triangle> *res = Aux_::genTriangles(triangles);
            delete triangles;
            triangles = res;
        }
#ifdef DEBUG
        qWarning() << "triangles->size()" << triangles->size();
#endif
        // Num of triangles times 3 since each triangle contains 3 vertices
        //and times 2 since each vertex has its own normal vector
        // and each vertex contains 3 floats
        m_numVertices = triangles->size() * 3 * 2;
        // Normalize triangles with respect to (0, 0, 0)
        Aux_::normalizeTriangles(triangles, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
        std::vector<glm::vec3> *normals = Aux_::genNormals(triangles);

        m_vertices = Aux_::planeVecs(normals);

#ifdef DEBUG
        qWarning() << "m_numVertices: " << m_numVertices;
#endif
        // remove unnecessary vectors
        delete normals;
        delete triangles;

        m_glFuncs->glGenVertexArrays(1, &m_VAO);
        m_glFuncs->glGenBuffers(1, &m_VBO);
        m_glFuncs->glBindVertexArray(m_VAO);
        m_glFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
          m_glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*(m_numVertices * 3), m_vertices, GL_STATIC_DRAW);
          // Position attribute
          m_glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
          // Normal vector attribute
          m_glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
          m_glFuncs->glEnableVertexAttribArray(0);
          m_glFuncs->glEnableVertexAttribArray(1);
        m_glFuncs->glBindVertexArray(0);
    }
    recalcMats();
    setId(id);
}

void Sphere::setScale(const glm::vec3 &scale)
{
    m_scale = scale;
    recalcMats();
}

void Sphere::setPositions(const glm::vec3 &positions)
{
    m_positions = positions;
    recalcMats();
}

void Sphere::setPosX(GLfloat xPos)
{
    m_positions.x = xPos;
    recalcMats();
}

void Sphere::setPosY(GLfloat yPos)
{
    m_positions.y = yPos;
    recalcMats();
}

void Sphere::setPosZ(GLfloat zPos)
{
    m_positions.z = zPos;
    recalcMats();
}

glm::vec3 Sphere::getPositions()
{
    return m_positions;
}

GLfloat Sphere::getPosX() const
{
    return m_positions.x;
}

GLfloat Sphere::getPosY() const
{
    return m_positions.y;
}

GLfloat Sphere::getPosZ() const
{
    return m_positions.z;
}

void Sphere::setRadius(GLfloat radius)
{
    m_radius = radius;
    m_scale = glm::vec3(1.0f, 1.0f, 1.0f) * m_radius;
    recalcMats();
}

GLfloat Sphere::getRadius() const
{
    return m_radius;
}

void Sphere::draw()
{
    m_glFuncs->glBindVertexArray(m_VAO);
      GLuint modelLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "model");
      GLuint uColorLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "uColor");
      GLuint normalMatLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "normalMat");
      GLuint affectLoc = m_glFuncs->glGetUniformLocation(m_myProg->programId(), "affect");
      m_glFuncs->glUniform3fv(uColorLoc, 1, glm::value_ptr(m_color));
      m_glFuncs->glUniform1i(affectLoc, 1);
      // set model matrix
      m_glFuncs->glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
      // set normal matrix
      m_glFuncs->glUniformMatrix3fv(normalMatLoc, 1, GL_FALSE, glm::value_ptr(m_normalMatrix));
      m_glFuncs->glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
      m_glFuncs->glBindVertexArray(0);
}

Sphere::~Sphere()
{
#ifdef DEBUG
    qWarning() << "Sphere::~Sphere()";
#endif
}

void Sphere::recalcMats()
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_positions);
    m_model = glm::scale(m_model, m_scale);
    m_normalMatrix = glm::mat3(glm::transpose(glm::inverse(m_model)));
}
