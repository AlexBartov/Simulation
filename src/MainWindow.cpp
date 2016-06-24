#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include "Animate.h"
#include <QProgressBar>
#include <QFileDialog>
#include "SceneObjectModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    sceneSettingsDialog = new SceneSettingsDialog(this);
    ui->setupUi(this);
    setMinimumSize(835, 710);
    setMaximumSize(850, 720);
    QString message = tr("Hold LMB and move cursor to rotate the scene");
    statusBar()->showMessage(message);
    createActions();
    createMenus();
    m_mainScene = ui->openGLWidget;
    ui->progressBar->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    ui->startScene->setEnabled(false);
    connect(sceneSettingsDialog, &SceneSettingsDialog::csvLoaded, this, &MainWindow::onCsvLoaded);
    connect(sceneSettingsDialog, &SceneSettingsDialog::csvFailed, this, &MainWindow::onCsvFailed);
    connect(this, SIGNAL(startScene()), MainSceneGL::mainScene, SLOT(startAnim()));
    connect(this, SIGNAL(stopScene()), MainSceneGL::mainScene, SLOT(stopAnim()));
    connect(sceneSettingsDialog,&SceneSettingsDialog::animSpeedChanged, MainSceneGL::mainScene, &MainSceneGL::speedChanged);
    connect(MainSceneGL::mainScene,&MainSceneGL::timeChanged, ui->progressBar, &QProgressBar::setValue);
    connect(this, &MainWindow::beginLoadScene, sceneSettingsDialog, &SceneSettingsDialog::beginLoadScene);
    connect(this, &MainWindow::endLoadScene, sceneSettingsDialog, &SceneSettingsDialog::endLoadScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    fileSaveAct = new QAction(tr("&Save model"), this);
    fileSaveAct->setStatusTip(tr("Save current model"));
    connect(fileSaveAct, &QAction::triggered, this, &MainWindow::fileSave);

    fileOpenAct = new QAction(tr("&Load model"), this);
    fileOpenAct->setStatusTip(tr("Load from file"));
    connect(fileOpenAct, &QAction::triggered, this, &MainWindow::fileOpen);

    fileNewAct = new QAction(tr("&New model"), this);
    fileNewAct->setStatusTip(tr("Create new model"));
    connect(fileNewAct, &QAction::triggered, this, &MainWindow::newScene);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("exit the program"));
    connect(exitAct, &QAction::triggered, this, &QApplication::quit);

    sceneSettingsAct = new QAction(tr("&Scene Settings"), this);
    sceneSettingsAct->setStatusTip(tr("set scene parameters"));
    connect(sceneSettingsAct, &QAction::triggered, this, &MainWindow::sceneSettings);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("About this program"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(fileNewAct);
    fileMenu->addAction(fileSaveAct);
    fileMenu->addAction(fileOpenAct);
    fileMenu->addAction(exitAct);

    preferencesMenu = menuBar()->addMenu(tr("&Preferences"));
    preferencesMenu->addAction(sceneSettingsAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::onCsvLoaded()
{
    ui->startScene->setEnabled(true);
}

void MainWindow::onCsvFailed()
{
    ui->startScene->setEnabled(false);
}

void MainWindow::newScene()
{
    emit beginLoadScene();
    Scene::scene->clear(true);
    emit endLoadScene();
    MainSceneGL::mainScene->update();
}

void MainWindow::fileSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save model to a file"),
                               "./untitled.model",
                               tr("Model files (*.model)"));
    if(!fileName.length())
    {
        return;
    }
    else
    {
        Scene::scene->save(fileName);
    }
}

void MainWindow::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open model file"), ".", tr("Model files (*.model)"));
    emit beginLoadScene();
    if(!fileName.length())
    {
        return;
    }
    else
    {
        Scene::scene->load(fileName);
    }
    emit endLoadScene();
    MainSceneGL::mainScene->update();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("О программе"),
            tr("<h2>Разработка средств графической интерпретации</h2>"
               "<h2>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; результатов анализа гибридных моделей</h2>"
               "<h3 align = \"center\">Дипломный проект </h3>"
               "<div style=\"font-weight: bold\" align=\"right\">Студент:</div>"
               "<div align=\"right\">Бартов Алексей</div>"
               "<div align=\"right\">ЗФ-122</div>"
               "<div style=\"font-weight: bold\" align=\"right\">Научный руководитель:</div>"
               "<div align=\"right\">Достовалов Д.Н.</div>"
               "<div align=\"right\">НГТУ</div>"
               "<div align=\"right\">Новосибирск. 2016</div>"
               ));
}

void MainWindow::sceneSettings()
{
    sceneSettingsDialog->show();
}

void MainWindow::on_startScene_clicked()
{
    if(MainSceneGL::mainScene->isPlaying)
    {
        return;
    }
    emit startScene();
}

void MainWindow::on_pushButton_clicked()
{
    emit stopScene();
}
