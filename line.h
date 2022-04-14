#ifndef LINE_H
#define LINE_H

#include <QObject>

class Line : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString processName READ processName WRITE setProcessName NOTIFY processNameChanged)
    Q_PROPERTY(QString commandName READ commandName WRITE setCommandName NOTIFY commandNameChanged)
    Q_PROPERTY(int processNum READ processNum WRITE setProcessNum NOTIFY processNumChanged)
    Q_PROPERTY(bool checkBoxState READ checkBoxState WRITE setCheckBoxState NOTIFY checkBoxStateChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)


public:
    explicit Line(QObject *parent = nullptr);

    Line(const QString &processName, const QString &commandName,const int &processNum ,const QString &status,const bool &cBoxState, QObject * parent = nullptr);



    const QString &processName() const;
    void setProcessName(const QString &newProcessName);

    const QString &commandName() const;
    void setCommandName(const QString &newCommandName);

    int processNum() const;
    void setProcessNum(int newProcessNum);

    bool checkBoxState() const;
    void setCheckBoxState(bool newCheckBoxState);

    const QString &status() const;
    Q_INVOKABLE void setStatus(const QString &newStatus);

signals:
    void processNameChanged(const QString processName);
    void commandNameChanged(const QString commandName);
    void processNumChanged(int newProcessNum);
    void checkBoxStateChanged(bool newCheckBoxState);
    void statusChanged(const QString &newStatus);


private:
    QString m_processName;
    QString m_commandName;
    int m_processNum;
    bool m_checkBoxState;
    QString m_status;

};

#endif // LINE_H
