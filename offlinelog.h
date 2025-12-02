#ifndef OFFLINELOG_H
#define OFFLINELOG_H

#include <QObject>
#include "ping.h"
#include "onlinetest.h"
#include "errorcounter.h"
#include "logentrymodel.h"

class OfflineLog : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString status READ status NOTIFY statusChanged FINAL)
	Q_PROPERTY(LogEntryModel *logModel READ logModel CONSTANT FINAL)
public:
	explicit OfflineLog(QObject *parent = nullptr);

	QString status() const;
	void setStatus(const QString &newStatus);
	LogEntryModel *logModel() const;

signals:

	void statusChanged();

private:
	OnlineTest *m_onlinetest;
	ErrorCounter *m_errorcounter;
	LogEntryModel *m_logModel;

	QString m_status;
};

#endif // OFFLINELOG_H
