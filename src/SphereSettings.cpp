#include "SphereSettings.h"
#include "ui_SphereSettings.h"
#include "MainSceneGL.h"
#include <QFileDialog>

SphereSettings::SphereSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SphereSettings),
    m_sphere(nullptr)
{
    ui->setupUi(this);
    QDoubleValidator *digitsValidator = new QDoubleValidator(-5000, 5000, 3, this);
    QDoubleValidator *digitsValidator2 = new QDoubleValidator(0, 1, 3, this);
    ui->xPos->setValidator(digitsValidator);
    ui->yPos->setValidator(digitsValidator);
    ui->zPos->setValidator(digitsValidator);
    ui->Radius->setValidator(digitsValidator);
    ui->ColorR->setValidator(digitsValidator2);
    ui->ColorG->setValidator(digitsValidator2);
    ui->ColorB->setValidator(digitsValidator2);
}

void SphereSettings::setTargetObject(Sphere *sphere)
{
    m_sphere = sphere;
    updateDataFields();
}

SphereSettings::~SphereSettings()
{
    delete ui;
}

void SphereSettings::onCsvLoaded()
{
    if(m_sphere)
    {
        for(SceneObject* object : Scene::scene->m_sceneObjects)
        {
            if(object->type == SPHERE)
            {
                ((Sphere*)object)->xValsIndex = 0;
                ((Sphere*)object)->yValsIndex = 0;
                ((Sphere*)object)->zValsIndex = 0;
                ((Sphere*)object)->xValues = nullptr;
                ((Sphere*)object)->yValues = nullptr;
                ((Sphere*)object)->zValues = nullptr;
            }
        }
        updateDataFields();
    }
}

void SphereSettings::on_xPos_textChanged(const QString &value)
{
    m_sphere->setPosX(value.toFloat());
    ui->xPos->setText(value);
    MainSceneGL::mainScene->update();
}

void SphereSettings::on_yPos_textChanged(const QString &value)
{
    m_sphere->setPosY(value.toFloat());
    ui->yPos->setText(value);
    MainSceneGL::mainScene->update();
}

void SphereSettings::on_zPos_textChanged(const QString &value)
{
    m_sphere->setPosZ(value.toFloat());
    ui->zPos->setText(value);
    MainSceneGL::mainScene->update();
}

void SphereSettings::on_Radius_textChanged(const QString &value)
{
    m_sphere->setRadius(value.toFloat());
    ui->Radius->setText(value);
    MainSceneGL::mainScene->update();
}

void SphereSettings::updateDataFields()
{
    ui->xValues->clear();
    ui->yValues->clear();
    ui->zValues->clear();
    ui->xValues->addItem("None");
    ui->yValues->addItem("None");
    ui->zValues->addItem("None");
    ui->xValues->addItems(Scene::scene->csvHeader);
    ui->yValues->addItems(Scene::scene->csvHeader);
    ui->zValues->addItems(Scene::scene->csvHeader);
    ui->xValues->setCurrentIndex(m_sphere->xValsIndex);
    ui->yValues->setCurrentIndex(m_sphere->yValsIndex);
    ui->zValues->setCurrentIndex(m_sphere->zValsIndex);
    ui->xPos->setText(QString::number(m_sphere->getPosX()));
    ui->yPos->setText(QString::number(m_sphere->getPosY()));
    ui->zPos->setText(QString::number(m_sphere->getPosZ()));
    ui->Radius->setText(QString::number(m_sphere->getRadius()));
    glm::vec3 color = m_sphere->getColor();
    ui->ColorR->setText(QString::number(color.x));
    ui->ColorG->setText(QString::number(color.y));
    ui->ColorB->setText(QString::number(color.z));
    ui->ID->setText(QString::number(m_sphere->getId()));
}

void SphereSettings::on_ColorR_textChanged(const QString &arg1)
{
    m_sphere->setColor(arg1.toFloat(), ui->ColorG->text().toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorR->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SphereSettings::on_ColorG_textChanged(const QString &arg1)
{
    m_sphere->setColor(ui->ColorR->text().toFloat(), arg1.toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorG->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SphereSettings::on_ColorB_textChanged(const QString &arg1)
{
    m_sphere->setColor(ui->ColorR->text().toFloat(), ui->ColorG->text().toFloat(), arg1.toFloat());
    ui->ColorB->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SphereSettings::on_xValues_activated(int index)
{
    m_sphere->xValsIndex = index;
    if(!index)
    {
        // if there is no axes chosen for m_sphere
        if(!(ui->xValues->currentIndex() || ui->yValues->currentIndex() || ui->zValues->currentIndex()))
        {
            Animate::animation->removeAnimator(m_sphere->getId());
        }
        m_sphere->xValues = nullptr;
        return;
    }
    m_sphere->xValues = &Scene::scene->csvTable[index-1];
#ifdef DEBUG
    qWarning() << "m_sphere->xValues->size(): " << m_sphere->xValues->size();
#endif
    Animate::animation->addAnimator(m_sphere);
}

void SphereSettings::on_yValues_activated(int index)
{
    m_sphere->yValsIndex = index;
    if(!index)
    {
        // if there is no axes chosen for m_sphere
        if(!(ui->xValues->currentIndex() || ui->yValues->currentIndex() || ui->zValues->currentIndex()))
        {
            Animate::animation->removeAnimator(m_sphere->getId());
        }
        m_sphere->yValues = nullptr;
        return;
    }
    m_sphere->yValues = &Scene::scene->csvTable[index-1];
    Animate::animation->addAnimator(m_sphere);
}

void SphereSettings::on_zValues_activated(int index)
{
    m_sphere->zValsIndex = index;
    if(!index)
    {
        // if there is no axes chosen for m_sphere
        if(!(ui->xValues->currentIndex() || ui->yValues->currentIndex() || ui->zValues->currentIndex()))
        {
            Animate::animation->removeAnimator(m_sphere->getId());
        }
        m_sphere->zValues = nullptr;
        return;
    }
    m_sphere->zValues = &Scene::scene->csvTable[index-1];
    Animate::animation->addAnimator(m_sphere);
}
