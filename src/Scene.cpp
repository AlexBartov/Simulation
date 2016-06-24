#include "Scene.h"
#include "MainSceneGL.h"
#include "Camera.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QCoreApplication>
#include <QDir>

Scene *Scene::scene = nullptr;

bool Scene::save(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream out(&file);
    for(int i = 0; i < m_sceneObjects.size(); i++)
    {
        Scene_Object_Type type = m_sceneObjects[i]->type;
        out << m_objNames[i];
        if(type == AXES)
        {
            Axes *axes = (Axes*) m_sceneObjects[i];
            out << "|";
            out << "AXES";
            out << "|";
            out << axes->getId();
            out << "|";
            out << axes->getColor().x;
            out << "|";
            out << axes->getColor().y;
            out << "|";
            out << axes->getColor().z;
            out << "|";
            out << axes->getXMin();
            out << "|";
            out << axes->getXMax();
            out << "|";
            out << axes->getYMin();
            out << "|";
            out << axes->getYMax();
            out << "|";
            out << axes->getZMin();
            out << "|";
            out << axes->getZMax();
            out << "\n";
        }
        if(type == SPHERE)
        {
            Sphere *sphere= (Sphere*)m_sceneObjects[i];
            out << "|";
            out << "SPHERE";
            out << "|";
            out << sphere->getId();
            out << "|";
            out << sphere->getColor().x;
            out << "|";
            out << sphere->getColor().y;
            out << "|";
            out << sphere->getColor().z;
            out << "|";
            out << sphere->getPosX();
            out << "|";
            out << sphere->getPosY();
            out << "|";
            out << sphere->getPosZ();
            out << "|";
            out << sphere->getRadius();
            out << "\n";
        }
        if(type == CUBE)
        {
            Cube *cube= (Cube*)m_sceneObjects[i];
            out << "|";
            out << "CUBE";
            out << "|";
            out << cube->getId();
            out << "|";
            out << cube->getColor().x;
            out << "|";
            out << cube->getColor().y;
            out << "|";
            out << cube->getColor().z;
            out << "|";
            out << cube->getPosX();
            out << "|";
            out << cube->getPosY();
            out << "|";
            out << cube->getPosZ();
            out << "|";
            out << cube->getScaleX();
            out << "|";
            out << cube->getScaleY();
            out << "|";
            out << cube->getScaleZ();
            out << "\n";
        }
        if(type == BRACKET)
        {
            Bracket *bracket= (Bracket*)m_sceneObjects[i];
            out << "|";
            out << "BRACKET";
            out << "|";
            out << bracket->getId();
            out << "|";
            out << bracket->getColor().x;
            out << "|";
            out << bracket->getColor().y;
            out << "|";
            out << bracket->getColor().z;
            out << "|";
            out << bracket->getPosX();
            out << "|";
            out << bracket->getPosY();
            out << "|";
            out << bracket->getPosZ();
            out << "|";
            out << bracket->getScaleX();
            out << "|";
            out << bracket->getScaleY();
            out << "|";
            out << bracket->getScaleZ();
            out << "\n";
        }
        if(type == PLANE)
        {
            Plane *plane= (Plane*)m_sceneObjects[i];
            out << "|";
            out << "PLANE";
            out << "|";
            out << plane->getId();
            out << "|";
            out << plane->getColor().x;
            out << "|";
            out << plane->getColor().y;
            out << "|";
            out << plane->getColor().z;
            out << "|";
            out << plane->getPosX();
            out << "|";
            out << plane->getPosY();
            out << "|";
            out << plane->getPosZ();
            out << "|";
            out << plane->getWidth();
            out << "|";
            out << plane->getLength();
            out << "|";
            out << plane->getRotationX();
            out << "|";
            out << plane->getRotationY();
            out << "|";
            out << plane->getRotationZ();
            out << "\n";
        }
        if(type == SPIRAL)
        {
            Spiral *spiral= (Spiral*)m_sceneObjects[i];
            out << "|";
            out << "SPIRAL";
            out << "|";
            out << spiral->getId();
            out << "|";
            out << spiral->getColor().x;
            out << "|";
            out << spiral->getColor().y;
            out << "|";
            out << spiral->getColor().z;
            out << "|";
            out << spiral->getPosX();
            out << "|";
            out << spiral->getPosY();
            out << "|";
            out << spiral->getPosZ();
            out << "|";
            out << spiral->getHeight();
            out << "|";
            out << spiral->getRadius();
            out << "|";
            out << spiral->getTargetId();
            out << "\n";
        }
        if(type == LINE)
        {
            Line *line= (Line*)m_sceneObjects[i];
            out << "|";
            out << "LINE";
            out << "|";
            out << line->getId();
            out << "|";
            out << line->getColor().x;
            out << "|";
            out << line->getColor().y;
            out << "|";
            out << line->getColor().z;
            out << "|";
            out << line->getPosX();
            out << "|";
            out << line->getPosY();
            out << "|";
            out << line->getPosZ();
            out << "|";
            out << line->getHeight();
            out << "|";
            out << line->getWidth();
            out << "|";
            out << line->getTargetId();
            out << "\n";
        }
    }
    file.close();
    return true;
}

bool Scene::handleObject(const QStringList &objectParams)
{
    m_objNames.push_back(objectParams[0]);
    QString type = objectParams[1];
    MainSceneGL::mainScene->makeCurrent();
    if(type == "AXES")
    {
        Axes *axes = (Axes*) m_sceneObjects[0];
        axes->setId(objectParams[2].toUInt());
        axes->setColor(objectParams[3].toFloat(), objectParams[4].toFloat(), objectParams[5].toFloat());
        axes->setXMin(objectParams[6].toFloat());
        axes->setXMax(objectParams[7].toFloat());
        axes->setYMin(objectParams[8].toFloat());
        axes->setYMax(objectParams[9].toFloat());
        axes->setZMin(objectParams[10].toFloat());
        axes->setZMax(objectParams[11].toFloat());
        return true;
    }
    if(type == "SPHERE")
    {
        Sphere *sphere= (Sphere*)this->add(SPHERE);
        sphere->setId(objectParams[2].toUInt());
        sphere->setColor(objectParams[3].toFloat(), objectParams[4].toFloat(), objectParams[5].toFloat());
        sphere->setPosX(objectParams[6].toFloat());
        sphere->setPosY(objectParams[7].toFloat());
        sphere->setPosZ(objectParams[8].toFloat());
        sphere->setRadius(objectParams[9].toFloat());
        return true;
    }
    if(type == "CUBE")
    {
        Cube *cube= (Cube*)this->add(CUBE);
        cube->setId(objectParams[2].toUInt());
        cube->setColor(objectParams[3].toFloat(), objectParams[4].toFloat(), objectParams[5].toFloat());
        cube->setPosX(objectParams[6].toFloat());
        cube->setPosY(objectParams[7].toFloat());
        cube->setPosZ(objectParams[8].toFloat());
        cube->setScaleX(objectParams[9].toFloat());
        cube->setScaleY(objectParams[10].toFloat());
        cube->setScaleZ(objectParams[11].toFloat());
        return true;
    }
    if(type == "BRACKET")
    {
        Bracket *bracket= (Bracket*)this->add(BRACKET);
        bracket->setId(objectParams[2].toUInt());
        bracket->setColor(objectParams[3].toFloat(), objectParams[4].toFloat(), objectParams[5].toFloat());
        bracket->setPosX(objectParams[6].toFloat());
        bracket->setPosY(objectParams[7].toFloat());
        bracket->setPosZ(objectParams[8].toFloat());
        bracket->setScaleX(objectParams[9].toFloat());
        bracket->setScaleY(objectParams[10].toFloat());
        bracket->setScaleZ(objectParams[11].toFloat());
        return true;
    }
    if(type == "PLANE")
    {
        Plane *plane= (Plane*)this->add(PLANE);
        plane->setId(objectParams[2].toUInt());
        plane->setColor(objectParams[3].toFloat(), objectParams[4].toFloat(), objectParams[5].toFloat());
        plane->setPosX(objectParams[6].toFloat());
        plane->setPosY(objectParams[7].toFloat());
        plane->setPosZ(objectParams[8].toFloat());
        plane->setWidth(objectParams[9].toFloat());
        plane->setLength(objectParams[10].toFloat());
        plane->setRotationX(objectParams[11].toFloat());
        plane->setRotationY(objectParams[12].toFloat());
        plane->setRotationZ(objectParams[13].toFloat());
        return true;
    }
    if(type == "SPIRAL")
    {
        Spiral *spiral= (Spiral*)this->add(SPIRAL);
        spiral->setId(objectParams[2].toUInt());
        m_childObjectsId.push_back(spiral->getId());
        spiral->setColor(objectParams[3].toFloat(), objectParams[4].toFloat(), objectParams[5].toFloat());
        spiral->setPosX(objectParams[6].toFloat());
        spiral->setPosY(objectParams[7].toFloat());
        spiral->setPosZ(objectParams[8].toFloat());
        spiral->setHeight(objectParams[9].toFloat());
        spiral->setRadius(objectParams[10].toFloat());
        m_targetObjectsId.push_back(objectParams[11].toInt());
        return true;
    }
    if(type == "LINE")
    {
        Line *line= (Line*)this->add(LINE);
        line->setId(objectParams[2].toUInt());
        m_childObjectsId.push_back(line->getId());
        line->setColor(objectParams[3].toFloat(), objectParams[4].toFloat(), objectParams[5].toFloat());
        line->setPosX(objectParams[6].toFloat());
        line->setPosY(objectParams[7].toFloat());
        line->setPosZ(objectParams[8].toFloat());
        line->setHeight(objectParams[9].toFloat());
        line->setWidth(objectParams[10].toFloat());
        m_targetObjectsId.push_back(objectParams[11].toInt());
        return true;
    }
    MainSceneGL::mainScene->doneCurrent();
}

unsigned int Scene::getMaxId()
{
    if(!m_sceneObjects.size())
    {
        return (uint)(-1);
    }
    uint id = m_sceneObjects[0]->getId();
    for(int i = 1; i < m_sceneObjects.size(); i++)
    {
        if(m_sceneObjects[i]->getId() > id)
        {
            id = m_sceneObjects[i]->getId();
        }
    }
    return id;
}

void Scene::applyBindings()
{
    for(int i = 0; i < m_childObjectsId.size(); i++)
    {
        SceneObject *object = this->getSceneObject(m_childObjectsId[i]);
        if(object->type == SPIRAL)
        {
            Spiral *spiral = (Spiral*) object;
            spiral->setTarget(m_targetObjectsId[i]);
        }
        if(object->type == LINE)
        {
            Line *line = (Line*) object;
            line->setTarget(m_targetObjectsId[i]);
        }
    }
    m_childObjectsId.clear();
    m_targetObjectsId.clear();
}

bool Scene::load(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    clear();
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QRegExp rx("(\\|)"); // Delimiter between objects parameters
        QStringList objectParams = line.split(rx);
        handleObject(objectParams);
    }
    applyBindings();
    m_objectCounter = getMaxId() + 1;
    file.close();
}

Scene::Scene(MainSceneGL *mainScene) : m_near (0.1f), m_far(100.0f), csvPath("...")
{
    m_sceneObjects.resize(0);
    m_mainScene = mainScene;
    m_objectCounter = 0;
    if(!scene)
    {
        scene = this;
    }
    else delete this;
}

void Scene::setGLFuncs(QOpenGLFunctions_4_5_Core *glFuncs)
{
    SceneObject::m_glFuncs  = glFuncs;
    m_glFuncs = glFuncs;
    prepareShaderProgram(QDir::currentPath() + "/cubeVertex.glsl", QDir::currentPath() + "/cubeFragment.glsl");
    m_axes = new Axes(m_objectCounter++,&m_myProg);
    m_sceneObjects.push_back(m_axes);
    m_objNames.push_back("Axes");
}

void Scene::draw()
{
    m_glFuncs->glEnable(GL_DEPTH_TEST);
    m_glFuncs->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    m_glFuncs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_myProg.bind();
    glm::mat4 view;
    view = m_camera.GetViewMatrix();
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(m_camera.m_zoom), (float)m_mainScene->width()/ (float)m_mainScene->height(), m_near, m_far);
    GLuint lightLoc = m_glFuncs->glGetUniformLocation(m_myProg.programId(), "lightPos");
    GLuint lightColorLoc = m_glFuncs->glGetUniformLocation(m_myProg.programId(), "lightColor");
    GLint viewLoc = m_glFuncs->glGetUniformLocation(m_myProg.programId(), "view");
    GLint projLoc = m_glFuncs->glGetUniformLocation(m_myProg.programId(), "projection");

    m_glFuncs->glUniform3fv(lightColorLoc, 1, glm::value_ptr(m_camera.m_lightColor));
    m_glFuncs->glUniform3fv(lightLoc, 1, glm::value_ptr(m_camera.m_position));
    m_glFuncs->glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    m_glFuncs->glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    if(!m_sceneObjects.empty())
    {
        for(SceneObject *i : m_sceneObjects)
        {
            i->draw();
        }
    }
}

void Scene::clear(bool addAxes)
{
    m_objNames.clear();
    if(addAxes)
    {
        m_objNames.push_back("Axes");
    }
    // Clear list of animators
    Animate::animation->animators.clear();
    // delete everything, except axes
    for(int i = 1; i < m_sceneObjects.size(); i++)
    {
        delete m_sceneObjects[i];
    }
    m_sceneObjects.erase(m_sceneObjects.begin() + 1, m_sceneObjects.end());
}

void Scene::rotateCam(float phi, float theta)
{
    m_camera.rotateCam(phi, theta);
}

SceneObject *Scene::add(Scene_Object_Type objectType)
{
    if(objectType == CUBE)
    {
        Cube *cube = new Cube(m_objectCounter, &m_myProg, glm::vec3(5.0f, 5.0f, 5.0f));
        m_sceneObjects.push_back(cube);
        ++m_objectCounter;
        return cube;
    }
    if(objectType == SPHERE)
    {
        Sphere *sphere = new Sphere(m_objectCounter, &m_myProg, glm::vec3(-7.0f, 5.0f, 5.0f), 1.0f);
        m_sceneObjects.push_back(sphere);
        ++m_objectCounter;
        return sphere;
    }
    if(objectType == SPIRAL)
    {
        Spiral *spiral= new Spiral(m_objectCounter, &m_myProg, glm::vec3(0.0f, 0.0f, 0.0f));
        m_sceneObjects.push_back(spiral);
        ++m_objectCounter;
        return spiral;
    }
    if(objectType == LINE)
    {
        Line *line= new Line(m_objectCounter, &m_myProg, glm::vec3(-10.0f, 0.0f, 5.0f), 5.0f, 100.0f);
        m_sceneObjects.push_back(line);
        ++m_objectCounter;
        return line;
    }
    if(objectType == BRACKET)
    {
        Bracket *bracket = new Bracket(m_objectCounter, &m_myProg, glm::vec3(8.0f, -5.0f, 5.0f));
        m_sceneObjects.push_back(bracket);
        ++m_objectCounter;
        return bracket;
    }
    if(objectType == PLANE)
    {
        Plane *plane = new Plane(m_objectCounter, &m_myProg, glm::vec3(8.0f, 2.0f, 5.0f));
        m_sceneObjects.push_back(plane);
        ++m_objectCounter;
        return plane;
    }
    return nullptr;
}

Scene::~Scene()
{
    for(int i = 0; i < m_sceneObjects.size(); i++)
    {
        delete m_sceneObjects[i];
    }
}

bool Scene::prepareShaderProgram(const QString& vertexShaderPath,
                                           const QString& fragmentShaderPath)
{
    if(m_myProg.isLinked())
    {
        return true;
    }
    // First we load and compile the vertex shader…
    bool result = m_myProg.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderPath);
    if (!result)
    {
        qWarning() << m_myProg.log();
    }

   // …now the fragment shader…
    result = m_myProg.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderPath);
    if (!result)
    {
        qWarning() << m_myProg.log();
    }

   // …and finally we link them to resolve any references.
    result = m_myProg.link();
    if (!result)
    {
        qWarning() << "Could not link shader program:" << m_myProg.log();
    }
    return result;
}

bool Scene::remove(int id)
{
    for(int i=0; i<m_sceneObjects.size(); i++)
    {
        if(m_sceneObjects[i]->getId() == id)
        {
            delete m_sceneObjects[i];
            m_sceneObjects.erase(m_sceneObjects.begin()+i);
            return true;
        }
    }
    return false;
}

SceneObject *Scene::getSceneObject(int id)
{
    for(int i = 0; i < m_sceneObjects.size(); i++)
    {
        if(m_sceneObjects[i]->getId() == id)
        {
            return m_sceneObjects[i];
        }
    }
    return nullptr;
}

void Scene::setNear(GLfloat value)
{
    m_near = value;
}

void Scene::setFar(GLfloat value)
{
    m_far = value;
}

GLfloat Scene::getNear()
{
    return m_near;
}

GLfloat Scene::getFar()
{
    return m_far;
}
