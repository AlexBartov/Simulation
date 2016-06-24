#include "SpiralSettings.h"
#include "ui_SpiralSettings.h"
#include "MainSceneGL.h"

void SpiralSettings::setTargetObject(Spiral *spiral)
{
    m_spiral = spiral;
    updateDataFields();
}

SpiralSettings::SpiralSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpiralSettings)
{
    ui->setupUi(this);
    QDoubleValidator *digitsValidator = new QDoubleValidator(-5000, 5000, 3, this);
    QDoubleValidator *digitsValidator2 = new QDoubleValidator(0, 1, 3, this);
    QIntValidator *targetValidator = new QIntValidator(-1, 50000, this);
    ui->xPos->setValidator(digitsValidator);
    ui->yPos->setValidator(digitsValidator);
    ui->zPos->setValidator(digitsValidator);
    ui->Height->setValidator(digitsValidator);
    ui->Target->setValidator(targetValidator);
    ui->Radius->setValidator(digitsValidator);
    ui->ColorR->setValidator(digitsValidator2);
    ui->ColorG->setValidator(digitsValidator2);
    ui->ColorB->setValidator(digitsValidator2);
}

SpiralSettings::~SpiralSettings()
{
    delete ui;
}

void SpiralSettings::updateDataFields()
{
    ui->xPos->setText(QString::number(m_spiral->getPosX()));
    ui->yPos->setText(QString::number(m_spiral->getPosY()));
    ui->zPos->setText(QString::number(m_spiral->getPosZ()));
    ui->Height->setText(QString::number(m_spiral->getHeight()));
    ui->Radius->setText(QString::number(m_spiral->getRadius()));
    ui->Target->setText(QString::number(m_spiral->getTargetId()));
    glm::vec3 color = m_spiral->getColor();
    ui->ColorR->setText(QString::number(color.x));
    ui->ColorG->setText(QString::number(color.y));
    ui->ColorB->setText(QString::number(color.z));
    ui->ID->setText(QString::number(m_spiral->getId()));
}

void SpiralSettings::on_xPos_textChanged(const QString &arg1)
{
    m_spiral->setPosX(arg1.toFloat());
    ui->xPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SpiralSettings::on_yPos_textChanged(const QString &arg1)
{
    m_spiral->setPosY(arg1.toFloat());
    ui->yPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SpiralSettings::on_zPos_textChanged(const QString &arg1)
{
    m_spiral->setPosZ(arg1.toFloat());
    ui->zPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SpiralSettings::on_Radius_textChanged(const QString &arg1)
{
    m_spiral->setRadius(arg1.toFloat());
    ui->Radius->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SpiralSettings::on_Height_textChanged(const QString &arg1)
{
    m_spiral->setHeight(arg1.toFloat());
    ui->Height->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SpiralSettings::on_Target_textChanged(const QString &arg1)
{
    SceneObject *target = Scene::scene->getSceneObject(arg1.toInt());
    if(target && target->type == SPHERE)
    {
        m_spiral->setTarget((Sphere*) target);
        ui->Target->setText(arg1);
        MainSceneGL::mainScene->update();
    }
    else
    {
        m_spiral->setTarget(nullptr);
        ui->Target->setText(QString::number(-1));
    }
}

void SpiralSettings::on_ColorR_textChanged(const QString &arg1)
{
    m_spiral->setColor(arg1.toFloat(), ui->ColorG->text().toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorR->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SpiralSettings::on_ColorG_textChanged(const QString &arg1)
{
    m_spiral->setColor(ui->ColorR->text().toFloat(), arg1.toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorG->setText(arg1);
    MainSceneGL::mainScene->update();
}

void SpiralSettings::on_ColorB_textChanged(const QString &arg1)
{
    m_spiral->setColor(ui->ColorR->text().toFloat(), ui->ColorG->text().toFloat(), arg1.toFloat());
    ui->ColorB->setText(arg1);
    MainSceneGL::mainScene->update();
}
