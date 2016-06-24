#ifndef MAINSCENEGL_H
#define MAINSCENEGL_H

//#define FACT_X 0.195f
//#define FACT_Y 0.175f

#define FACT_X 0.14f
#define FACT_Y 0.14f

#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QWidget>
#include <QOpenGLShader>
#include <QMatrix4x4>
#include "Scene.h"
#include <QMouseEvent>
#include "Animate.h"
class MainSceneGL : public  QOpenGLWidget,
        protected  QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit MainSceneGL(QWidget *parent = 0);
    static MainSceneGL *mainScene;
    Scene m_scene;
    float delta;
    int index;
    float getSpeed() const;
    bool isPlaying;
signals:
    void renderDone();
    void timeChanged(GLfloat time);
public slots:
    void startAnim();
    void stopAnim();
    void speedChanged(GLfloat m_speed);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QEventLoop pause;
    QElapsedTimer deltaTimer;
    void finish();
    void nextFrame();
    QOpenGLFunctions_4_5_Core *m_glFuncs;
    QPoint m_lastPos;
    ~MainSceneGL();
    Animate m_animation;
    float m_curTime;
    float m_speed;
    float m_deltaSpeed;
    float m_maxTime;
    bool m_stop;
};
#endif // MAINSCENEGL_H
