#include "linemodel.h"

void LineModel::removeLine(int index)
{
    beginRemoveRows(QModelIndex(),index,index);
    mLines.removeAt(index);
    endRemoveRows();
    executing = false;
    exitCodeList.clear();
}


void LineModel::removeCheckedLines()
{
    foreach (QObject * obj, mLines) {
        Line * line = static_cast<Line *> (obj);
        if (line->checkBoxState()==true){
            removeLine(mLines.indexOf(line));}
    }}

void LineModel::removeAllLines()
{
    foreach (QObject * obj, mLines) {
        Line * line = static_cast<Line *> (obj);

        removeLine(mLines.indexOf(line));
    }

}
