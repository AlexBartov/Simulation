#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"
#include <vector>
#include <list>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>

#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "Axes.h"
#include "Spiral.h"
#include "Line.h"
#include "Bracket.h"
#include "Plane.h"
#include "CsvParser/include/csvparser.h"
#include <QString>
#include "Animate.h"
#include <QStringList>
class MainSceneGL;

class Scene
{
public:
    Scene(MainSceneGL *mainScene);
    bool save(const QString &filePath);
    bool load(const QString &filePath);
    SceneObject* add(Scene_Object_Type objectType);
    void draw();
    void clear(bool addAxes = false);
    bool remove(int id);
    SceneObject *getSceneObject(int id);
    void setNear(GLfloat value);
    void setFar(GLfloat value);
    GLfloat getNear();
    GLfloat getFar();
    void rotateCam(float phi, float theta);
    void setGLFuncs(QOpenGLFunctions_4_5_Core *glFuncs);
    static Scene* scene;
    Camera m_camera;
    QString csvPath;
    QStringList csvHeader;
    std::vector<std::vector<GLfloat>> csvTable;
    std::vector<SceneObject *> m_sceneObjects;
    QStringList m_objNames;
    ~Scene();
private:
    // Function that loads shaders specified by *ShaderPath parameter
    bool prepareShaderProgram(const QString& vertexShaderPath,
                              const QString& fragmentShaderPath);
    bool handleObject(const QStringList& objectParams);
    unsigned int getMaxId();
    // Spiral/line/similar objects id's that should obtain target
    std::vector<int> m_childObjectsId;
    // targets ids
    std::vector<int> m_targetObjectsId;
    // apply objects bindings
    void applyBindings();
    GLfloat m_near;
    GLfloat m_far;
    Axes *m_axes;
    QOpenGLShaderProgram m_myProg;
    class MainSceneGL *m_mainScene;
    QOpenGLFunctions_4_5_Core *m_glFuncs;
    unsigned int m_objectCounter;
};

#endif // SCENE_H
