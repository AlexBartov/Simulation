#include "SceneSettingsDialog.h"
#include "ui_SceneSettingsDialog.h"

#include "MainWindow.h"
#include "MainSceneGL.h"
#include "Scene.h"
#include "Sphere.h"

#include <QFileDialog>

SceneSettingsDialog::SceneSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneSettingsDialog),
    m_model(nullptr),
    m_currentWidget(nullptr)
{
    ui->setupUi(this);
    QDoubleValidator *digitsValidator = new QDoubleValidator(0, 100, 3, this);
    ui->Near->setValidator(digitsValidator);
    ui->Far->setValidator(digitsValidator);
    ui->Zoom->setValidator(digitsValidator);
    ui->animSpeed->setValidator(digitsValidator);

    m_sphereSettings = new SphereSettings(this);
    m_cubeSettings = new CubeSettings(this);
    m_planeSettings = new PlaneSettings(this);
    m_axesSettings = new AxesSettings(this);
    m_bracketSettings = new BracketSettings(this);
    m_spiralSettings = new SpiralSettings(this);
    m_lineSettings = new LineSettings(this);
    ui->SettingsLayout->addWidget(m_sphereSettings);
    ui->SettingsLayout->addWidget(m_cubeSettings);
    ui->SettingsLayout->addWidget(m_planeSettings);
    ui->SettingsLayout->addWidget(m_axesSettings);
    ui->SettingsLayout->addWidget(m_bracketSettings);
    ui->SettingsLayout->addWidget(m_spiralSettings);
    ui->SettingsLayout->addWidget(m_lineSettings);
    m_sphereSettings->hide();
    m_cubeSettings->hide();
    m_planeSettings->hide();
    m_axesSettings->hide();
    m_bracketSettings->hide();
    m_spiralSettings->hide();
    m_lineSettings->hide();

    connect(this,&SceneSettingsDialog::csvLoaded, m_sphereSettings, &SphereSettings::onCsvLoaded);
    connect(this,&SceneSettingsDialog::csvFailed, m_sphereSettings, &SphereSettings::onCsvLoaded);
    connect(this,&SceneSettingsDialog::csvFailed, this, &SceneSettingsDialog::csvUpdated);
    connect(this,&SceneSettingsDialog::csvLoaded, this, &SceneSettingsDialog::csvUpdated);
}

void SceneSettingsDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    ui->Near->setText(QString::number(Scene::scene->getNear()));
    ui->Far->setText(QString::number(Scene::scene->getFar()));
    ui->Zoom->setText(QString::number(Scene::scene->m_camera.getZoom()));
    ui->CameraDistance->setText(QString::number(Scene::scene->m_camera.getDistance()));
    ui->animSpeed->setText(QString::number(MainSceneGL::mainScene->getSpeed()));
    if(!m_model)
    {
        m_model = new SceneObjectModel(this, &Scene::scene->m_sceneObjects);
        ui->sceneObjectsList->setModel(m_model);
    }
}

SceneSettingsDialog::~SceneSettingsDialog()
{
    delete ui;
}

void SceneSettingsDialog::on_buttonBox_accepted()
{
}

void SceneSettingsDialog::on_Near_textChanged(const QString &value)
{
    Scene::scene->setNear(value.toFloat());
    ui->Near->setText(value);
    MainSceneGL::mainScene->update();
}

void SceneSettingsDialog::on_Far_textChanged(const QString &value)
{
    Scene::scene->setFar(value.toFloat());
    ui->Far->setText(value);
    MainSceneGL::mainScene->update();
}

void SceneSettingsDialog::on_Zoom_textChanged(const QString &value)
{
    Scene::scene->m_camera.setZoom(value.toFloat());
    ui->Zoom->setText(value);
    MainSceneGL::mainScene->update();
}

void SceneSettingsDialog::on_tabWidget_tabBarClicked(int index)
{
}

void SceneSettingsDialog::on_Create_Spiral_Button_clicked()
{
    m_model->addObject(SPIRAL);
}

void SceneSettingsDialog::on_CameraDistance_textChanged(const QString &value)
{
    Scene::scene->m_camera.setDistance(value.toFloat());
    ui->CameraDistance->setText(value);
    MainSceneGL::mainScene->update();
}

void SceneSettingsDialog::updateDataFields()
{
    ui->timeValues->clear();
    ui->timeValues->addItem("None");
    ui->timeValues->addItems(Scene::scene->csvHeader);
}

void SceneSettingsDialog::on_sceneObjectsList_clicked(const QModelIndex &index)
{
    SceneObject *object = m_model->objectByIndex(index);
    if(!object)
    {
        return;
    }
    Scene_Object_Type type = object->type;
#ifdef DEBUG
    qWarning() << "type: " << Aux_::typeToStr(type);
#endif
    if(m_currentWidget)
    {
        m_currentWidget->hide();
    }
    switch(type)
    {
    case SPHERE:
       m_sphereSettings->setTargetObject((Sphere*) object);
       m_currentWidget = m_sphereSettings;
       m_currentWidget->show();
        break;
    case CUBE:
        m_cubeSettings->setTargetObject((Cube*) object);
        m_currentWidget = m_cubeSettings;
        m_currentWidget->show();
        break;
    case PLANE:
        m_planeSettings->setTargetObject((Plane*) object);
        m_currentWidget = m_planeSettings;
        m_currentWidget->show();
        break;
    case AXES:
        m_axesSettings->setTargetObject((Axes*) object);
        m_currentWidget = m_axesSettings;
        m_currentWidget->show();
        break;
    case BRACKET:
        m_bracketSettings->setTargetObject((Bracket*) object);
        m_currentWidget = m_bracketSettings;
        m_currentWidget->show();
        break;
    case SPIRAL:
        m_spiralSettings->setTargetObject((Spiral*) object);
        m_currentWidget = m_spiralSettings;
        m_currentWidget->show();
        break;
    case LINE:
        m_lineSettings->setTargetObject((Line*) object);
        m_currentWidget = m_lineSettings;
        m_currentWidget->show();
        break;
    }
}

void SceneSettingsDialog::on_Remove_Button_clicked()
{
    m_model->removeObj(ui->sceneObjectsList->selectionModel()->currentIndex());
    MainSceneGL::mainScene->update();
}

void SceneSettingsDialog::on_Create_Cube_button_clicked()
{
    m_model->addObject(CUBE);
}

void SceneSettingsDialog::on_Create_Sphere_Button_clicked()
{
    m_model->addObject(SPHERE);
}

void SceneSettingsDialog::on_Create_Plane_button_clicked()
{
    m_model->addObject(PLANE);
}

void SceneSettingsDialog::on_Create_Bracket_button_clicked()
{
    m_model->addObject(BRACKET);
}

void SceneSettingsDialog::on_Create_Line_Button_clicked()
{
    m_model->addObject(LINE);
}

void SceneSettingsDialog::on_loadCSV_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open coordinates file"), ".", tr("Csv files (*.csv)"));
#ifdef DEBUG
    qWarning() << "path : " << path;
#endif
    ui->csvPath->setText(path);

    Scene::scene->csvPath = path;
    Scene::scene->csvHeader.clear();
    Scene::scene->csvTable.clear();
    if(!path.length())
    {
        emit csvFailed();
        return;
    }
    QByteArray ba = path.toLatin1();
    const char* cPath = ba.data();

    CsvParser *csvParser = CsvParser_new(cPath, ",", 1);
    CsvRow *header;
    CsvRow *row;

    header = CsvParser_getHeader(csvParser);
    if (header == NULL)
    {
        qWarning() << "CsvParser Error: " << CsvParser_getErrorMessage(csvParser);
        CsvParser_destroy(csvParser);
        Scene::scene->csvPath = "";
        emit csvFailed();
        return;
    }
    // load csv header
    const char **headerFields = CsvParser_getFields(header);
    int headerFieldsNum = CsvParser_getNumFields(header);
    Scene::scene->csvTable.resize(headerFieldsNum);
    for (int i = 0 ; i < headerFieldsNum; i++)
    {
         Scene::scene->csvHeader << headerFields[i];
    }

    // Load csv data
    while ((row = CsvParser_getRow(csvParser)) )
    {
        const char **rowFields = CsvParser_getFields(row);
        for (int i = 0 ; i < CsvParser_getNumFields(row) ; i++)
        {
            Scene::scene->csvTable[i].push_back(QString(rowFields[i]).toFloat());
        }
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvParser);
    emit csvLoaded();
}

void SceneSettingsDialog::on_timeValues_activated(int index)
{
    if(!index)
    {
        Animate::animation->time = nullptr;
        return;
    }
    Animate::animation->time = &Scene::scene->csvTable[index-1];
}

void SceneSettingsDialog::csvUpdated()
{
    updateDataFields();
}

void SceneSettingsDialog::on_animSpeed_textEdited(const QString &arg1)
{
    ui->animSpeed->setText(arg1);
    emit animSpeedChanged(arg1.toFloat());
}

void SceneSettingsDialog::beginLoadScene()
{
    if(m_model)
    {
        m_model->beginResetModel();
    }
}

void SceneSettingsDialog::endLoadScene()
{
    if(m_model)
    {
        m_model->endResetModel();
    }
}
