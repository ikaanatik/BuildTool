#include "linemodel.h"

void LineModel::addLine(Line *line)
{
    const int index = mLines.size();
    beginInsertRows(QModelIndex(),index,index);
    mLines.append(line);
    endInsertRows();
    executing = false;
    exitCodeList.clear();
}

void LineModel::addLine()
{
    Line* line = new Line("Name","Command",0,"Status",false,this);
    addLine(line);
}

void LineModel::addLine(const QString &processName, const QString &commandName, const int &processNum, const QString &status, const bool &cBoxState)
{
    Line* line = new Line(processName,commandName,processNum,status,cBoxState);
    addLine(line);
}
