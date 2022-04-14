#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "linemodel.h"
#include <QQmlContext>
#include <QObject>
#include <QQuickView>
#include <QObject>
#include <QtQuick>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<LineModel> ("LineModel",1,0,"LineModel");
    LineModel mModel;


    if( !mModel.initialize())
        return -1;

    return app.exec();
}
