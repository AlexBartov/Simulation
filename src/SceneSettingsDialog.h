#ifndef SCENESETTINGSDIALOG_H
#define SCENESETTINGSDIALOG_H

#include <QDialog>
#include "SphereSettings.h"
#include "CubeSettings.h"
#include "PlaneSettings.h"
#include "AxesSettings.h"
#include "BracketSettings.h"
#include "SpiralSettings.h"
#include "LineSettings.h"
#include <QWidget>
#include "SceneObjectModel.h"
#include <QItemSelection>

namespace Ui {
class SceneSettingsDialog;
}

class SceneSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SceneObjectModel *m_model;
    explicit SceneSettingsDialog(QWidget *parent = 0);
    void showEvent(QShowEvent *event);
    ~SceneSettingsDialog();
private slots:
    void on_buttonBox_accepted();
    void on_Create_Sphere_Button_clicked();
    void on_Near_textChanged(const QString &value);
    void on_Far_textChanged(const QString &value);
    void on_Zoom_textChanged(const QString &value);
    void on_tabWidget_tabBarClicked(int index);
    void on_Create_Spiral_Button_clicked();
    void on_sceneObjectsList_clicked(const QModelIndex &index);
    void on_Remove_Button_clicked();
    void on_Create_Cube_button_clicked();
    void on_Create_Plane_button_clicked();
    void on_Create_Bracket_button_clicked();
    void on_Create_Line_Button_clicked();
    void on_loadCSV_clicked();
    void on_timeValues_activated(int index);
    void csvUpdated();
    void on_animSpeed_textEdited(const QString &arg1);
signals:
    void animSpeedChanged(GLfloat speed);
    void csvLoaded();
    void csvFailed();
public slots:
    void beginLoadScene();
    void endLoadScene();
    void on_CameraDistance_textChanged(const QString &value);
private:
    Ui::SceneSettingsDialog *ui;
    QWidget *m_currentWidget;
    SphereSettings *m_sphereSettings;
    CubeSettings *m_cubeSettings;
    PlaneSettings *m_planeSettings;
    AxesSettings *m_axesSettings;
    BracketSettings *m_bracketSettings;
    SpiralSettings *m_spiralSettings;
    LineSettings *m_lineSettings;
    void updateDataFields();
};

#endif // SCENESETTINGSDIALOG_H
