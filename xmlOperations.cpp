#include "linemodel.h"


void LineModel::saveXML()
{
    QList<QString> ListCmd;
    QList<QString> ListName;

    foreach(QObject *obj, mLines){
        Line * line = static_cast<Line *> (obj);

        if(line->processName() != "Name" && line->commandName() != "Command")
        {

            QString strName = line->processName();
            QString strCmd = line->commandName();
            if (strName == "" && strCmd == "")
                return;
            ListName.append(strName);
            ListCmd.append(strCmd);
        }

    }
    QDomDocument document;
    QDomElement root = document.createElement("Processes");
    document.appendChild(root);
    for (int i=0 ; i < ListName.length(); i++){
        QDomElement node = document.createElement("Process");
        node.setAttribute("Name",ListName[i]);
        node.setAttribute("Command",ListCmd[i]);
        root.appendChild(node);
    }


    QFile file(m_fileName.toString());

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Failed";

    }
    else {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Finished";
    }
}

void LineModel::loadXML()
{
    QDomDocument document;

    auto filename = m_fileName.toString();
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Failed";

    }
    else {

        if (!document.setContent(&file)) {
            qDebug() << "Failed to load doc.";
        }
        file.close();
    }


    QDomElement root = document.firstChildElement();

    AddFromXML(root,"Process","Name");

}

void LineModel::AddFromXML(QDomElement root, QString tagname, QString attribute)
{
    QDomNodeList items = root.elementsByTagName (tagname);
    QDomNodeList items2 = root.elementsByTagName (tagname);
    QStringList txtList,cmdList;
    int k=0;

    for (int i = 0; i<items.count(); i++){
        QDomNode itemnode = items.at(i);
        if (itemnode.isElement()){
            QDomElement itemele = itemnode.toElement();
            QString txt = itemele.attribute(attribute);
            txtList.append(txt);

        }
    }
    for (int i = 0; i<items.count(); i++){
        QDomNode itemnode = items.at(i);
        if (itemnode.isElement()){
            QDomElement itemele = itemnode.toElement();
            QString txt2 = itemele.attribute("Command");
            cmdList.append(txt2);

        }
    }

    for (int i = 0; i<items.count(); i++){
        QDomNode itemnode = items.at(i);
        if (itemnode.isElement()){
            QDomElement itemele = itemnode.toElement();
            QString txt = itemele.attribute(attribute);
            addLine(txtList[k],cmdList[k],1,"Status",false);
            k++;
        }
    }}


const QVariant &LineModel::fileName() const
{
    return m_fileName;
}

void LineModel::setFileName(const QVariant &newFileName)
{
    if (m_fileName == newFileName)
        return;
    m_fileName = newFileName;
    emit fileNameChanged();
}
