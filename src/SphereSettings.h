#ifndef SPHERESETTINGS_H
#define SPHERESETTINGS_H

#include <QWidget>
#include "Sphere.h"
namespace Ui
{
    class SphereSettings;
}

class SphereSettings : public QWidget
{
    Q_OBJECT
public:
    explicit SphereSettings(QWidget *parent = 0);
    void setTargetObject(Sphere *sphere);
    ~SphereSettings();
public slots:
    void onCsvLoaded();
private slots:
    void on_xPos_textChanged(const QString &value);
    void on_yPos_textChanged(const QString &value);
    void on_zPos_textChanged(const QString &value);
    void on_Radius_textChanged(const QString &value);
    void on_ColorR_textChanged(const QString &arg1);
    void on_ColorG_textChanged(const QString &arg1);
    void on_ColorB_textChanged(const QString &arg1);
    void on_xValues_activated(int index);
    void on_yValues_activated(int index);
    void on_zValues_activated(int index);
private:
    void updateDataFields();
    Ui::SphereSettings *ui;
    Sphere *m_sphere;
};

#endif // SPHERESETTINGS_H
