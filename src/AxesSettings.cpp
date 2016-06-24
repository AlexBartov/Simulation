#include "AxesSettings.h"
#include "ui_AxesSettings.h"
#include "MainSceneGL.h"

AxesSettings::AxesSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxesSettings)
{
    ui->setupUi(this);
    QDoubleValidator *axesMinValidator = new QDoubleValidator(-5000, 0, 3, this);
    QDoubleValidator *axesMaxValidator = new QDoubleValidator(0, 5000, 3, this);
    ui->xMin->setValidator(axesMinValidator);
    ui->yMin->setValidator(axesMinValidator);
    ui->zMin->setValidator(axesMinValidator);
    ui->xMax->setValidator(axesMaxValidator);
    ui->yMax->setValidator(axesMaxValidator);
    ui->zMax->setValidator(axesMaxValidator);
}

void AxesSettings::setTargetObject(Axes *axes)
{
    m_axes = axes;
    updateDataFields();
}

AxesSettings::~AxesSettings()
{
    delete ui;
}

void AxesSettings::on_xMin_textChanged(const QString &arg1)
{
    MainSceneGL::mainScene->makeCurrent();
    m_axes->setXMin(arg1.toFloat());
    ui->xMin->setText(arg1);
    MainSceneGL::mainScene->doneCurrent();
    MainSceneGL::mainScene->update();
}

void AxesSettings::on_xMax_textChanged(const QString &arg1)
{
    m_axes->setXMax(arg1.toFloat());
    ui->xMax->setText(arg1);
    MainSceneGL::mainScene->update();
}

void AxesSettings::on_yMin_textChanged(const QString &arg1)
{
    m_axes->setYMin(arg1.toFloat());
    ui->yMin->setText(arg1);
    MainSceneGL::mainScene->update();
}

void AxesSettings::on_yMax_textChanged(const QString &arg1)
{
    m_axes->setYMax(arg1.toFloat());
    ui->yMax->setText(arg1);
    MainSceneGL::mainScene->update();
}

void AxesSettings::on_zMin_textChanged(const QString &arg1)
{
    m_axes->setZMin(arg1.toFloat());
    ui->zMin->setText(arg1);
    MainSceneGL::mainScene->update();
}

void AxesSettings::on_zMax_textChanged(const QString &arg1)
{
    m_axes->setZMax(arg1.toFloat());
    ui->zMax->setText(arg1);
    MainSceneGL::mainScene->update();
}

void AxesSettings::updateDataFields()
{
    ui->xMin->setText(QString::number(m_axes->getXMin()));
    ui->yMin->setText(QString::number(m_axes->getYMin()));
    ui->zMin->setText(QString::number(m_axes->getZMin()));
    ui->xMax->setText(QString::number(m_axes->getXMax()));
    ui->yMax->setText(QString::number(m_axes->getYMax()));
    ui->zMax->setText(QString::number(m_axes->getZMax()));
    ui->ID->setText(QString::number(m_axes->getId()));
}
