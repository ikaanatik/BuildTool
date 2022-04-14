#include <QDebug>
#include "line.h"

Line::Line(QObject *parent) : QObject(parent)
{

}

Line::Line(const QString &processName, const QString &commandName, const int &processNum, const QString &status, const bool &cBoxState, QObject *parent)
    :    QObject(parent),m_processName(processName),m_commandName(commandName),m_processNum(processNum),m_checkBoxState(cBoxState),m_status(status)

{

}

const QString &Line::processName() const
{
    return m_processName;
}

void Line::setProcessName(const QString &newProcessName)
{
    if (m_processName == newProcessName)
        return;
    m_processName = newProcessName;
    emit processNameChanged(m_processName);
}

const QString &Line::commandName() const
{
    return m_commandName;
}

void Line::setCommandName(const QString &newCommandName)
{
    if (m_commandName == newCommandName)
        return;
    m_commandName = newCommandName;
    emit commandNameChanged(m_commandName);
}

int Line::processNum() const
{
    return m_processNum;
}

void Line::setProcessNum(int newProcessNum)
{
    if (m_processNum == newProcessNum)
        return;
    m_processNum = newProcessNum;
    emit processNumChanged(m_processNum);
}

bool Line::checkBoxState() const
{
    return m_checkBoxState;
}

void Line::setCheckBoxState(bool newCheckBoxState)
{
    if (m_checkBoxState == newCheckBoxState)
        return;
    m_checkBoxState = newCheckBoxState;
    emit checkBoxStateChanged(m_checkBoxState);
}

const QString &Line::status() const
{
    return m_status;
}

void Line::setStatus(const QString &newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged(m_status);
}

