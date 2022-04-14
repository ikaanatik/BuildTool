#include "linemodel.h"

void LineModel::runCheckedLines()
{
    if(!argz.isEmpty()){
        mProcess = new QProcess(this);
        connect(mProcess, SIGNAL(readyReadStandardOutput()),
                this, SLOT(outlog()));
        connect(mProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
                this, SLOT(onProcessFinished(int,QProcess::ExitStatus)));
        connect(mProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(ExecFinished2()));
        connect(mProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(uncheckedLinesStatus()));
        connect(mProcess, SIGNAL(finished(int)), mProcess, SLOT(deleteLater()) );

        QStringList argsFinal;
        argsFinal << "/c";

        if(!argz.isEmpty() && !executing)
        {
            QString val = argz.takeFirst();
            argsFinal.append(val);
            mProcess->start("cmd",argsFinal);

            if (argsFinal.size() != 1)
            {argsFinal.remove(1);}

        }
        else {
            if(argz.isEmpty()){
                checkedStatusCollect();}

        }

    }else exitCodeList.clear();
}


void LineModel::runAllLines()
{
    if(!argz.isEmpty()){
        mProcess = new QProcess(this);

        connect(mProcess, SIGNAL(readyReadStandardOutput()),
                this, SLOT(outlog()));
        connect(mProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
                this, SLOT(onProcessFinished(int,QProcess::ExitStatus)));
        connect(mProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(ExecFinished()));
        connect(mProcess, SIGNAL(finished(int)), mProcess, SLOT(deleteLater()) );

        QStringList argsFinal;
        argsFinal << "/c";

        if(!argz.isEmpty() && !executing)
        {
            QString val = argz.takeFirst();
            argsFinal.append(val);
            mProcess->start("cmd",argsFinal);

            executing=true;

            if (argsFinal.size() != 1){
                argsFinal.remove(1);}

        }

        else {
            if(argz.isEmpty()){
                statusCollect();}


        }

    }else exitCodeList.clear();
}

QStringList LineModel::argCollector()
{
    if(exitCodeList.isEmpty()){
        foreach (QObject * obj, mLines) {
            Line * line = static_cast<Line *> (obj);

            QString str= line->commandName();
            if (str == ""){
                str = "kaan";
            }
            argz.append(str);
        }}

    else {mProcess->kill();argz.clear(); emit runAgainPressed();outputList.clear();

    }

    return argz;

}


QStringList LineModel::checkedArgCollector()
{
    if(exitCodeList.isEmpty()){
        foreach (QObject * obj, mLines) {
            Line * line = static_cast<Line *> (obj);
            if (line->checkBoxState()==true){

                QString str= line->commandName();
                if (str == ""){
                    str = "kaan";
                }
                argz.append(str);
            }
            else if (line->checkBoxState()==false){
                QString allUncheckedLines=  line->commandName();
                allUncheckedLines=  "kaan";
                argz.append(allUncheckedLines);
            }}}
    else {mProcess->kill();argz.clear();emit runAgainPressed();outputList.clear();
    }

    return argz;
}


void LineModel::ExecFinished()
{
    executing = false;
    runAllLines();

    int a= exitCodeList.size()+1;
    QString s = QString :: number(a);
    outputList.append("\n----------------------------------");
    outputList.append(s);
    outputList.append(".PROCESS----------------------------------\n");
}


void LineModel::ExecFinished2()
{
    executing = false;
    runCheckedLines();

    int a= exitCodeList.size()+1;
    QString s = QString :: number(a);
    outputList.append("\n----------------------------------");
    outputList.append(s);
    outputList.append(".PROCESS----------------------------------\n");
}

void LineModel::stopProcess()
{

    if(!outputList.isEmpty()&&!exitCodeList.isEmpty()){
        mProcess->kill();}
    else {}
}


void LineModel::outputClear()
{
    outputList.clear();
}


void LineModel::onProcessFinished(int exitCode , QProcess::ExitStatus status)
{
    exitCodeList.append(exitCode);

    emit statusCode(exitCode);
    if(status==QProcess::CrashExit){emit runAgainPressed(); }

}

void LineModel::statusCollect(){
    int i = 0;
    foreach (QObject * obj, mLines) {
        Line * line = static_cast<Line *> (obj);


        if (exitCodeList[i]==0){line->setStatus("/qtIcons/tick.png");}
        else if (exitCodeList[i]==1||62097){line->setStatus("/qtIcons/xmark.gif");}
        else line->setStatus("/qtIcons/pending.gif");

        i++;

    }

}

void LineModel::checkedStatusCollect(){
    int i=0;
    foreach (QObject * obj, mLines) {
        Line * line = static_cast<Line *> (obj);
        if(line->checkBoxState()==true){

            if (exitCodeList[i]==0){line->setStatus("/qtIcons/tick.png");}
            else if (exitCodeList[i]==1||62097){line->setStatus("/qtIcons/xmark.gif");}
            else line->setStatus("/qtIcons/pending.gif");
        }
        else{line->setStatus("");}

        i++;
    }

}


QStringList LineModel::outlog()
{
    QString output = mProcess->readAllStandardOutput();

    outputList.append(output);
    emit outlogText(outputList.join(""));

    return outputList;
}



void LineModel::uncheckedLinesStatus()
{
    foreach (QObject * obj, mLines) {
        Line * line = static_cast<Line *> (obj);
        if (line->checkBoxState()==false){

            emit uncheckedLinesSignal(mLines.indexOf(line));
        }
    }

}
