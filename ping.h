#ifndef PING_H
#define PING_H

#include <QObject>
#include <QDateTime>
#include <QProcess>
#include <QTimer>
#include <QDebug>

class Ping : public QObject
{
	Q_OBJECT
public:
	explicit Ping(QObject *parent = nullptr);

signals:
	void online(bool isOnline);

private slots:
	void onErrorOcurred(QProcess::ProcessError error);
	void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
	QString m_hostName;
	QProcess *m_process;
	QTimer *m_timer;
	void startPing();

};

#endif // PING_H
