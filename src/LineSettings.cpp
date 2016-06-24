#include "LineSettings.h"
#include "ui_LineSettings.h"
#include "MainSceneGL.h"

void LineSettings::setTargetObject(Line *line)
{
    m_line = line;
    updateDataFields();
}

LineSettings::LineSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineSettings)
{
    ui->setupUi(this);

    QDoubleValidator *digitsValidator = new QDoubleValidator(-5000, 5000, 3, this);
    QDoubleValidator *digitsValidator2 = new QDoubleValidator(0, 1, 3, this);
    QDoubleValidator *widthValidator = new QDoubleValidator(0, 100, 3, this);
    QIntValidator *targetValidator = new QIntValidator(-1, 50000, this);
    ui->xPos->setValidator(digitsValidator);
    ui->yPos->setValidator(digitsValidator);
    ui->zPos->setValidator(digitsValidator);
    ui->Width->setValidator(widthValidator);
    ui->Height->setValidator(digitsValidator);
    ui->Target->setValidator(targetValidator);
    ui->ColorR->setValidator(digitsValidator2);
    ui->ColorG->setValidator(digitsValidator2);
    ui->ColorB->setValidator(digitsValidator2);
}

LineSettings::~LineSettings()
{
    delete ui;
}

void LineSettings::on_xPos_textChanged(const QString &arg1)
{
    m_line->setPosX(arg1.toFloat());
    ui->xPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::on_yPos_textChanged(const QString &arg1)
{
    m_line->setPosY(arg1.toFloat());
    ui->yPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::on_zPos_textChanged(const QString &arg1)
{
    m_line->setPosZ(arg1.toFloat());
    ui->zPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::on_Width_textChanged(const QString &arg1)
{
    m_line->setWidth(arg1.toFloat());
    ui->Width->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::on_Height_textChanged(const QString &arg1)
{
    m_line->setHeight(arg1.toFloat());
    ui->Height->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::on_Target_textChanged(const QString &arg1)
{
    SceneObject *target = Scene::scene->getSceneObject(arg1.toInt());
    if(target && target->type == SPHERE)
    {
        m_line->setTarget((Sphere*) target);
        ui->Target->setText(arg1);
        MainSceneGL::mainScene->update();
    }
    else
    {
        m_line->setTarget(nullptr);
        ui->Target->setText(QString::number(-1));
    }
}

void LineSettings::on_ColorR_textChanged(const QString &arg1)
{
    m_line->setColor(arg1.toFloat(), ui->ColorG->text().toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorR->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::on_ColorG_textChanged(const QString &arg1)
{
    m_line->setColor(ui->ColorR->text().toFloat(), arg1.toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorG->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::on_ColorB_textChanged(const QString &arg1)
{
    m_line->setColor(ui->ColorR->text().toFloat(), ui->ColorG->text().toFloat(), arg1.toFloat());
    ui->ColorB->setText(arg1);
    MainSceneGL::mainScene->update();
}

void LineSettings::updateDataFields()
{
    ui->xPos->setText(QString::number(m_line->getPosX()));
    ui->yPos->setText(QString::number(m_line->getPosY()));
    ui->zPos->setText(QString::number(m_line->getPosZ()));
    ui->Height->setText(QString::number(m_line->getHeight()));
    ui->Width->setText(QString::number(m_line->getWidth()));
    ui->Target->setText(QString::number(m_line->getTargetId()));
    glm::vec3 color = m_line->getColor();
    ui->ColorR->setText(QString::number(color.x));
    ui->ColorG->setText(QString::number(color.y));
    ui->ColorB->setText(QString::number(color.z));
    ui->ID->setText(QString::number(m_line->getId()));
}
