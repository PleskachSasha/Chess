#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "PieceArr.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    PieceArr whitePieces(1);
    PieceArr blackPieces(0);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("whitePieces", &whitePieces);
    engine.rootContext()->setContextProperty("blackPieces", &blackPieces);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
