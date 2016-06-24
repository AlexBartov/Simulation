#include "BracketSettings.h"
#include "ui_BracketSettings.h"
#include "MainSceneGL.h"

void BracketSettings::setTargetObject(Bracket *bracket)
{
    m_bracket = bracket;
    updateDataFields();
}

BracketSettings::BracketSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BracketSettings)
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

BracketSettings::~BracketSettings()
{
    delete ui;
}

void BracketSettings::updateDataFields()
{
    ui->xPos->setText(QString::number(m_bracket->getPosX()));
    ui->yPos->setText(QString::number(m_bracket->getPosY()));
    ui->zPos->setText(QString::number(m_bracket->getPosZ()));
    ui->Width->setText(QString::number(m_bracket->getScaleX()));
    ui->Height->setText(QString::number(m_bracket->getScaleY()));
    ui->Length->setText(QString::number(m_bracket->getScaleZ()));
    glm::vec3 color = m_bracket->getColor();
    ui->ColorR->setText(QString::number(color.x));
    ui->ColorG->setText(QString::number(color.y));
    ui->ColorB->setText(QString::number(color.z));
    ui->ID->setText(QString::number(m_bracket->getId()));
}

void BracketSettings::on_xPos_textChanged(const QString &arg1)
{
    m_bracket->setPosX(arg1.toFloat());
    ui->xPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_yPos_textChanged(const QString &arg1)
{
    m_bracket->setPosY(arg1.toFloat());
    ui->yPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_zPos_textChanged(const QString &arg1)
{
    m_bracket->setPosZ(arg1.toFloat());
    ui->zPos->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_Width_textChanged(const QString &arg1)
{
    m_bracket->setScaleX(arg1.toFloat());
    ui->Width->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_Height_textChanged(const QString &arg1)
{
    m_bracket->setScaleY(arg1.toFloat());
    ui->Height->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_Length_textChanged(const QString &arg1)
{
    m_bracket->setScaleZ(arg1.toFloat());
    ui->Length->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_ColorR_textChanged(const QString &arg1)
{
    m_bracket->setColor(arg1.toFloat(), ui->ColorG->text().toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorR->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_ColorG_textChanged(const QString &arg1)
{
    m_bracket->setColor(ui->ColorR->text().toFloat(), arg1.toFloat(),  ui->ColorB->text().toFloat());
    ui->ColorG->setText(arg1);
    MainSceneGL::mainScene->update();
}

void BracketSettings::on_ColorB_textChanged(const QString &arg1)
{
    m_bracket->setColor(ui->ColorR->text().toFloat(), ui->ColorG->text().toFloat(), arg1.toFloat());
    ui->ColorB->setText(arg1);
    MainSceneGL::mainScene->update();
}
