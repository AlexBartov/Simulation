#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "SceneSettingsDialog.h"
#include "MainSceneGL.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainSceneGL *m_mainScene;
private:
    QMenu *fileMenu;
    QAction *fileSaveAct;
    QAction *fileOpenAct;
    QAction *fileNewAct;
    QAction *exitAct;
    QMenu *preferencesMenu;
    QAction *sceneSettingsAct;
    QMenu *helpMenu;
    QAction *aboutAct;
    void createActions();
    void createMenus();
    Ui::MainWindow *ui;
    SceneSettingsDialog *sceneSettingsDialog;
public slots:
    void onCsvLoaded();
    void onCsvFailed();
signals:
    void startScene();
    void stopScene();
    void beginLoadScene();
    void endLoadScene();
private slots:
    void newScene();
    void fileSave();
    void fileOpen();
    void about();
    void sceneSettings();
    void on_startScene_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
