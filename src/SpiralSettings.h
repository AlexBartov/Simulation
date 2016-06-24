#ifndef SPIRALSETTINGS_H
#define SPIRALSETTINGS_H

#include <QWidget>
#include "Spiral.h"

namespace Ui
{
    class SpiralSettings;
}

class SpiralSettings : public QWidget
{
    Q_OBJECT
public:
    void setTargetObject(Spiral *spiral);
    explicit SpiralSettings(QWidget *parent = 0);
    ~SpiralSettings();
private slots:
    void on_xPos_textChanged(const QString &arg1);
    void on_yPos_textChanged(const QString &arg1);
    void on_zPos_textChanged(const QString &arg1);
    void on_Radius_textChanged(const QString &arg1);
    void on_Height_textChanged(const QString &arg1);
    void on_Target_textChanged(const QString &arg1);
    void on_ColorR_textChanged(const QString &arg1);
    void on_ColorG_textChanged(const QString &arg1);
    void on_ColorB_textChanged(const QString &arg1);
private:
    void updateDataFields();
    Spiral *m_spiral;
    Ui::SpiralSettings *ui;
};

#endif // SPIRALSETTINGS_H
