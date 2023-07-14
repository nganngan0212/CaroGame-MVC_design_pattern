#include <QGuiApplication>
#include "controller.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QTranslator translator;
    QTranslator guiTranslator;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Controller myCaroGame(&engine);

    translator.load(":/translations/vietnamese.qm");
    guiTranslator.load(":/translations/qtbase_fr.qm");

    app.installTranslator(&translator);
    app.installTranslator(&guiTranslator);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
