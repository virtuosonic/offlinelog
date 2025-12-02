#include "logentrymodel.h"

LogEntryModel::LogEntryModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

int LogEntryModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return m_entries.size();
}

QVariant LogEntryModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || index.row() >= m_entries.size())
		return QVariant();

	const LogEntry &entry = m_entries.at(index.row());

	switch (role) {
	case StartTimestampRole:
		return entry.startTimestamp;
	case EndTimestampRole:
		return entry.endTimestamp;
	case OnlineRole:
		return entry.online;
	default:
		return QVariant();
	}
}

QHash<int, QByteArray> LogEntryModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[StartTimestampRole] = "startTimestamp";
	roles[EndTimestampRole] = "endTimestamp";
	roles[OnlineRole] = "online";
	return roles;
}

void LogEntryModel::addEntry(const QDateTime &startTimestamp, const QDateTime &endTimestamp, bool online)
{
	beginInsertRows(QModelIndex(), m_entries.size(), m_entries.size());
	LogEntry entry;
	entry.startTimestamp = startTimestamp;
	entry.endTimestamp = endTimestamp;
	entry.online = online;
	m_entries.append(entry);
	endInsertRows();
}

void LogEntryModel::setLastEndTimestamp(const QDateTime &endTimestamp)
{
	if (m_entries.isEmpty())
		return;

	int lastIndex = m_entries.size() - 1;
	m_entries[lastIndex].endTimestamp = endTimestamp;
	QModelIndex index = createIndex(lastIndex, 0);
	emit dataChanged(index, index, {EndTimestampRole});
}

void LogEntryModel::clear()
{
	beginResetModel();
	m_entries.clear();
	endResetModel();
}

