#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ping.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	app.setApplicationName("OfflineLog");
	Ping ping;
	QQmlApplicationEngine engine;
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
					 &app, []() { QCoreApplication::exit(-1); },
	Qt::QueuedConnection);
	engine.rootContext()->setContextProperty("ping", &ping);
	engine.loadFromModule("offlinelog", "Main");

	return app.exec();
}
