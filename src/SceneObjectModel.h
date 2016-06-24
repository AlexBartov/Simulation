#ifndef SCENEOBJECTMODEL_H
#define SCENEOBJECTMODEL_H
#include <QAbstractListModel>
#include "SceneObject.h"

class SceneObjectModel : public QAbstractListModel
{
    friend class SceneSettingsDialog;
    friend class MainWindow;
    Q_OBJECT
public:
    static SceneObjectModel *sceneObjectModel;
    SceneObjectModel(QObject *parent = 0, std::vector<SceneObject*> *objectsVec = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                    int role = Qt::EditRole);

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    QModelIndex firstRow();
    QModelIndex lastRow();

    void removeObj(const QModelIndex &index);
    void addObject(Scene_Object_Type type);
    SceneObject *objectByIndex(const QModelIndex &index);

private:
    QStringList &m_objNames;
    std::vector<SceneObject*> *m_objectsVec;
};

#endif // SCENEOBJECTMODEL_H
