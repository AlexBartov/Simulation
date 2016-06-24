#include "CubeSettings.h"
#include "ui_CubeSettings.h"
#include "MainSceneGL.h"

CubeSettings::CubeSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CubeSettings)
{
    ui->setupUi(this);
    QDoubleValidator *digitsValidator = new QDoubleValidator(-5000, 5000, 3, this);
    QDoubleValidator *digitsValidator2 = new QDoubleValidator(0, 1, 3, this);
    ui->xPos->setValidator(digitsValidator);
    ui->yPos->setValidator(digitsValidator);
    ui->zPos->setValidator(digitsValidator);
    ui->Width->setValidator(digitsValidator);
    ui->Height->setValidator(digitsValidator);
    ui->Length->setValidator(digitsValidator);
    ui->ColorR->setValidator(digitsValidator2);
    ui->ColorG->setValidator(digitsValidator2);
    ui->ColorB->setValidator(digitsValidator2);
}

void CubeSettings::setTargetObject(Cube *cube)
{
    m_cube = cube;
    updateDataFields();
}

CubeSettings::~CubeSettings()
{
    delete ui;
}

void CubeSettings::updateDataFields()
{
    ui->xPos->setText(QString::number(m_cube->getPosX()));
    ui->yPos->setText(QString::number(m_cube->getPosY()));
    ui->zPos->setText(QString::number(m_cube->getPosZ()));
    ui->Width->setText(QString::number(m_cube->getScaleX()));
    ui->Height->setText(QString::number(m_cube->getScaleY()));
    ui->Length->setText(QString::number(m_cube->getScaleZ()));
    glm::vec3 color = m_cube->getColor();
    ui->ColorR->setText(QString::number(color.x));
    ui->ColorG->setText(QString::number(color.y));
    ui->ColorB->setText(QString::number(color.z));
    ui->ID->setText(QString::number(m_cube->getId()));
}

void CubeSettings::on_xPos_textChanged(const QString &arg1)
{
    m_cube->setPosX(arg1.toFloat());
    ui->xPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_yPos_textChanged(const QString &arg1)
{
    m_cube->setPosY(arg1.toFloat());
    ui->yPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_zPos_textChanged(const QString &arg1)
{
    m_cube->setPosZ(arg1.toFloat());
    ui->zPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_Width_textChanged(const QString &arg1)
{
    m_cube->setScaleX(arg1.toFloat());
    ui->Width->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_Height_textChanged(const QString &arg1)
{
    m_cube->setScaleY(arg1.toFloat());
    ui->Height->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_Length_textChanged(const QString &arg1)
{
    m_cube->setScaleZ(arg1.toFloat());
    ui->Length->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_ColorR_textChanged(const QString &arg1)
{
    m_cube->setColor(arg1.toFloat(), ui->ColorG->text().toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorR->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_ColorG_textChanged(const QString &arg1)
{
    m_cube->setColor(ui->ColorR->text().toFloat(), arg1.toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorG->setText(arg1);
    MainSceneGL::mainScene->update();
}

void CubeSettings::on_ColorB_textChanged(const QString &arg1)
{
    m_cube->setColor(ui->ColorR->text().toFloat(), ui->ColorG->text().toFloat(), arg1.toFloat());
    ui->ColorB->setText(arg1);
    MainSceneGL::mainScene->update();
}
