#pragma once
#include<QAbstractListModel>
#include "activitate.h"
#include <vector>
#include <qdebug.h>
class MyListModel :public QAbstractListModel {
	std::vector<Event> events;
public:
	MyListModel(const std::vector<Event>& events) :events{ events } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return events.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto ev = events[index.row()].get_title();
			//string ev = { "[" + std::to_string(events[index.row()].get_id()) + "]" + events[index.row()].get_title() };
			return QString::fromStdString(ev);
		}
		return QVariant{};
	}
	void setEvents(const vector<Event>& ev) {
		this->events = ev;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), 0);
		emit dataChanged(topLeft, bottomR);
	}
};