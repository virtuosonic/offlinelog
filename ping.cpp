#include "ping.h"

constexpr int normal_interval = 10000;
constexpr int error_interval = 2000;

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
	if (exitStatus == QProcess::NormalExit && exitCode == 0)
	{
		qDebug() << "Host" << m_hostName << "is reachable.";
		if (!m_isConnected)
		{
			m_lastChange = QDateTime::currentDateTime();
			m_isConnected = true;
			m_errorCount = 0;
			emit connectionChanged(m_isConnected, m_lastChange);
		}
		m_timer->start(normal_interval);
	}
	else
	{
		qDebug() << "Host" << m_hostName << "is not reachable.";
		m_errorCount++;
		if (m_isConnected)
		{
			m_isConnected = false;
			m_lastChange = QDateTime::currentDateTime();

		}
		if (m_errorCount > 4)
		{
			emit connectionChanged(m_isConnected, m_lastChange);
		}
		m_timer->start(error_interval);
	}

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
