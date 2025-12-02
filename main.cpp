#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "offlinelog.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	app.setApplicationName("OfflineLog");
	app.setOrganizationName("Virtuosonic");
	app.setOrganizationDomain("virtuosonic.com");
	app.setApplicationVersion("1.0.0");
	OfflineLog ol;
	QQmlApplicationEngine engine;
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
					 &app, []() { QCoreApplication::exit(-1); },
	Qt::QueuedConnection);
	engine.rootContext()->setContextProperty("ol", &ol);
	engine.loadFromModule("offlinelog", "Main");

	return app.exec();
}
