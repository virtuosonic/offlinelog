#ifndef ERRORCOUNTER_H
#define ERRORCOUNTER_H

#include <QObject>
#include <QDateTime>
#include <optional>

class ErrorCounter : public QObject
{
	Q_OBJECT
public:
	explicit ErrorCounter(QObject *parent = nullptr);
signals:
	void connectionChanged(bool isConnected,QDateTime timestamp);

public slots:
	void reachable();
	void unreachable();

private:
	std::optional<bool> m_isConnected;
	unsigned m_errorCount{0};
	QDateTime m_lastChange;
};

#endif // ERRORCOUNTER_H
