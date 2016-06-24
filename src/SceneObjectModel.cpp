#include "SceneObjectModel.h"
#include "Scene.h"
#include "MainSceneGL.h"
SceneObjectModel *SceneObjectModel::sceneObjectModel = nullptr;

SceneObjectModel::SceneObjectModel(QObject *parent, std::vector<SceneObject *> *objectsVec)
    : QAbstractListModel(parent), m_objectsVec(objectsVec), m_objNames (Scene::scene->m_objNames)
{
#ifdef DEBUG
    qWarning() << "SceneObjectModel::SceneObjectModel(QObject *parent, std::vector";
#endif
    if(!sceneObjectModel)
    {
        sceneObjectModel = this;
    }
    else delete this;
}

int SceneObjectModel::rowCount(const QModelIndex &parent) const
{
    return m_objectsVec->size();
}

QVariant SceneObjectModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= m_objNames.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return m_objNames.at(index.row());
    }
    else
    {
        return QVariant();
    }
}

QVariant SceneObjectModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        return QString("Column %1").arg(section);
    }
    else
    {
        return QString("Row %1").arg(section);
    }
}

Qt::ItemFlags SceneObjectModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool SceneObjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        m_objNames.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool SceneObjectModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row)
    {
        m_objNames.insert(position, "");
    }

    endInsertRows();
    return true;
}

bool SceneObjectModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row)
    {
        m_objNames.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QModelIndex SceneObjectModel::firstRow()
{
    return index(0, 0, QModelIndex());
}

QModelIndex SceneObjectModel::lastRow()
{
    return index(m_objNames.size() - 1, 0, QModelIndex());
}

void SceneObjectModel::removeObj(const QModelIndex &index)
{
    if(!index.isValid())
    {
        return;
    }
    beginRemoveRows(QModelIndex(), index.row(), index.row()+1);
    int position = index.row();
    if(!position)
    {
        endRemoveRows();
        return;
    }
    Scene::scene->remove(m_objectsVec->operator [](position)->getId());
    m_objNames.removeAt(position);

    endRemoveRows();
}

void SceneObjectModel::addObject(Scene_Object_Type type)
{
    beginInsertRows(QModelIndex(), m_objNames.size()-1, m_objNames.size());
        MainSceneGL::mainScene->makeCurrent();
        Scene::scene->add(type);
        MainSceneGL::mainScene->doneCurrent();
        m_objNames.push_back(Aux_::typeToStr(type));
    endInsertRows();
    MainSceneGL::mainScene->update();
}

SceneObject *SceneObjectModel::objectByIndex(const QModelIndex &index)
{
    if(!index.isValid())
    {
        return nullptr;
    }
#ifdef DEBUG
    qWarning() << "Index: " << index.row();
#endif
    if (index.row() >= m_objNames.size())
    {
        return nullptr;
    }
    return m_objectsVec->operator[](index.row());
}
