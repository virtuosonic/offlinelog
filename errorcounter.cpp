#include "errorcounter.h"


ErrorCounter::ErrorCounter(QObject *parent)
	: QObject{parent}
{

}

void ErrorCounter::reachable()
{
	qDebug() << "Host is reachable.";
	if (!m_isConnected.has_value() || !m_isConnected.value())
	{
		m_lastChange = QDateTime::currentDateTime();
		m_isConnected = true;
		m_errorCount = 0;
		emit connectionChanged(m_isConnected.value(), m_lastChange);
	}
}

void ErrorCounter::unreachable()
{
	qDebug() << "Host is not reachable.";
	m_errorCount++;
	if (!m_isConnected.has_value() || m_isConnected.value())
	{
		m_isConnected = false;
		m_lastChange = QDateTime::currentDateTime();

	}
	if (m_errorCount == 4)
	{
		emit connectionChanged(m_isConnected.value(), m_lastChange);
	}
}
