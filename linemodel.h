#ifndef LINEMODEL_H
#define LINEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "line.h"
#include <QProcess>
#include <QtXml>
#include <QFileDialog>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>

class LineModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariant fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

    enum Roles{
        ProcessNameRole = Qt::UserRole +1,
        CommandNameRole,
        ProcessNumRole,
        CheckBoxStateRole,
        StatusRole
    };

public:

    explicit LineModel(QObject *parent = nullptr);

    bool initialize();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QHash<int,QByteArray> roleNames() const;

    void addLine (Line *line);

    Q_INVOKABLE void addLine();
    Q_INVOKABLE void addLine(const QString &processName, const QString &commandName,const int &processNum ,const QString &status,const bool &cBoxState);
    Q_INVOKABLE void removeLine(int index);
    Q_INVOKABLE void removeCheckedLines();
    Q_INVOKABLE void removeAllLines();
    Q_INVOKABLE void runCheckedLines();
    Q_INVOKABLE void runAllLines();
    Q_INVOKABLE void saveXML();
    Q_INVOKABLE void loadXML();
    Q_INVOKABLE void outputClear();
    Q_INVOKABLE QStringList argCollector();
    Q_INVOKABLE QStringList checkedArgCollector();
    Q_INVOKABLE void move(int oldIndex,int newIndex);

    const QVariant &fileName() const;
    Q_INVOKABLE void setFileName(const QVariant &newFileName);


signals:
    void outlogText(QString parameter);
    void myLinesChanged(const QList<QObject *> &newMyLines);
    void statusCode(int value);
    void checkedLineIndex(QList<int> value);
    void fileNameChanged();
    void uncheckedLinesSignal(int value);
    void runAgainPressed();

public slots:
    void onProcessFinished(int, QProcess::ExitStatus);
    QStringList outlog();
    void AddFromXML(QDomElement,QString,QString);
    void ExecFinished();
    void ExecFinished2();
    void stopProcess();
    void uncheckedLinesStatus();
    void statusCollect();
    void checkedStatusCollect();
private slots:

private:
    QQmlApplicationEngine mEngine;

    QList<Line*> mLines;

    QProcess *mProcess;
    QStringList argz;

    QList<int> exitCodeList;
    QList<int> exitCodeLis;
    QStringList outputList ;

    QString m_getFileName;
    QVariant m_fileName;
    bool executing=false;
};

inline void LineModel::move(int oldIndex, int newIndex)
{
    QModelIndex parent;

    beginMoveRows(parent,oldIndex,oldIndex,parent,newIndex);
    mLines.move(oldIndex,newIndex);

    endMoveRows();
}



#endif // LINEMODEL_H
