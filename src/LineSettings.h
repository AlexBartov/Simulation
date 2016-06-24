#ifndef LINESETTINGS_H
#define LINESETTINGS_H

#include <QWidget>
#include "Line.h"

namespace Ui {
class LineSettings;
}

class LineSettings : public QWidget
{
    Q_OBJECT
public:
    void setTargetObject(Line *line);
    explicit LineSettings(QWidget *parent = 0);
    ~LineSettings();

private slots:
    void on_xPos_textChanged(const QString &arg1);
    void on_yPos_textChanged(const QString &arg1);
    void on_zPos_textChanged(const QString &arg1);
    void on_Width_textChanged(const QString &arg1);
    void on_Height_textChanged(const QString &arg1);
    void on_Target_textChanged(const QString &arg1);
    void on_ColorR_textChanged(const QString &arg1);
    void on_ColorB_textChanged(const QString &arg1);
    void on_ColorG_textChanged(const QString &arg1);

private:
    Line *m_line;
    void updateDataFields();
    Ui::LineSettings *ui;
};

#endif // LINESETTINGS_H
