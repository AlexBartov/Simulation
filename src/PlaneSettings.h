#ifndef PLANESETTINGS_H
#define PLANESETTINGS_H

#include <QWidget>
#include "Plane.h"
namespace Ui {
class PlaneSettings;
}

class PlaneSettings : public QWidget
{
    Q_OBJECT

public:
    void setTargetObject(Plane *plane);
    explicit PlaneSettings(QWidget *parent = 0);
    ~PlaneSettings();

private slots:
    void on_xPos_textChanged(const QString &arg1);
    void on_yPos_textChanged(const QString &arg1);
    void on_zPos_textChanged(const QString &arg1);
    void on_xRot_textChanged(const QString &arg1);
    void on_yRot_textChanged(const QString &arg1);
    void on_zRot_textChanged(const QString &arg1);
    void on_Width_textChanged(const QString &arg1);
    void on_Length_textChanged(const QString &arg1);
    void on_ColorR_textChanged(const QString &arg1);
    void on_ColorG_textChanged(const QString &arg1);
    void on_ColorB_textChanged(const QString &arg1);

private:
    Plane *m_plane;
    void updateDataFields();
    Ui::PlaneSettings *ui;
};

#endif // PLANESETTINGS_H
