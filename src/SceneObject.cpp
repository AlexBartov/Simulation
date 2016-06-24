#include "SceneObject.h"
#include "Sphere.h"
QOpenGLFunctions_4_5_Core *SceneObject::m_glFuncs = nullptr;

int SceneObject::getId()
{
    return m_Id;
}

void SceneObject::setId(int id)
{
    m_Id = id;
}

SceneObject::~SceneObject()
{
#ifdef DEBUG
    qWarning() << "SceneObject::~SceneObject()";
#endif
}

void SceneObject::setColor(GLfloat R, GLfloat G, GLfloat B)
{
    m_color = glm::vec3(R, G, B);
}

const glm::vec3 SceneObject::getColor()
{
    return m_color;
}

std::vector<Triangle>* Aux_::genTriangles(const std::vector<Triangle>* triangles)
{
    std::vector<Triangle>* result = new std::vector<Triangle>;
    result->resize(triangles->size() * 4); // Since each triangle are divided into four ones
    for(int i = 0; i < triangles->size(); i++)
    {
        using namespace Triangle_;
        const Triangle *triangle = &triangles->operator [](i);
        result->operator [](i * 4    ) = Triangle(
                     mid(triangle->C, triangle->A),
                    mid(triangle->A, triangle->B),
                    mid(triangle->B, triangle->C)
                                              );
        result->operator [](i * 4 + 1) = Triangle(mid(triangle->A, triangle->B),
                                                  triangle->B,
                                                  mid(triangle->B, triangle->C)
                                                  );
        result->operator [](i * 4 + 2) = Triangle(triangle->A,
                                                  mid(triangle->A, triangle->B),
                                                  mid(triangle->C, triangle->A));
        result->operator [](i * 4 + 3) = Triangle(mid(triangle->C, triangle->A),
                                                  mid(triangle->B, triangle->C),
                                                  triangle->C
                                                  );
    }
    return result;
}

    // Turn an array of Triangles into an array of vertices
GLfloat* Aux_::planeVecs(const std::vector<Triangle> *triangles)
{
    GLfloat *res = new GLfloat[triangles->size() * 9 * 2];
    for(int i = 0; i < triangles->size(); i++)
    {
        const Triangle *triangle = &triangles->operator [](i);
        res[i * 9]     = triangle->A.x;
        res[i * 9 + 1] = triangle->A.y;
        res[i * 9 + 2] = triangle->A.z;

        res[i * 9 + 3] = triangle->B.x;
        res[i * 9 + 4] = triangle->B.y;
        res[i * 9 + 5] = triangle->B.z;

        res[i * 9 + 6] = triangle->C.x;
        res[i * 9 + 7] = triangle->C.y;
        res[i * 9 + 8] = triangle->C.z;
    }
    return res;
}

    // Normalizes point B with respect to A with a given length
glm::vec3 Aux_::normalize(const glm::vec3 &A, const glm::vec3 &B, const GLfloat length)
{
    // Get the distance between points along the axes
    GLfloat dx = B.x - A.x;
    GLfloat dy = B.y - A.y;
    GLfloat dz = B.z - A.z;
    // now : sqrt(dx^2+dy^2+dz^2) = distance(a,b);
    // we want sqrt(dx^2+dy^2+dz^2) = length
    GLfloat distance = glm::distance(A,B);
    dx = dx * length / distance;
    dy = dy * length / distance;
    dz = dz * length / distance;

    return glm::vec3(A.x + dx, A.y + dy, A.z + dz);
}

void Aux_::normalizeTriangles(std::vector<Triangle> *triangles, const glm::vec3 &point, const GLfloat &length)
{
    for(int i = 0; i < triangles->size(); i++)
    {
        Triangle* triangle = &triangles->operator [](i);
        triangle->A = normalize(point, triangle->A, length);
        triangle->B = normalize(point, triangle->B, length);
        triangle->C = normalize(point, triangle->C, length);
    }
}

GLfloat *Aux_::planeVecs(const std::vector<glm::vec3> *vertices)
{
    GLfloat *res = new GLfloat[vertices->size() * 3];
    for(int i = 0; i < vertices->size(); i++)
    {
        const glm::vec3 *vertex= &vertices->operator [](i);
        res[i * 3]     = vertex->x;
        res[i * 3 + 1] = vertex->y;
        res[i * 3 + 2] = vertex->z;
    }
    return res;
}

Triangle Aux_::normalVec(const Triangle &triangle)
{
    glm::vec3 normal = glm::cross(triangle.B - triangle.A, triangle.C - triangle.A);
    return Triangle(
                normal,
                normal,
                normal
                );
}

std::vector<glm::vec3> *Aux_::genNormals(const std::vector<Triangle> *triangles)
{
    std::vector<glm::vec3>* res = new std::vector<glm::vec3>;
    res->resize(triangles->size() * 3 * 2);
    for(int i = 0; i < triangles->size(); i++)
    {
        const Triangle *triangle = &triangles->operator [](i);
        Triangle normals(normalVec(*triangle));
        res->operator [](i * 6    ) = triangle->A;
        res->operator [](i * 6 + 1) = normals.A;

        res->operator [](i * 6 + 2) = triangle->B;
        res->operator [](i * 6 + 3) = normals.B;

        res->operator [](i * 6 + 4) = triangle->C;
        res->operator [](i * 6 + 5) = normals.C;
    }
    return res;
}

GLfloat Aux_::normalAngle(GLfloat angle)
{
        if(angle < 360.0f || angle > 360.0f)
        {
            int whole = int(glm::abs(angle));               // Fraction part
            return glm::sign(angle) * ((whole % 360) + glm::abs(angle) - whole);
        }
        return angle;
}

QString Aux_::objToStr(SceneObject *object)
{
    Scene_Object_Type type = object->type;
    switch(type)
    {
        case AXES:
            return "Axes";
        case CUBE:
            return "Cube";
        case SPIRAL:
            return "Spiral";
        case SPHERE:
            return "Sphere";
        case LINE:
            return "Line";
        case BRACKET:
            return "Bracket";
        case PLANE:
            return "Plane";
        default:
            return "";
    }
}

QString Aux_::typeToStr(Scene_Object_Type type)
{
    switch(type)
    {
        case AXES:
            return "Axes";
        case CUBE:
            return "Cube";
        case SPIRAL:
            return "Spiral";
        case SPHERE:
            return "Sphere";
        case LINE:
            return "Line";
        case BRACKET:
            return "Bracket";
        case PLANE:
            return "Plane";
        default:
            return "";
    }
}
