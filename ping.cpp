#include "ping.h"

constexpr int normal_interval = 10000;
constexpr int error_interval = 2000;

using namespace std::literals;

Ping::Ping(QObject *parent) :
	QObject{parent},
	m_hostName{"8.8.8.8"},
	m_process{new QProcess(this)},
	m_timer{new QTimer(this)}
{
	connect(m_process, &QProcess::errorOccurred,
			this, &Ping::onErrorOcurred);
	connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
			this, &Ping::onFinished);
	connect(m_timer, &QTimer::timeout,
			this, &Ping::startPing);
	m_timer->setSingleShot(true);
	m_timer->start(normal_interval);
}

void Ping::onErrorOcurred(QProcess::ProcessError error)
{
	qDebug() << "Ping error occurred:" << error;
	m_timer->start(error_interval);
}

void Ping::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	qDebug() << "Ping finished with exit code:" << exitCode
			 << "and exit status:" << exitStatus;

	auto ok = exitStatus == QProcess::NormalExit && exitCode == 0;
	emit online(ok);
	m_timer->start(ok ? 10s : 2s);

}

void Ping::startPing()
{
	qDebug() << "Starting ping to" << m_hostName;
	QStringList parameters;
#if defined(WIN32)
	parameters << "-n" << "1";
#else
	parameters << "-c" << "1";
#endif

	parameters << m_hostName;
	m_process->start("ping", parameters);
}
