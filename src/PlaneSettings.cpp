#include "PlaneSettings.h"
#include "ui_PlaneSettings.h"
#include "MainSceneGL.h"

void PlaneSettings::setTargetObject(Plane *plane)
{
    m_plane = plane;
    updateDataFields();
}

PlaneSettings::PlaneSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaneSettings)
{
    ui->setupUi(this);
    QDoubleValidator *digitsValidator = new QDoubleValidator(-5000, 5000, 3, this);
    QDoubleValidator *digitsValidator2 = new QDoubleValidator(0, 1, 3, this);
    ui->xPos->setValidator(digitsValidator);
    ui->yPos->setValidator(digitsValidator);
    ui->zPos->setValidator(digitsValidator);
    ui->xRot->setValidator(digitsValidator);
    ui->yRot->setValidator(digitsValidator);
    ui->zRot->setValidator(digitsValidator);
    ui->Width->setValidator(digitsValidator);
    ui->Length->setValidator(digitsValidator);
    ui->ColorR->setValidator(digitsValidator2);
    ui->ColorG->setValidator(digitsValidator2);
    ui->ColorB->setValidator(digitsValidator2);
}

PlaneSettings::~PlaneSettings()
{
    delete ui;
}

void PlaneSettings::updateDataFields()
{
    ui->xPos->setText(QString::number(m_plane->getPosX()));
    ui->yPos->setText(QString::number(m_plane->getPosY()));
    ui->zPos->setText(QString::number(m_plane->getPosZ()));
    ui->xRot->setText(QString::number(m_plane->getRotationX()));
    ui->yRot->setText(QString::number(m_plane->getRotationY()));
    ui->zRot->setText(QString::number(m_plane->getRotationZ()));
    ui->Width->setText(QString::number(m_plane->getWidth()));
    ui->Length->setText(QString::number(m_plane->getLength()));
    glm::vec3 color = m_plane->getColor();
    ui->ColorR->setText(QString::number(color.x));
    ui->ColorG->setText(QString::number(color.y));
    ui->ColorB->setText(QString::number(color.z));
    ui->ID->setText(QString::number(m_plane->getId()));
}

void PlaneSettings::on_xPos_textChanged(const QString &arg1)
{
    m_plane->setPosX(arg1.toFloat());
    ui->xPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_yPos_textChanged(const QString &arg1)
{
    m_plane->setPosY(arg1.toFloat());
    ui->yPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_zPos_textChanged(const QString &arg1)
{
    m_plane->setPosZ(arg1.toFloat());
    ui->zPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_xRot_textChanged(const QString &arg1)
{
    m_plane->setRotationX(arg1.toFloat());
    ui->xRot->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_yRot_textChanged(const QString &arg1)
{
    m_plane->setRotationY(arg1.toFloat());
    ui->yRot->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_zRot_textChanged(const QString &arg1)
{
    m_plane->setRotationZ(arg1.toFloat());
    ui->zRot->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_Width_textChanged(const QString &arg1)
{
    m_plane->setWidth(arg1.toFloat());
    ui->Width->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_Length_textChanged(const QString &arg1)
{
    m_plane->setLength(arg1.toFloat());
    ui->Length->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_ColorR_textChanged(const QString &arg1)
{
    m_plane->setColor(arg1.toFloat(), ui->ColorG->text().toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorR->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_ColorG_textChanged(const QString &arg1)
{
    m_plane->setColor(ui->ColorR->text().toFloat(), arg1.toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorG->setText(arg1);
    MainSceneGL::mainScene->update();
}

void PlaneSettings::on_ColorB_textChanged(const QString &arg1)
{
    m_plane->setColor(ui->ColorR->text().toFloat(), ui->ColorG->text().toFloat(), arg1.toFloat());
    ui->ColorB->setText(arg1);
    MainSceneGL::mainScene->update();
}
