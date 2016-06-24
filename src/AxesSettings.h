#ifndef AXESSETTINGS_H
#define AXESSETTINGS_H

#include <QWidget>
#include "Axes.h"

namespace Ui {
class AxesSettings;
}

class AxesSettings : public QWidget
{
    Q_OBJECT
public:
    explicit AxesSettings(QWidget *parent = 0);
    void setTargetObject(Axes *axes);
    ~AxesSettings();

private slots:
    void on_xMin_textChanged(const QString &arg1);
    void on_xMax_textChanged(const QString &arg1);
    void on_yMin_textChanged(const QString &arg1);
    void on_yMax_textChanged(const QString &arg1);
    void on_zMin_textChanged(const QString &arg1);
    void on_zMax_textChanged(const QString &arg1);

private:
    Axes *m_axes;
    void updateDataFields();
    Ui::AxesSettings *ui;
};

#endif // AXESSETTINGS_H
