#ifndef ONLINETEST_H
#define ONLINETEST_H

#include <QObject>
#include <QRestAccessManager>
#include <QRestReply>
#include <QTimer>

class OnlineTest : public QObject
{
	Q_OBJECT
public:
	explicit OnlineTest(QObject *parent = nullptr);

signals:
	void online(bool isOnline);
private:
	QNetworkAccessManager _manager;
	QRestAccessManager _restmanager;
	QTimer *m_timer;
	void gstatic204();
};

#endif // ONLINETEST_H
