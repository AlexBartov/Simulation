#include "MainSceneGL.h"
#include <QDir>
#include <QMessageBox>

MainSceneGL *MainSceneGL::mainScene = nullptr;

MainSceneGL::MainSceneGL(QWidget *parent) : QOpenGLWidget(parent),
    m_scene(this), m_speed (1.0f), isPlaying(false)
{
#ifdef DEBUG
    qWarning() << "MainSceneGL::MainsceneGL(QWidget*)";
#endif
    if(!mainScene)
    {
        mainScene = this;
    }
    else delete this;
    connect(this, SIGNAL(renderDone()), &pause, SLOT(quit()));
}

MainSceneGL::~MainSceneGL()
{
#ifdef DEBUG
    qWarning() << "MainSceneGL::~MainSceneGL()";
#endif
}

void MainSceneGL::initializeGL()
{
#ifdef DEBUG
    qWarning() << "MainSceneGL::initializeGL()";
#endif
    QOpenGLFunctions_4_5_Core::initializeOpenGLFunctions();
    m_glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    if(!m_glFuncs)
    {
#ifdef DEBUG
        qWarning() << "Could not obtain required OpenGL context version";
#endif
        exit(1);
    }
    m_scene.setGLFuncs(m_glFuncs);
    glViewport(0, 0, this->width(), this->height());
    m_scene.draw();
}

void MainSceneGL::paintGL()
{
    m_scene.draw();
    emit renderDone();
}

void MainSceneGL::resizeGL(int width, int height)
{
    glViewport( 0, 0, width, qMax(height, 1 ) );
}

void MainSceneGL::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void MainSceneGL::mouseMoveEvent(QMouseEvent * event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();
    m_lastPos = event->pos();
    if(event->buttons() & Qt::LeftButton)
    {
        m_scene.rotateCam(FACT_X*dx, FACT_Y*dy);
        update();
    }
}

void MainSceneGL::finish()
{
    index = 0;
    m_curTime = 0.0f;
    for(Animator *animator : m_animation.animators)
    {
        animator->revertInitial();
    }
    emit timeChanged(0.0f);
    update();
    isPlaying = false;
}

void MainSceneGL::stopAnim()
{
    m_stop = true;
}

void MainSceneGL::speedChanged(GLfloat speed)
{
    m_speed = speed;
}

void MainSceneGL::startAnim()
{
    isPlaying = true;
    if(!m_animation.time)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Time variable is a nullptr!");
        messageBox.setFixedSize(500,200);
        return;
    }
    m_maxTime = m_animation.time->operator [](m_animation.time->size()-1);
    m_stop = false;
    m_curTime = m_animation.time->operator [](0);
    index = 0;
    deltaTimer.start();
    for(auto animator : m_animation.animators)
    {
        animator->setInitial();
        animator->firstPos();
    }
    update();
    pause.exec();
    return nextFrame();
}

void MainSceneGL::nextFrame()
{
    while(!m_stop)
    {
        m_deltaSpeed = ((deltaTimer.elapsed())/1000.0f)* m_speed;
        if(m_deltaSpeed <= Animator::epsilon)
        {
            m_deltaSpeed = FPS60;
        }
        deltaTimer.restart();
        m_curTime += m_deltaSpeed;
        emit timeChanged(m_curTime * 10000.0f / m_maxTime);
        while((index < m_animation.time->size()) && (m_curTime + m_deltaSpeed >= m_animation.time->operator [](index)))
        {
            index++;
        }
        if(index >= m_animation.time->size())
        {
            break;
        }
        delta = m_deltaSpeed / glm::abs((m_animation.time->operator [](index) - m_curTime));
        for(Animator *animator : m_animation.animators)
        {
            animator->nextFrame();
        }
        update();
        // Wait until render is done
        pause.exec();
    }
    finish();
    return;
}

float MainSceneGL::getSpeed() const
{
    return m_speed;
}
