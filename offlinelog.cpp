#include "offlinelog.h"


OfflineLog::OfflineLog(QObject *parent) :
	QObject{parent},
	m_onlinetest{new OnlineTest(this)},
	m_errorcounter{new ErrorCounter(this)},
	m_logModel{new LogEntryModel(this)}
{
	setStatus("Verifying");
	connect(m_onlinetest, &OnlineTest::online,
			m_errorcounter, [=](bool isOnline)
	{
		if(isOnline)
		{
			m_errorcounter->reachable();
		}
		else
		{
			m_errorcounter->unreachable();
		}
	});

	connect(m_errorcounter, &ErrorCounter::connectionChanged,
			this, [=](bool isConnected,QDateTime timestamp)
	{
		if(isConnected)
		{
			setStatus("<font color='green'>Online</font>");
			qInfo("Connection restored at %s", qPrintable(timestamp.toString(Qt::ISODate)));
			if(m_logModel->rowCount())
			{
				m_logModel->setLastEndTimestamp(timestamp);
			}
		}
		else
		{
			setStatus("<font color='red'>Offline</font>");
			qWarning("Connection lost at %s", qPrintable(timestamp.toString(Qt::ISODate)));
			m_logModel->addEntry(timestamp,{}, false);
		}
	});
}

QString OfflineLog::status() const
{
	return m_status;
}

void OfflineLog::setStatus(const QString &newStatus)
{
	if (m_status == newStatus)
		return;
	m_status = newStatus;
	emit statusChanged();
}

LogEntryModel *OfflineLog::logModel() const
{
	return m_logModel;
}
