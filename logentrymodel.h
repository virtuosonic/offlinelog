#ifndef LOGENTRYMODEL_H
#define LOGENTRYMODEL_H

#include <QAbstractListModel>
#include <QDateTime>

class LogEntryModel : public QAbstractListModel
{
	Q_OBJECT

public:
	explicit LogEntryModel(QObject *parent = nullptr);

	// Data structure for log entries
	struct LogEntry {
		QDateTime startTimestamp;
		QDateTime endTimestamp;
		bool online;
	};

	// QAbstractListModel interface
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

	// Methods to add/modify entries
	Q_INVOKABLE void addEntry(const QDateTime &startTimestamp, const QDateTime &endTimestamp, bool online);
	Q_INVOKABLE void setLastEndTimestamp(const QDateTime &endTimestamp);
	Q_INVOKABLE void clear();

private:
	QList<LogEntry> m_entries;

	enum Roles {
		StartTimestampRole = Qt::UserRole + 1,
		EndTimestampRole,
		OnlineRole
	};
};

#endif // LOGENTRYMODEL_H

