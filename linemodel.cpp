#include "linemodel.h"
#include <QQuickView>


LineModel::LineModel(QObject *parent)
    : QAbstractListModel(parent)
{
    addLine();

}

bool LineModel::initialize()
{
    mEngine.load(QUrl(QStringLiteral("qrc:/BuildTool/main.qml")));

    if (mEngine.rootObjects().isEmpty()){
        return false;}


    return true;

}

int LineModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mLines.size();
}

QVariant LineModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mLines.size())
        return QVariant();

    Line* line = mLines[index.row()];
    if (role==ProcessNameRole){
        return line->processName();}

    if (role==CommandNameRole){
        return line->commandName();}

    if (role==ProcessNumRole){
        return line->processNum();}

    if (role==CheckBoxStateRole){
        return line->checkBoxState();}

    if (role==StatusRole){
        return line->status();}

    else return "Error status";
}


bool LineModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Line* line = mLines[index.row()];
    bool somethingChanged = false;
    switch (role) {
    case ProcessNameRole:
    {
        if (line->processName()!=value.toString()) {
            line->setProcessName(value.toString());
            somethingChanged = true;
            exitCodeList.clear();
            executing = false;
        }
    }
        break;
    case CommandNameRole:
    {
        if (line->commandName()!=value.toString()) {
            line->setCommandName(value.toString());
            somethingChanged = true;
            exitCodeList.clear();
            executing = false;
        }
    }
        break;
    case ProcessNumRole:
    {
        if (line->processNum()!=value.toInt()) {
            line->setProcessNum(value.toInt());
            somethingChanged = true;
        }
    }
        break;
    case CheckBoxStateRole:
    {
        if (line->checkBoxState()!=value.toBool()) {
            line->setCheckBoxState(value.toBool());
            somethingChanged = true;
            exitCodeList.clear();
            executing = false;
        }
    }
        break;
    case StatusRole:
    {
        if (line->status()!=value.toString()) {
            line->setStatus(value.toString());
            somethingChanged = true;
        }
    }
        if (somethingChanged){
            emit dataChanged(index,index,QVector<int>() << role);
            return true;
            exitCodeList.clear();
            executing = false;
        }
        return false;
    }
    return somethingChanged;
}

Qt::ItemFlags LineModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()){
        return Qt::NoItemFlags;}
    else   return Qt::ItemIsEditable;
}

QHash<int, QByteArray> LineModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ProcessNameRole] = "processName";
    roles[CommandNameRole] = "commandName";
    roles[ProcessNumRole] = "processNum";
    roles[CheckBoxStateRole] = "checkBoxState";
    roles[StatusRole] = "status";
    return roles;
}











