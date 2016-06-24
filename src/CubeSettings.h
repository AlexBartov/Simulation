#ifndef CUBESETTINGS_H
#define CUBESETTINGS_H

#include <QWidget>
#include "Cube.h"

namespace Ui {
class CubeSettings;
}

class CubeSettings : public QWidget
{
    Q_OBJECT

public:
    void setTargetObject(Cube *cube);
    explicit CubeSettings(QWidget *parent = 0);
    ~CubeSettings();

private slots:
    void on_xPos_textChanged(const QString &arg1);
    void on_yPos_textChanged(const QString &arg1);
    void on_zPos_textChanged(const QString &arg1);
    void on_Width_textChanged(const QString &arg1);
    void on_Height_textChanged(const QString &arg1);
    void on_Length_textChanged(const QString &arg1);
    void on_ColorR_textChanged(const QString &arg1);
    void on_ColorG_textChanged(const QString &arg1);
    void on_ColorB_textChanged(const QString &arg1);

private:
    void updateDataFields();
    Cube *m_cube;
    Ui::CubeSettings *ui;
};

#endif // CUBESETTINGS_H
