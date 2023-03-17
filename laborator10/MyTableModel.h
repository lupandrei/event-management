#pragma once
#include <QAbstractTableModel>
#include "activitate.h"
#include <vector>
#include <qdebug.h>

class MyTableModel :public QAbstractTableModel {
	std::vector<Event> events;
public:
	MyTableModel(const std::vector<Event>& events) :events{ events } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return events.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 3;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::ForegroundRole) {
			Event e = events[index.row()];
			/*if (e.get_time() > 0) {
				return QBrush{ Qt::red };
			}*/
		}
		if (role == Qt::DisplayRole) {

			Event e = events[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(e.get_title());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(e.get_description());
			}
			else if (index.column() == 2) {
				return QString::number(e.get_time());
			}
		}

		return QVariant{};	
	}

	void setPets(const std::vector<Event>& events) {
		this->events = events;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};