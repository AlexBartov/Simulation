#ifndef BRACKETSETTINGS_H
#define BRACKETSETTINGS_H

#include <QWidget>
#include "Bracket.h"

namespace Ui {
class BracketSettings;
}

class BracketSettings : public QWidget
{
    Q_OBJECT

public:
    void setTargetObject(Bracket *bracket);
    explicit BracketSettings(QWidget *parent = 0);
    ~BracketSettings();

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
    Bracket *m_bracket;
    Ui::BracketSettings *ui;
};

#endif // BRACKETSETTINGS_H
